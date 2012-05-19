############
# Settings #
############

# Build all test applications:
#   make
#
# Program a test application using UISP (appname => test app e.g. sems1):
#   make program app=appname

# Location of build tools and atomthreads sources
KERNEL_DIR=../../kernel
TESTS_DIR=../../tests
CC=avr-gcc
OBJCOPY=avr-objcopy
SIZE=avr-size
UISP=uisp

# Modify this to the device name of the UART used for UISP
UISP_DEV=/dev/ttyUSB0

# Modify this to the CPU you are using
PART=atmega2560

# Enable stack-checking. WARNING: the full automated test suite currently
# requires a little over 1KB RAM with stack-checking enabled. If you are 
# using a device with 1KB internal SRAM and no external SRAM then you
# must disable stack-checking to run all of the automated tests.
#STACK_CHECK=true

# Directory for built objects
BUILD_DIR=build

# Port/application object files
APP_OBJECTS = atomport.o uart.o tests-main.o TracerPort.o StopWatch.o SerialPort.o
APP_ASM_OBJECTS = atomport-asm.o

# Kernel object files
KERNEL_OBJECTS = atomkernel.o atomsem.o atommutex.o atomtimer.o atomqueue.o Tracer.o SerialManager.o
# Collection of built objects (excluding test applications)
ALL_OBJECTS = $(APP_OBJECTS) $(APP_ASM_OBJECTS) $(KERNEL_OBJECTS)
BUILT_OBJECTS = $(patsubst %,$(BUILD_DIR)/%,$(ALL_OBJECTS))

# Test object files (dealt with separately as only one per application build)
TEST_OBJECTS = $(notdir $(patsubst %.c,%.o,$(wildcard $(TESTS_DIR)/*.c)))

# Target application filenames (.elf and .hex) for each test object
TEST_ELFS = $(patsubst %.o,%.elf,$(TEST_OBJECTS))
TEST_HEXS = $(patsubst %.o,%.hex,$(TEST_OBJECTS))

# Search build/output directory for dependencies
vpath %.o ./$(BUILD_DIR)
vpath %.elf ./$(BUILD_DIR)
vpath %.hex ./$(BUILD_DIR)

# GCC flags
CFLAGS=-g -mmcu=$(PART) -gdwarf-2 -Wall -Wno-error -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums

# Enable stack-checking (disable if not required)
ifeq ($(STACK_CHECK),true)
CFLAGS += -DATOM_STACK_CHECKING
endif


#################
# Build targets #
#################

# All tests
all: $(BUILD_DIR) $(TEST_HEXS) Makefile

# Make build/output directory
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

# Test HEX files (one application build for each test)
$(TEST_HEXS): %.hex: %.elf
	@echo Building $@
	$(OBJCOPY) -j .text -j .data -O ihex $(BUILD_DIR)/$< $(BUILD_DIR)/$@

# Test ELF files (one application build for each test)
$(TEST_ELFS): %.elf: %.o $(KERNEL_OBJECTS) $(APP_OBJECTS) $(APP_ASM_OBJECTS)
	$(CC) $(CFLAGS) $(BUILD_DIR)/$(notdir $<) $(BUILT_OBJECTS) --output $(BUILD_DIR)/$@ -Wl,-Map,$(BUILD_DIR)/$(basename $@).map

# Kernel objects builder
$(KERNEL_OBJECTS): %.o: $(KERNEL_DIR)/%.c
	$(CC) -c $(CFLAGS) -I. $< -o $(BUILD_DIR)/$(notdir $@)

# Test objects builder
$(TEST_OBJECTS): %.o: $(TESTS_DIR)/%.c
	$(CC) -c $(CFLAGS) -I. -I$(KERNEL_DIR) $< -o $(BUILD_DIR)/$(notdir $@)

# Application C objects builder
$(APP_OBJECTS): %.o: ./%.c
	$(CC) -c $(CFLAGS) -I. -I$(KERNEL_DIR) -I$(TESTS_DIR) $< -o $(BUILD_DIR)/$(notdir $@)

# Application asm objects builder
$(APP_ASM_OBJECTS): %.o: ./%.s
	$(CC) -c $(CFLAGS) -x assembler-with-cpp -I. -I$(KERNEL_DIR) $< -o $(BUILD_DIR)/$(notdir $@)

# .lst file builder
%.lst: %.c
	$(CC) $(CFLAGS) -I. -I$(KERNEL_DIR) -I$(TESTS_DIR) -Wa,-al $< > $@

# Clean
clean:
	rm -f *.o *.elf *.map *.hex *.bin *.lst
	rm -rf doxygen-kernel
	rm -rf doxygen-avr
	rm -rf build

# Send to STK500
program : $(BUILD_DIR)/$(app).hex
	$(SIZE) -C --mcu=$(PART) $(BUILD_DIR)/$(app).elf
	$(UISP) -dprog=stk500 -dserial=$(UISP_DEV) -dpart=$(PART) --erase --upload --verify if=$(BUILD_DIR)/$(app).hex

doxygen:
	doxygen $(KERNEL_DIR)/Doxyfile
	doxygen ./Doxyfile

# Library
AR=avr-ar
LIB=libatomthreads-avr.a
vpath %.a ./$(BUILD_DIR)
PORT_OBJECTS = atomport.o atomport-asm.o StopWatch.o TracerPort.o SerialPort.o
ALL_LIB_OBJECTS = $(PORT_OBJECTS) $(KERNEL_OBJECTS)
BUILT_LIB_OBJECTS = $(patsubst %,$(BUILD_DIR)/%,$(ALL_LIB_OBJECTS))
$(LIB): $(BUILD_DIR) $(ALL_LIB_OBJECTS)
	$(AR) ruv $(BUILD_DIR)/$@ $(BUILT_LIB_OBJECTS)
lib: $(LIB)

INSTALL_DIR=../../../atomthreads-avr
INCLUDE_DIR=$(INSTALL_DIR)/include
LIB_DIR=$(INSTALL_DIR)/lib

# Make install directories
$(INSTALL_DIR):
	mkdir $(INSTALL_DIR)
	mkdir $(INCLUDE_DIR)
	mkdir $(LIB_DIR)

install: $(INSTALL_DIR) $(INCLUDE_DIR) $(LIB_DIR) $(LIB)
	cp $(KERNEL_DIR)/*.h $(INCLUDE_DIR)/
	cp *.h $(INCLUDE_DIR)/
	cp $(BUILD_DIR)/$(LIB) $(LIB_DIR)/
	