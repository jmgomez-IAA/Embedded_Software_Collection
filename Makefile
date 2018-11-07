#This Makefile should be modified to include multiple platform.
# Set some paths for the tools.

PLATFORM=sensor-mp-v1
MCAL=atsam4s16c

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
	  src/mcal/${MCAL}/mcal_adc.cpp\
      src/hal/hal.cpp \
	  src/hal/${PLATFORM}/hal_led.cpp\
      src/hal/${PLATFORM}/hal_sw.cpp

#	  src/hal/${PLATFORM}/hal_flow.cpp\
#	  src/hal/${PLATFORM}/hal_rele.cpp

OBJ =  $(addprefix $(BUILD_DIR),$(patsubst %.cpp,%.o,$(SRC)))

PROGRAM = src/app/pio_periph_test.cpp src/app/pio_periph_test.cpp src/app/uart_periph_test.cpp  src/app/flash_periph_test.cpp src/app/addr_value_test.cpp src/app/i2c_periph_test.cpp src/app/adc_periph_test.cpp src/app/rele_close_test.cpp src/app/scheduler_task_test.cpp

.PHONY = all

all: pio_periph systick_periph uart_periph i2c_periph flash_periph addr_value adc_periph rele_close sched_test
	echo "All done..."
	echo "sudo ${FLASH} -bpv -t atmel_cm4 -f bin/program_to_test.elf.bin"

#############################
#
# Link the executables.
#
############################

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

$(BIN_DIR)addr_value_test.elf: $(BUILD_DIR)src/app/addr_value_test.o $(OBJ)
	mkdir -p $(@D)
	${LD} -g  $(LDFLAGS) $^ -o $@ -Wl,-Map="$(BUILD_DIR)src/app/addr_value_test.map"
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

$(BIN_DIR)flash_periph_test.elf: $(BUILD_DIR)src/app/flash_periph_test.o $(OBJ)
	mkdir -p $(@D)
	${LD} -g  $(LDFLAGS) $^ -o $@ -Wl,-Map="$(BUILD_DIR)src/app/flash_periph_test.map"
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

$(BIN_DIR)i2c_periph_test.elf: $(BUILD_DIR)src/app/i2c_periph_test.o $(OBJ)
	mkdir -p $(@D)
	${LD} -g  $(LDFLAGS) $^ -o $@ -Wl,-Map="$(BUILD_DIR)src/app/i2c_periph_test.map"
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

$(BIN_DIR)adc_periph_test.elf: $(BUILD_DIR)src/app/adc_periph_test.o $(OBJ)
	mkdir -p $(@D)
	${LD} -g  $(LDFLAGS) $^ -o $@ -Wl,-Map="$(BUILD_DIR)src/app/adc_periph_test.map"
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

$(BIN_DIR)rele_close_test.elf: $(BUILD_DIR)src/app/rele_close_test.o $(OBJ)
	mkdir -p $(@D)
	${LD} -g  $(LDFLAGS) $^ -o $@ -Wl,-Map="$(BUILD_DIR)src/app/rele_close_test.map"
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

$(BIN_DIR)sched_test.elf: $(BUILD_DIR)src/app/scheduler_task_test.o $(OBJ)
	mkdir -p $(@D)
	${LD} -g  $(LDFLAGS) $^ -o $@ -Wl,-Map="$(BUILD_DIR)src/app/sched_test.map"
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list
#############################
#
# Object files construction.
#
############################
#
$(BUILD_DIR)src/app/pio_periph_test.o: src/app/pio_periph_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/app/systick_periph_test.o: src/app/systick_periph_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/app/uart_periph_test.o: src/app/uart_periph_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/app/addr_value_test.o: src/app/addr_value_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/app/flash_periph_test.o: src/app/flash_periph_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/app/i2c_periph_test.o: src/app/i2c_periph_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/app/adc_periph_test.o: src/app/adc_periph_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/app/rele_close_test.o: src/app/rele_close_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/app/scheduler_task_test.o: src/app/scheduler_task_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)%.o: %.cpp
	mkdir -p $(@D)
	$(CXX)  $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -c $< -o $@

#############################
#
# Binary files generation
#
############################
pio_periph: $(BIN_DIR)pio_periph_test.elf
	echo "Building PIO  Peripheral Test Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin

systick_periph: $(BIN_DIR)systick_periph_test.elf
	echo "Building SYSTICK  Peripheral Test Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin

uart_periph: $(BIN_DIR)uart_periph_test.elf
	echo "Building UART  Peripheral Test Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin

adc_periph: $(BIN_DIR)adc_periph_test.elf
	echo "Building UART  Peripheral Test Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin

flash_periph: $(BIN_DIR)flash_periph_test.elf
	echo "Building FLASH Peripheral Test Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin

i2c_periph: $(BIN_DIR)i2c_periph_test.elf
	echo "Building I2C Peripheral Test Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin

addr_value: $(BIN_DIR)addr_value_test.elf
	echo "Building FLASH Peripheral Test Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin


rele_close: $(BIN_DIR)rele_close_test.elf
	echo "Building RELE Test Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin

sched_test: $(BIN_DIR)sched_test.elf
	echo "Building Scheduler Test Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin


clean:
	rm bin build -rf
