LINK_TARGET = HelloWorldSimple.axf
C_FILES := $(wildcard src/*.c)
AS_FILES := $(wildcard src/*.s)
LDFILE := $(wildcard src/*.ld)

CC = clang
AS = clang
LD = arm-none-eabi-ld
SIZE = $(TARGET_TRIPLE)-size
QEMU = qemu-system-arm
QEMU_OPTS = -M versatilepb -m 128M -nographic -kernel 
OPTS = -O0 -fno-exceptions -fno-asynchronous-unwind-tables -fdata-sections -ffunction-sections
DEBUG = 
TARGET_TRIPLE = arm-none-eabi
CORE = arm926ej-s
FLOAT_TYPE = soft
CFLAGS = $(OPTS) -target $(TARGET_TRIPLE) -mcpu=$(CORE) -mfloat-abi=$(FLOAT_TYPE)
LFLAGS = -L$(OBJ_DIR) --gc-sections --print-gc-sections $(DEBUG) -T
OBJ_DIR = obj
BIN_DIR = bin

OBJECTS_C := $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))
OBJECTS_S := $(addprefix obj/,$(notdir $(AS_FILES:.s=.o)))
OBJECTS_ALL := $(OBJECTS_S) $(OBJECTS_C)

LINK = $(patsubst %.o,bin/%.axf,$(LINK_TARGET)) 

all : $(OBJECTS_ALL) $(LINK) 

$(LINK) : bin
	$(LD) $(LFLAGS) $(LDFILE) $(OBJECTS_ALL) -o $(BIN_DIR)/$(LINK_TARGET)
	$(SIZE) $(BIN_DIR)/$(LINK_TARGET)

bin :
	@mkdir -p $@

$(OBJECTS_ALL) : | obj

obj :
	@mkdir -p $@

obj/%.o : src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

obj/%.o : src/%.s
	$(CC) $(CFLAGS) -o $@ -c $<

size : all
	$(SIZE) $(BIN_DIR)/$(LINK_TARGET)

test : all
	$(QEMU) $(QEMU_OPTS) $(BIN_DIR)/$(LINK_TARGET)

clean :
	-@$(RM) -f $(OBJ_DIR)/*.o
	-@$(RM) -f $(BIN_DIR)/$(LINK_TARGET)

