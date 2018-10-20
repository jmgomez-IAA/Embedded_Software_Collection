#This Makefile should be modified to include multiple platform.
# Set some paths for the tools.

PLATFORM=atsam4s-xpro
MCAL=atsam4sd32c

SRC_DIR = src/
BUILD_DIR = build/
BIN_DIR = bin/


#TOOL_PATH = /opt/gnu-mcu-eclipse/arm-none-eabi-gcc/7.2.1-1.1-20180401-0515/bin/
TOOL_PATH = /opt/gcc-arm-none-eabi-7-2018-q2-update/bin/
FLASH_PATH = /opt/edbg

# We are compiling for SAM4S CortexM4 on SAM4S Xplainned Pro Board
MCAL_DIR = src/mcal/${MCAL}
PLATFORM_DIR = src/platform/${PLATFORM}
ARCH = cortex-m4

# Compiler toolset
CROSS_COMPILE = arm-none-eabi-
CXX = ${TOOL_PATH}/${CROSS_COMPILE}g++
LD = ${TOOL_PATH}/${CROSS_COMPILE}g++
OBJDUMP = ${TOOL_PATH}/${CROSS_COMPILE}objdump
SIZE = ${TOOL_PATH}/${CROSS_COMPILE}size
OBJCOPY = ${TOOL_PATH}/${CROSS_COMPILE}objcopy
FLASH = ${FLASH_PATH}/edbg

# Compiler flags
#-----------------
INCLUDES = src/
LIBS = src/

CINCLUDES = -Isrc \
            -Isrc/mcal/${MCAL} \
            -Isrc/hal/${PLATFORM} \
            -Isrc/util/STL \
            -Isrc/sys/start/${MCAL}

#Use the GCC -ffunction-sections and LD --gc-sections directives to automatically only include used code and data for C sources. This will require linker scripts updated to include the new input sections.
CPPFLAGS =  -mcpu=${ARCH} -ffunction-sections\
			-g -O2 -Wall -Wextra -pedantic -fsigned-char -fno-exceptions

CXXFLAGS = -std=c++11

LDFLAGS =  -mthumb -L"./src/sys/start/${MCAL}" -Wl,--gc-sections -T${MCAL}.ld

SRC = src/sys/start/${MCAL}/crt0.cpp \
      src/sys/start/${MCAL}/crt0_init_ram.cpp \
      src/sys/start/${MCAL}/crt1.cpp \
      src/sys/start/${MCAL}/int_vect.cpp \
      src/mcal/mcal.cpp \
      src/mcal/${MCAL}/mcal_cpu.cpp\
      src/mcal/${MCAL}/mcal_irq.cpp\
      src/mcal/${MCAL}/mcal_wdt.cpp\
      src/mcal/${MCAL}/mcal_port.cpp\
      src/mcal/${MCAL}/mcal_gpt.cpp\
	  src/mcal/${MCAL}/mcal_uart.cpp\
      src/hal/hal.cpp src/hal/${PLATFORM}/hal_led.cpp\
      src/hal/${PLATFORM}/hal_sw.cpp

OBJ =  $(addprefix $(BUILD_DIR),$(patsubst %.cpp,%.o,$(SRC)))

PROGRAM = src/app/pio_periph_test.cpp src/app/pio_periph_test.cpp src/app/uart_periph_test.cpp

.PHONY = all

all: pio_periph systick_periph uart_periph
	echo "All done..."
	echo "sudo ${FLASH} -bpv -t atmel_cm4 -f bin/program_to_test.elf.bin"

$(BIN_DIR)systick_periph_test.elf: $(BUILD_DIR)src/app/systick_periph_test.o $(OBJ)
	mkdir -p $(@D)
	${LD} -g $(LDFLAGS) $^ -o $@ -Wl,-Map="$(BUILD_DIR)src/app/systick_periph_test.map"
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

$(BIN_DIR)pio_periph_test.elf: $(BUILD_DIR)src/app/pio_periph_test.o $(OBJ)
	mkdir -p $(@D)
	${LD} -g  $(LDFLAGS) $^ -o $@ -Wl,-Map="$(BUILD_DIR)src/app/pio_periph_test.map"
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

$(BIN_DIR)uart_periph_test.elf: $(BUILD_DIR)src/app/uart_periph_test.o $(OBJ)
	mkdir -p $(@D)
	${LD} -g  $(LDFLAGS) $^ -o $@ -Wl,-Map="$(BUILD_DIR)src/app/uart_periph_test.map"
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

$(BUILD_DIR)src/app/pio_periph_test.o: src/app/pio_periph_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/app/systick_periph_test.o: src/app/systick_periph_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/app/uart_periph_test.o: src/app/uart_periph_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)%.o: %.cpp
	mkdir -p $(@D)
	$(CXX)  $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -c $< -o $@

pio_periph: $(BIN_DIR)pio_periph_test.elf
	echo "Building PIO  Peripheral Test Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin

systick_periph: $(BIN_DIR)systick_periph_test.elf
	echo "Building PIO  Peripheral Test Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin

uart_periph: $(BIN_DIR)uart_periph_test.elf
	echo "Building PIO  Peripheral Test Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin


clean:
	rm bin build -rf
