LINK_TARGET = semihosted-main.axf
C_FILES = $(wildcard src/*.c)
AS_FILES = $(wildcard src/*.s)
LDFILE = generic-hosted.ld 
CORE = arm926ej-s
LOBJS = -l :crti.o -l :crtbegin.o -l :crtend.o -l :crtn.o 
LOBJSEARCH = -L/Users/administrator/arm-cs-tools/arm-none-eabi/lib -L/Users/administrator/arm-cs-tools/lib/gcc/arm-none-eabi/4.7.3 \
# CORE = cortex-m0
CC = clang
AS = clang
LD = arm-none-eabi-ld
SIZE = $(TARGET_TRIPLE)-size
QEMU = qemu-system-arm
QEMU_OPTS = -nographic -monitor null -serial null -semihosting -kernel 
OPTS = -O0 -fno-exceptions -fno-asynchronous-unwind-tables -fdata-sections -ffunction-sections
DEBUG = 
TARGET_TRIPLE = arm-none-eabi
FLOAT_TYPE = soft
CFLAGS = $(OPTS) -target $(TARGET_TRIPLE) -mcpu=$(CORE) -mfloat-abi=$(FLOAT_TYPE) -nostdlib -nostartfiles -ffreestanding
LFLAGS = -L$(OBJ_DIR) --gc-sections --print-gc-sections $(DEBUG) -T
OBJ_DIR = obj
BIN_DIR = bin

OBJECTS_C := $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))
OBJECTS_S := $(addprefix obj/,$(notdir $(AS_FILES:.s=.o)))
OBJECTS_ALL := $(OBJECTS_S) $(OBJECTS_C)

LINK = $(patsubst %.o,bin/%.axf,$(LINK_TARGET)) 

all : $(OBJECTS_ALL) $(LINK) 

$(LINK) : bin
	$(LD) $(LOBJSEARCH) $(LOBJS) $(LFLAGS) $(LDFILE) $(OBJECTS_ALL) -o $(BIN_DIR)/$(LINK_TARGET)
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

test :
	$(QEMU) $(QEMU_OPTS) $(BIN_DIR)/$(LINK_TARGET)

clean :
	-@$(RM) -f $(OBJ_DIR)/*.o
	-@$(RM) -f $(BIN_DIR)/$(LINK_TARGET)

