PAYLOAD=../mprv/micropython/ports/riscv-generic/build/firmware.bin
OPENSBI_BUILD=opensbi/build/platform/generic/firmware

fw_payload.bin:
	cd micropython && (git am ../0001-add-riscv-port.patch || true)
	env CROSS_COMPILE=../buildroot-2021.05/output/host/bin/riscv32-buildroot-linux-gnu- \
		PLATFORM=generic \
		PLATFORM_RISCV_XLEN=32 \
		PLATFORM_RISCV_ISA=rv32ima \
		PLATFORM_RISCV_ABI=ilp32 \
		FW_PAYLOAD_PATH=$(PAYLOAD) \
		FW_PIC=n \
		$(MAKE) -C opensbi all
	cp $(OPENSBI_BUILD)/fw_payload.bin .
