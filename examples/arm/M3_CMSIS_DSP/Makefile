LINK_TARGET = main.axf

C_FILES := $(wildcard src/*.c)
AS_FILES := $(wildcard src/*.s)
LD_FILE := $(wildcard src/*.ld)

TARGET_TRIPLE = arm-none-eabi
CORE = cortex-m0 
QCORE = cortex-m3
FLOAT_TYPE = soft
ARMARCH = armv6-m
CMSIS_MATH_CORE = ARM_MATH_CM0

CC = clang
AS = clang
LD = $(TARGET_TRIPLE)-ld
SIZE = $(TARGET_TRIPLE)-size
QEMU = qemu-system-arm
QEMU_OPTS = -cpu $(QCORE) -semihosting -nographic -kernel 

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
LGROUP += --library=arm_cortexM0l_math
LGROUP += --end-group

CFLAGS  = -nostdlib
CFLAGS += -ffreestanding  
CFLAGS += -target $(TARGET_TRIPLE) 
CFLAGS += -mcpu=$(CORE) 
CFLAGS += -mfloat-abi=$(FLOAT_TYPE) 
CFLAGS += -mthumb 
CFLAGS += -D$(CMSIS_MATH_CORE)
CFLAGS += $(CINCLUDES) 

LFLAGS  = -nostartfiles  
LFLAGS += -nostdlib
LFLAGS += -nostartupfiles 
LFLAGS += --gc-sections 
LFLAGS += --print-gc-sections 
LFLAGS += -Map $(BIN_DIR)/$(LINK_TARGET).map 
LFLAGS += -T $(LD_FILE) 
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

qemu: 
	$(QEMU) $(QEMU_OPTS) $(BIN_DIR)/$(LINK_TARGET)

qgdb: all
	$(QEMU) -s -S $(QEMU_OPTS) $(BIN_DIR)/$(LINK_TARGET)

qkill:
	@killall -SIGABRT $(QEMU)

clean:
	-@$(RM) -f $(OBJ_DIR)/*.o
	-@$(RM) -f $(BIN_DIR)/$(LINK_TARGET)
	-@$(RM) -f $(BIN_DIR)/$(LINK_TARGET).map

env:
	@echo $(TOOLCHAIN_INSTALL)
	@echo $(TARGET_TRIPLE)
	@echo $(CMSIS)
	@echo $(NEWLIB)

