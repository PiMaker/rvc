TARGET ?= rvc
SRC_DIRS ?= ./src

CC=clang

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

Q=$(CURDIR)/buildroot-2021.05/output/host/bin/riscv32-buildroot-linux-gnu-

CFLAGS=-g

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -I./elfy/elfy.h $(OBJS) -o $@ $(LOADLIBES) $(LDLIBS) -L./elfy/target/release/ -Wl,--no-as-needed -ldl -lpthread -lelfy

-include $(DEPS)

# build device tree
dts.dtb: dts.dts
	dtc -o $@ $<

OPENSBI_BUILD=opensbi/build/platform/generic/firmware
PAYLOAD=rust_payload/target/riscv32ima-unknown-none-elf/release/rust_payload.bin
LINUX_PAYLOAD=linux/arch/riscv/boot/Image

BUILDROOT_MARKER=buildroot-2021.05/build.marker
$(BUILDROOT_MARKER):
	$(MAKE) -C buildroot-2021.05
	cd buildroot-2021.05 && cp init output/target/ && cp pi.js output/target/
	$(MAKE) -C buildroot-2021.05
	touch $@

$(PAYLOAD): $(shell find rust_payload/src -type f)
	cd rust_payload; \
		cargo +riscv32ima rustc -Zbuild-std --release --target "riscv32ima-unknown-none-elf" -- -Clink-arg=-Tlinker.ld -Clinker=$(Q)ld
	$(Q)objcopy -O binary \
		rust_payload/target/riscv32ima-unknown-none-elf/release/rust_payload $(PAYLOAD)

rust_payload.bin: rust_payload.elf
	cp $(OPENSBI_BUILD)/fw_payload.bin ./rust_payload.bin
rust_payload.elf: $(PAYLOAD) $(BUILDROOT_MARKER)
	$(MAKE) -C opensbi clean
	env CROSS_COMPILE=$(Q) \
		PLATFORM=generic \
		PLATFORM_RISCV_XLEN=32 \
		PLATFORM_RISCV_ISA=rv32ima \
		PLATFORM_RISCV_ABI=ilp32 \
		FW_PAYLOAD_PATH=../$(PAYLOAD) \
		FW_PIC=n \
		$(MAKE) -C opensbi all
	cp $(OPENSBI_BUILD)/fw_payload.elf ./rust_payload.elf

.PHONY: $(LINUX_PAYLOAD)
$(LINUX_PAYLOAD): linux $(BUILDROOT_MARKER)
	cd linux && (git am ../linux-_pi_-patches-for-rvc.patch || true)
	cd linux && \
		env CROSS_COMPILE=$(Q) \
			CFLAGS="-march=rv32ima -mabi=ilp32" \
			LDFLAGS="-march=rv32ima -mabi=ilp32" \
			ARCH=riscv \
			KCONFIG_ALLCONFIG=../linux.config \
				make allnoconfig
	cd linux && \
		env CROSS_COMPILE=$(Q) \
			CFLAGS="-march=rv32ima -mabi=ilp32" \
			LDFLAGS="-march=rv32ima -mabi=ilp32" \
			ARCH=riscv \
				intercept-build make -j$(shell nproc)

linux_payload.bin: linux_payload.elf
	cp $(OPENSBI_BUILD)/fw_payload.bin ./linux_payload.bin
linux_payload.elf: $(LINUX_PAYLOAD) $(BUILDROOT_MARKER)
	$(MAKE) -C opensbi clean
	env CROSS_COMPILE=$(Q) \
		PLATFORM=generic \
		PLATFORM_RISCV_XLEN=32 \
		PLATFORM_RISCV_ISA=rv32ima \
		PLATFORM_RISCV_ABI=ilp32 \
		FW_PAYLOAD_PATH=../$(LINUX_PAYLOAD) \
		FW_PIC=n \
		$(MAKE) -C opensbi all
	cp $(OPENSBI_BUILD)/fw_payload.elf ./linux_payload.elf

.PHONY: run
run: fw_payload.bin $(TARGET) dts.dtb
	./rvc -b fw_payload.bin -d dts.dtb

run-v1: fw_payload.bin $(TARGET) dts.dtb
	./rvc -b fw_payload.bin -d dts.dtb -v1


.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

.PHONY: distclean
distclean: clean
	$(RM) $(TARGET) $(OBJS) $(DEPS) *_payload.*
	$(MAKE) -C opensbi clean
	$(MAKE) -C linux clean
	$(RM) $(BUILDROOT_MARKER)
