TARGET ?= bare
SRC_DIRS ?= .

PREFIX ?= ../buildroot-2021.05/output/host/bin/riscv32-buildroot-linux-gnu-
CC := $(PREFIX)cc
AS := $(PREFIX)as
LD := $(PREFIX)ld
OBJCOPY := $(PREFIX)objcopy

SRCS := $(wildcard *.S)
SRCS += $(wildcard *.c)
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CFLAGS += -O2 -march=rv32ima -mabi=ilp32 -fno-stack-protector -fno-pie
ASFLAGS += -march=rv32ima -mabi=ilp32
LDFLAGS += -static -nostdlib -nostartfiles -nodefaultlibs -Triscv32.ld -Wl,--no-as-needed

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LOADLIBES) $(LDLIBS)

$(TARGET).img: $(TARGET)
	$(OBJCOPY) -O binary $< $@

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

.PHONY: run
run: $(TARGET).img
	../rvc -d ../dts.dtb -b $(TARGET).img
