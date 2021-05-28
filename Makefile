TARGET ?= rvc
SRC_DIRS ?= ./src

CC=clang

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -I./elfy/elfy.h $(OBJS) -o $@ $(LOADLIBES) $(LDLIBS) -L./elfy/target/debug/ -Wl,--no-as-needed -ldl -lpthread -lelfy

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)

