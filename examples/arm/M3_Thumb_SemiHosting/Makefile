LINK_TARGET = thumb_semi_hosting.axf
C_FILES := $(wildcard src/*.c)
AS_FILES := $(wildcard src/*.s)
LDFILE := $(wildcard src/*.ld)

CC = clang
AS = clang
LD = $(TARGET_TRIPLE)-ld
SIZE = $(TARGET_TRIPLE)-size
QEMU = qemu-system-arm
QEMU_OPTS = -cpu $(CORE) -semihosting -nographic -kernel 
OPTS = -O0 
CINCLUDES += -I$(NEWLIB)/newlib/$(TARGET_TRIPLE)/include
CINCLUDES += -I$(NEWLIB)/$(TARGET_TRIPLE)/include
CINCLUDES += -I$(CMSIS)/Include 
LINCLUDES += --library-path $(NEWLIB)/newlib/$(TARGET_TRIPLE)/lib/thumb 
# LINCLUDES += --library-path $(NEWLIB)/newlib/$(TARGET_TRIPLE)/lib
# LINCLUDES += --library-path $(NEWLIB)/$(TARGET_TRIPLE)/lib/thumb 
# LINCLUDES += --library-path $(NEWLIB)/$(TARGET_TRIPLE)/lib
# LINCLUDES += --library-path $(NEWLIB)/lib/gcc
LINCLUDES += --library-path $(NEWLIB)/lib/gcc/arm-none-eabi/4.8.3/thumb
# LINCLUDES += --library-path $(NEWLIB)/lib/gcc/arm-none-eabi/4.8.3
LINCLUDES += --library-path $(CMSIS)/LIB/GCC 
# LGROUP += --start-group --library=arm_cortexM3l_math -lgcc -lc --end-group
LGROUP += --start-group --library=arm_cortexM3l_math -lgcc -lc --end-group
DEBUG = 
TARGET_TRIPLE = $(BUILD_TRIPLE)
CORE = cortex-m3 
CMSIS_MATH_CORE = -DARM_MATH_CM3
FLOAT_TYPE = soft
CFLAGS = $(OPTS) -target $(TARGET_TRIPLE) -mcpu=$(CORE) -mfloat-abi=$(FLOAT_TYPE) $(CINCLUDES) $(CMSIS_MATH_CORE)
# LFLAGS = $(LINCLUDES) -L$(OBJ_DIR) -nostdlib -nostartupfiles --gc-sections --print-gc-sections $(DEBUG) -T
LFLAGS = -T $(LDFILE) $(LINCLUDES) $(DEBUG) 
OBJ_DIR = obj
BIN_DIR = bin

OBJECTS_C := $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))
OBJECTS_S := $(addprefix obj/,$(notdir $(AS_FILES:.s=.o)))
OBJECTS_ALL := $(OBJECTS_S) $(OBJECTS_C)

LINK = $(patsubst %.o,bin/%.axf,$(LINK_TARGET)) 

all : $(OBJECTS_ALL) $(LINK) 

$(LINK) : bin
	$(LD) $(LFLAGS) $(OBJECTS_ALL) $(LGROUP) -o $(BIN_DIR)/$(LINK_TARGET)
	$(SIZE) $(BIN_DIR)/$(LINK_TARGET)

bin :
	@mkdir -p $@

$(OBJECTS_ALL) : | obj

obj :
	@mkdir -p $@

obj/%.o : src/%.c
	$(CC) $(DEBUG) $(CFLAGS) -o $@ -c $<

obj/%.o : src/%.s
	$(CC) $(DEBUG) $(CFLAGS) -o $@ -c $<

size : all
	$(SIZE) $(BIN_DIR)/$(LINK_TARGET)

qemu : 
	$(QEMU) $(QEMU_OPTS) $(BIN_DIR)/$(LINK_TARGET)

qgdb : 
	$(QEMU) -s -S $(QEMU_OPTS) $(BIN_DIR)/$(LINK_TARGET)

clean :
	-@$(RM) -f $(OBJ_DIR)/*.o
	-@$(RM) -f $(BIN_DIR)/$(LINK_TARGET)

env :
	@echo $(TOOLCHAIN_INSTALL)
	@echo $(BUILD_TRIPLE)
	@echo $(CMSIS)
	@echo $(NEWLIB)

