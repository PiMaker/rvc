TARGET ?= rvc
SRC_DIRS ?= ./src

CC=clang

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -I./elfy/elfy.h $(OBJS) -o $@ $(LOADLIBES) $(LDLIBS) -L./elfy/target/release/ -Wl,--no-as-needed -ldl -lpthread -lelfy

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS) fw_payload.*
	$(MAKE) -C opensbi clean

-include $(DEPS)

# build device tree
dts.dtb: dts.dts
	dtc -o $@ $<

OPENSBI_BUILD="opensbi/build/platform/generic/firmware"
PAYLOAD="rust_payload/target/riscv32ima-unknown-none-elf/release/rust_payload.bin"

$(PAYLOAD): $(shell find rust_payload/src -type f)
	cd rust_payload; \
		cargo +riscv32ima rustc -Zbuild-std --release --target "riscv32ima-unknown-none-elf" -- -Clink-arg=-Tlinker.ld -Clinker=riscv32-elf-ld
	riscv32-elf-objcopy -O binary \
		rust_payload/target/riscv32ima-unknown-none-elf/release/rust_payload $(PAYLOAD)

fw_payload.bin: fw_payload.elf
	cp $(OPENSBI_BUILD)/fw_payload.bin .
fw_payload.elf: $(PAYLOAD)
	env CROSS_COMPILE=riscv64-elf- \
		PLATFORM=generic \
		PLATFORM_RISCV_XLEN=32 \
		PLATFORM_RISCV_ISA=rv32ima \
		PLATFORM_RISCV_ABI=ilp32 \
		FW_PAYLOAD_PATH=../$(PAYLOAD) \
		FW_PIC=n \
		ELFFLAGS=-L/usr/lib/gcc/riscv64-elf/10.2.0/rv32im/ilp32 \
		$(MAKE) -C opensbi all
	cp $(OPENSBI_BUILD)/fw_payload.elf .

.PHONY: run
run: fw_payload.bin $(TARGET) dts.dtb
	./rvc -b fw_payload.bin -d dts.dtb

run-v1: fw_payload.bin $(TARGET) dts.dtb
	./rvc -b fw_payload.bin -d dts.dtb -v1
