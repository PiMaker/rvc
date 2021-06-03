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
	$(RM) $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)

# build device tree
dts.dtb: dts.dts
	dtc -o $@ $<

OPENSBI_BUILD="opensbi/build/platform/generic/firmware"

fw_payload.bin: fw_payload.elf
	cp $(OPENSBI_BUILD)/fw_payload.bin .
fw_payload.elf: opensbi
	env CROSS_COMPILE=riscv64-elf- \
		PLATFORM=generic \
		PLATFORM_RISCV_XLEN=32 \
		PLATFORM_RISCV_ISA=rv32ima \
		PLATFORM_RISCV_ABI=ilp32 \
		FW_PIC=n \
		ELFFLAGS=-L/usr/lib/gcc/riscv64-elf/10.2.0/rv32im/ilp32 \
		$(MAKE) -C opensbi all
	cp $(OPENSBI_BUILD)/fw_payload.elf .
