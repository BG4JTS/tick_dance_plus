##########################################################################################################################
# Makefile for Tick Dance Project
##########################################################################################################################

######################################
# target
######################################
TARGET = Project

######################################
# building variables
######################################
DEBUG = 1
OPT = -Og

#######################################
# paths
#######################################
BUILD_DIR = build
PROJECT_ROOT = f:/github/tick_dance

######################################
# source
######################################
C_SOURCES = \
$(PROJECT_ROOT)/Src/main.c \
$(PROJECT_ROOT)/Src/py32f0xx_hal_msp.c \
$(PROJECT_ROOT)/Src/py32f0xx_it.c \
$(PROJECT_ROOT)/Src/myAPP_system.c \
$(PROJECT_ROOT)/Src/myAPP_display.c \
$(PROJECT_ROOT)/Src/myAPP_device_init.c \
$(PROJECT_ROOT)/Src/myAPP_button.c \
$(PROJECT_ROOT)/Drivers/CMSIS/Device/PY32F0xx/Source/system_py32f0xx.c \
$(PROJECT_ROOT)/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal.c \
$(PROJECT_ROOT)/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_rcc.c \
$(PROJECT_ROOT)/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_rcc_ex.c \
$(PROJECT_ROOT)/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_flash.c \
$(PROJECT_ROOT)/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_flash_ex.c \
$(PROJECT_ROOT)/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_gpio.c \
$(PROJECT_ROOT)/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_dma.c \
$(PROJECT_ROOT)/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_pwr.c \
$(PROJECT_ROOT)/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_uart.c \
$(PROJECT_ROOT)/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_spi.c \
$(PROJECT_ROOT)/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_cortex.c \
$(PROJECT_ROOT)/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_tim.c \
$(PROJECT_ROOT)/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_tim_ex.c \
$(PROJECT_ROOT)/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_rtc.c \
$(PROJECT_ROOT)/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_rtc_ex.c \
$(PROJECT_ROOT)/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_lptim.c \
$(PROJECT_ROOT)/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_exti.c \
$(PROJECT_ROOT)/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_iwdg.c \
$(PROJECT_ROOT)/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_wwdg.c \
$(PROJECT_ROOT)/Devices/ST7305.c \
$(PROJECT_ROOT)/Fonts/num_trans.c \
$(PROJECT_ROOT)/Fonts/colon_trans.c \
$(PROJECT_ROOT)/ltx/src/ltx.c \
$(PROJECT_ROOT)/ltx/components/app/ltx_app.c \
$(PROJECT_ROOT)/ltx/components/debug/ltx_cmd.c \
$(PROJECT_ROOT)/ltx/components/debug/ltx_param.c \
$(PROJECT_ROOT)/ltx/components/event_group/ltx_event_group.c \
$(PROJECT_ROOT)/ltx/components/lock/ltx_lock.c \
$(PROJECT_ROOT)/ltx/components/log/ltx_log.c \
$(PROJECT_ROOT)/ltx/components/log/SEGGER_RTT.c \
$(PROJECT_ROOT)/ltx/components/log/SEGGER_RTT_printf.c \
$(PROJECT_ROOT)/ltx/components/script/ltx_script.c

ASM_SOURCES = \
startup_py32f030xx.s

#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
GCC_PATH = C:/Users/zzz/.eide/tools/gcc_arm/bin

CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

#######################################
# CFLAGS
#######################################
CPU = -mcpu=cortex-m0plus
MCU = $(CPU) -mthumb

C_DEFS = \
-DUSE_HAL_DRIVER \
-DPY32F030x8

C_INCLUDES = \
-I$(PROJECT_ROOT)/Inc \
-I$(PROJECT_ROOT)/Drivers/CMSIS/Include \
-I$(PROJECT_ROOT)/Drivers/CMSIS/Device/PY32F0xx/Include \
-I$(PROJECT_ROOT)/Drivers/PY32F0xx_HAL_Driver/Inc \
-I$(PROJECT_ROOT)/Devices/Inc \
-I$(PROJECT_ROOT)/Fonts \
-I$(PROJECT_ROOT)/ltx/inc \
-I$(PROJECT_ROOT)/ltx/components/app \
-I$(PROJECT_ROOT)/ltx/components/debug \
-I$(PROJECT_ROOT)/ltx/components/event_group \
-I$(PROJECT_ROOT)/ltx/components/lock \
-I$(PROJECT_ROOT)/ltx/components/log \
-I$(PROJECT_ROOT)/ltx/components/script

ASFLAGS = $(MCU) $(C_DEFS) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections --specs=nosys.specs --specs=nano.specs

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

#######################################
# LDFLAGS
#######################################
LDSCRIPT = py32f030x8.ld
LIBS = -lc -lm -lnosys
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

#######################################
# build
#######################################
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))

vpath %.c $(sort $(dir $(C_SOURCES)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(ASFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir $@

#######################################
# clean
#######################################
clean:
	-rm -fR $(BUILD_DIR)

#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)
