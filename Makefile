TARGET ?= rvc
SRC_DIRS ?= ./src ./tinypngout

CC=clang

BUILDROOT := "buildroot-2022.02.1"

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

Q=$(CURDIR)/$(BUILDROOT)/output/host/bin/riscv32-buildroot-linux-gnu-

CFLAGS ?= -g -O2

.PHONY: $(TARGET)
$(TARGET):
	touch src/main.c
	rm -f src/main.o
	$(MAKE) $(TARGET)-real

$(TARGET)-real: $(OBJS)
	$(CC) $(LDFLAGS) -I./elfy/elfy.h -I./tinypngout/TinyPngOut.h $(OBJS) -o $(TARGET) $(LOADLIBES) $(LDLIBS) -L./elfy/target/release/ -Wl,--no-as-needed -ldl -lpthread -lelfy -lm

-include $(DEPS)

# build device tree
dts.dtb: dts.dts
	dtc -o $@ $<

OPENSBI_BUILD=opensbi/build/platform/generic/firmware
PAYLOAD=rust_payload/target/riscv32ima-unknown-none-elf/release/rust_payload.bin
LINUX_PAYLOAD=linux/arch/riscv/boot/Image
RAYTRACE_PAYLOAD=rust_raytrace/target/riscv32ima-unknown-none-elf/release/rust_raytrace.bin

BUILDROOT_MARKER=$(BUILDROOT)/build.marker
$(BUILDROOT_MARKER):
	if [ ! -f $(BUILDROOT_MARKER) ]; then $(MAKE) -C $(BUILDROOT); fi
	touch $@

$(PAYLOAD): $(shell find rust_payload/src -type f)
	cd rust_payload; \
		cargo +riscv32ima rustc -Zbuild-std --release --target "riscv32ima-unknown-none-elf" -- -Clink-arg=-Tlinker.ld -Clinker=$(Q)ld
	$(Q)objcopy -O binary \
		rust_payload/target/riscv32ima-unknown-none-elf/release/rust_payload $(PAYLOAD)

$(RAYTRACE_PAYLOAD): $(shell find rust_raytrace/src -type f)
	cd rust_raytrace; \
		cargo +riscv32ima rustc -Zbuild-std --release --target "riscv32ima-unknown-none-elf" -- -Clink-arg=-Tlinker.ld -Clinker=$(Q)ld
	$(Q)objcopy -O binary \
		rust_raytrace/target/riscv32ima-unknown-none-elf/release/rust_raytrace $(RAYTRACE_PAYLOAD)

rust_raytrace.bin: $(RAYTRACE_PAYLOAD)
	cp $(RAYTRACE_PAYLOAD) $@

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
	# cd linux && (git apply ../linux-_pi_-patches-for-rvc.patch || true)
	cd linux && \
		env CROSS_COMPILE=$(Q) \
			CFLAGS="-march=rv32ima -mabi=ilp32" \
			LDFLAGS="-march=rv32ima -mabi=ilp32" \
			ARCH=riscv \
			KCONFIG_ALLCONFIG=../linux.config \
				make allnoconfig
	cd linux && ./scripts/clang-tools/gen_compile_commands.py
	cd linux && \
		env CROSS_COMPILE=$(Q) \
			CFLAGS="-march=rv32ima -mabi=ilp32" \
			LDFLAGS="-march=rv32ima -mabi=ilp32" \
			ARCH=riscv \
				make -j$(shell nproc)
	cd linux && ./scripts/clang-tools/gen_compile_commands.py

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

.PHONY: run-v1
run-v1: fw_payload.bin $(TARGET) dts.dtb
	./rvc -b fw_payload.bin -d dts.dtb -v1

.PHONY: run-network
run-network: linux_payload.bin $(TARGET) dts.dtb
	tmux new -s rvc-network -d "./rvc -b linux_payload.bin -d dts.dtb -n /tmp/rvc-test.sock -i ./$(BUILDROOT)/output/images/rootfs.romfs -f"
	tmux split-window -t rvc-network "./rvc -b linux_payload.bin -d dts.dtb -N /tmp/rvc-test.sock -i ./$(BUILDROOT)/output/images/rootfs.romfs -f"
	tmux select-layout -t rvc-network even-horizontal
	tmux attach -t rvc-network
	tmux kill-session -t rvc-network || true

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

.PHONY: distclean
distclean: clean
	$(RM) $(TARGET) $(OBJS) $(DEPS) *_payload.*
	$(MAKE) -C opensbi clean
	$(MAKE) -C linux clean
	$(RM) $(BUILDROOT_MARKER)
