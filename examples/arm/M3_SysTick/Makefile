LINK_TARGET = main.axf
C_FILES := $(wildcard src/*.c)
AS_FILES := $(wildcard src/*.s)
LDFILE := $(wildcard src/*.ld)

TARGET_TRIPLE = $(BUILD_TRIPLE)
CORE = cortex-m3
QCORE = $(CORE)
FLOAT_TYPE = soft
ARMARCH = armv7-m
CMSIS_MATH_CORE = -DARM_MATH_CM3

CC = clang
AS = clang
LD = $(TARGET_TRIPLE)-ld
SIZE = $(TARGET_TRIPLE)-size
DUMP = $(TARGET_TRIPLE)-objdump
READELF = $(TARGET_TRIPLE)-readelf
STRIP = $(TARGET_TRIPLE)-strip
GDB = $(TARGET_TRIPLE)-gdb
QEMU = qemu-system-arm
# QEMU_OPTS = -M lm3s811evb -cpu $(QCORE) -semihosting -nographic -kernel 
QEMU_OPTS = -M lm3s811evb -cpu $(QCORE) -semihosting -kernel 

# NEWLIBTYPE = newlib-nosyscalls
NEWLIBTYPE = newlib-syscalls

CINCLUDES  = -I$(NEWLIB)/$(NEWLIBTYPE)/$(TARGET_TRIPLE)/include
CINCLUDES += -I$(NEWLIB)/$(TARGET_TRIPLE)/include
CINCLUDES += -I$(CMSIS)/Include 

LINCLUDES += --library-path $(NEWLIB)/$(NEWLIBTYPE)/$(TARGET_TRIPLE)/lib/thumb/thumb2
LINCLUDES += --library-path $(NEWLIB)/lib/gcc/arm-none-eabi/4.8.3/$(ARMARCH)
LINCLUDES += --library-path $(CMSIS)/LIB/GCC 

LGROUP  = --start-group
LGROUP += --library=gcc
LGROUP += --library=c
LGROUP += --library=m
LGROUP += --library=arm_cortexM3l_math
LGROUP += --end-group

CFLAGS  = -nostdlib
CFLAGS += -ffreestanding  
CFLAGS += -target $(TARGET_TRIPLE) 
CFLAGS += -mcpu=$(CORE) 
CFLAGS += -mfloat-abi=$(FLOAT_TYPE) 
CFLAGS += -mthumb 
CFLAGS += $(CMSIS_MATH_CORE)
CFLAGS += $(CINCLUDES) 

LFLAGS  = -nostartfiles  
LFLAGS += -nostdlib
LFLAGS += -nostartupfiles 
LFLAGS += --gc-sections 
LFLAGS += --print-gc-sections 
LFLAGS += -Map $(BIN_DIR)/$(LINK_TARGET).map 
LFLAGS += -T $(LDFILE) 
LFLAGS += $(LINCLUDES) 
LFLAGS += $(OBJECTS_ALL)
LFLAGS += $(LGROUP)

OBJ_DIR = obj
BIN_DIR = bin

OBJECTS_C := $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))
OBJECTS_S := $(addprefix obj/,$(notdir $(AS_FILES:.s=.o)))
OBJECTS_ALL := $(OBJECTS_S) $(OBJECTS_C)
LINK_AXF := $(addprefix $(BIN_DIR)/,$(notdir $(LINK_TARGET)))

all: debug 

release: OPTS=-Os
release: DEBUG=
release: $(LINK_AXF)

debug: OPTS=-O0
debug: DEBUG=-g
debug: $(LINK_AXF)

$(LINK_AXF) : | bin

bin:
	mkdir -p $@

bin/%.axf: $(OBJECTS_ALL)
	$(LD) $(LFLAGS) -o $@
	@$(SIZE) $@

$(OBJECTS_ALL) : | obj

obj:
	@mkdir -p $@

obj/%.o: src/%.c
	$(CC) $(OPTS) $(DEBUG) $(CFLAGS) -o $@ -c $<

obj/%.o: src/%.s
	$(CC) $(OPTS) $(DEBUG) $(CFLAGS) -o $@ -c $<

size: 
	$(SIZE) $(BIN_DIR)/$(LINK_TARGET)

dump:
	$(DUMP) -d $(BIN_DIR)/$(LINK_TARGET)

sections:
	$(READELF) --sections $(BIN_DIR)/$(LINK_TARGET)

strip:
	$(STRIP) $(BIN_DIR)/$(LINK_TARGET)

qemu: 
	$(QEMU) $(QEMU_OPTS) $(BIN_DIR)/$(LINK_TARGET)

gdb: 
	$(GDB) $(BIN_DIR)/$(LINK_TARGET)

qgdb: all
	$(QEMU) -s -S $(QEMU_OPTS) $(BIN_DIR)/$(LINK_TARGET)

qkill:
	-@killall -SIGABRT $(QEMU)

clean:
	-@$(RM) -f $(OBJ_DIR)/*.o
	-@$(RM) -f $(BIN_DIR)/$(LINK_TARGET)
	-@$(RM) -f $(BIN_DIR)/$(LINK_TARGET).map

env:
	@echo $(TOOLCHAIN_INSTALL)
	@echo $(BUILD_TRIPLE)
	@echo $(CMSIS)
	@echo $(NEWLIB)

