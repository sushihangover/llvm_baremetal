LINK_TARGET = main.axf
C_FILES := $(wildcard src/*.c)
AS_FILES := $(wildcard src/*.s)
LDFILE := $(wildcard src/*.ld)

TARGET_TRIPLE = $(BUILD_TRIPLE)
CORE = cortex-m0 
QCORE = cortex-m3 
FLOAT_TYPE = soft
ARMARCH = armv6-m
CMSIS_MATH_CORE = -DARM_MATH_CM3
DSP_MATH = arm_cortexM0l_math

CC = clang
AS = clang
LD = $(TARGET_TRIPLE)-ld
SIZE = $(TARGET_TRIPLE)-size
DUMP = $(TARGET_TRIPLE)-objdump
READELF = $(TARGET_TRIPLE)-readelf
STRIP = $(TARGET_TRIPLE)-strip
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
LGROUP += --library=$(DSP_MATH)
LGROUP += --end-group

CFLAGS  = -nostdlib
CFLAGS += -ffreestanding  
CFLAGS += -target $(TARGET_TRIPLE) 
CFLAGS += -mcpu=$(CORE) 
CFLAGS += -mfloat-abi=$(FLOAT_TYPE) 
CFLAGS += -msoft-float
CFLAGS += -mthumb 
CFLAGS += $(CMSIS_MATH_CORE)
CFLAGS += $(CINCLUDES) 

LFLAGS  = -static 
LFLAGS += -nostartfiles  
LFLAGS += -nostdlib
LFLAGS += -nostartupfiles 
LFLAGS += --gc-sections 
LFLAGS += --print-gc-sections 
LFLAGS += -Map $(BIN_DIR)/$(LINK_TARGET).map 
LFLAGS += -T $(LDFILE) 
LFLAGS += $(LINCLUDES) 
LFLAGS += $(OBJECTS_ALL)
LFLAGS += $(LGROUP)
#LFLAGS += -fwhole-program 
LFLAGS += -flto 

OBJ_DIR = obj
BIN_DIR = bin

OBJECTS_C := $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))
OBJECTS_S := $(addprefix obj/,$(notdir $(AS_FILES:.s=.o)))
OBJECTS_ALL := $(OBJECTS_S) $(OBJECTS_C)
LINK_AXF := $(addprefix $(BIN_DIR)/,$(notdir $(LINK_TARGET)))

all: debug 

release: COPTS=-Os
release: LOPTS=-O4
release: CDEBUG=
release: $(LINK_AXF)

debug: COPTS=-O0
debug: CDEBUG=-g
debug: $(LINK_AXF)

$(LINK_AXF) : | bin

bin:
	mkdir -p $@

bin/%.axf: $(OBJECTS_ALL)
	$(LD) $(LOPTS) $(LFLAGS) -o $@
	@$(SIZE) $@

$(OBJECTS_ALL) : | obj

obj:
	@mkdir -p $@

obj/%.o: src/%.c
	$(CC) $(COPTS) $(CDEBUG) $(CFLAGS) -o $@ -c $<

obj/%.o: src/%.s
	$(CC) $(COPTS) $(CDEBUG) $(CFLAGS) -o $@ -c $<

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

qgdb: all
	$(QEMU) -s -S $(QEMU_OPTS) $(BIN_DIR)/$(LINK_TARGET)

clean:
	-@$(RM) -f $(OBJ_DIR)/*.o
	-@$(RM) -f $(BIN_DIR)/$(LINK_TARGET)
	-@$(RM) -f $(BIN_DIR)/$(LINK_TARGET).map

env:
	@echo $(TOOLCHAIN_INSTALL)
	@echo $(BUILD_TRIPLE)
	@echo $(CMSIS)
	@echo $(NEWLIB)

