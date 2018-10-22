#This Makefile should be modified to include multiple platform.
# Set some paths for the tools.

PLATFORM=gr712rc-comercial
MCAL=gr712rc

SRC_DIR = src/
BUILD_DIR = build/
BIN_DIR = bin/


#TOOL_PATH = /opt/gnu-mcu-eclipse/arm-none-eabi-gcc/7.2.1-1.1-20180401-0515/bin/
TOOL_PATH=/opt/bcc-2.0.2-gcc/bin/
#/opt/bcc-2.0.2-gcc/sparc-gaisler-elf/bin/
FLASH_PATH = /opt/grmon

# We are compiling for SAM4S CortexM4 on SAM4S Xplainned Pro Board
MCAL_DIR = src/mcal/${MCAL}
PLATFORM_DIR = src/platform/${PLATFORM}
ARCH = leon3

# Compiler toolset
CROSS_COMPILE = sparc-gaisler-elf-
CXX = ${TOOL_PATH}/${CROSS_COMPILE}g++
LD = ${TOOL_PATH}/${CROSS_COMPILE}gcc
OBJDUMP = ${TOOL_PATH}/${CROSS_COMPILE}objdump 
SIZE = ${TOOL_PATH}/${CROSS_COMPILE}size
OBJCOPY = ${TOOL_PATH}/${CROSS_COMPILE}objcopy
FLASH = ${FLASH_PATH}/edbg

# Compiler flags
#-----------------
INCLUDES = src/
LIBS = src/

CPPFLAGS =  -mcpu=${ARCH} -qbsp=${MCAL} -mfix-gr712rc -msoft-float -mflat\
            -g -O2 -Wall -Wextra -pedantic -fsigned-char -fno-exceptions

CXXFLAGS = -std=c++11

CINCLUDES = -Isrc \
            -Isrc/mcal/${MCAL} \
            -Isrc/hal/${PLATFORM} \
            -Isrc/util/STL \
            -Isrc/sys/start/${MCAL}

LDFLAGS = -T linkcmds-ahbram 

SRC = src/mcal/mcal.cpp \
      src/mcal/${MCAL}/mcal_cpu.cpp\
      src/mcal/${MCAL}/mcal_port.cpp\
      src/mcal/${MCAL}/mcal_spw.cpp\
      src/hal/hal.cpp src/hal/${PLATFORM}/hal_led.cpp\
      src/hal/${PLATFORM}/hal_sw.cpp

OBJ =  $(addprefix $(BUILD_DIR),$(patsubst %.cpp,%.o,$(SRC)))

PROGRAM = src/app/pio_periph_test.cpp

.PHONY = all

all: pio_periph spw_periph
	echo "All done..."
	echo "sudo ${FLASH} -bpv -t atmel_cm4 -f bin/program_to_test.elf.bin"

$(BIN_DIR)pio_periph_test.elf: $(BUILD_DIR)src/app/pio_periph_test.o $(OBJ)
	mkdir -p $(@D)
	${LD} -g $^ -o $@  $(LDFLAGS)
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

$(BIN_DIR)spw_periph_test.elf: $(BUILD_DIR)src/app/spw_periph_test.o $(OBJ)
	mkdir -p $(@D)
	${LD} -g $^ -o $@  $(LDFLAGS) $(CXXFLAGS) $(CPPFLAGS)
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

$(BUILD_DIR)src/app/pio_periph_test.o: src/app/pio_periph_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/app/spw_periph_test.o: src/app/spw_periph_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)%.o: %.cpp
	mkdir -p $(@D)
	$(CXX)  $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -c $< -o $@

pio_periph: $(BIN_DIR)pio_periph_test.elf
	echo "Building PIO  Peripheral Test Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin

spw_periph: $(BIN_DIR)spw_periph_test.elf
	echo "Building Spw  Peripheral Test Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin


clean:
	rm bin build -rf
