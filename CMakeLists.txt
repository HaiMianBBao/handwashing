cmake_minimum_required(VERSION 3.20)
include(cmake/toolchain.cmake)
project(handwashing LANGUAGES C CXX ASM)

# 编译选项配置
set(COMMON_FLAGS "-mcpu=cortex-m3")
list(APPEND COMMON_FLAGS "-mthumb")
list(APPEND COMMON_FLAGS "-specs=nano.specs")
list(APPEND COMMON_FLAGS "-ffunction-sections")
list(APPEND COMMON_FLAGS "-fdata-sections")

add_compile_options(
    ${COMMON_FLAGS}
    -Wall
    "$<$<CONFIG:Debug>:-g;-DDEBUG>"
    "$<$<COMPILE_LANGUAGE:C>:-std=gnu11>"
)

add_link_options(
    ${COMMON_FLAGS}
    -Wl,--gc-sections
    -Wl,-Map=${PROJECT_NAME}.map
    -T${CMAKE_SOURCE_DIR}/STM32F103C8Tx_FLASH.ld
)

# 源文件定义
set(SOURCES
    Core/Src/main.c
    Core/Src/stm32f1xx_it.c
    Core/Src/stm32f1xx_hal_msp.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c
    Core/Src/system_stm32f1xx.c
)

set(ASM_SOURCES
    startup_stm32f103xb.s
)

# 包含目录
include_directories(
    Core/Inc
    Drivers/STM32F1xx_HAL_Driver/Inc
    Drivers/STM32F1xx_HAL_Driver/Inc/Legacy
    Drivers/CMSIS/Device/ST/STM32F1xx/Include
    Drivers/CMSIS/Include
)

# 定义可执行目标
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${ASM_SOURCES})

# 宏定义
target_compile_definitions(${PROJECT_NAME}.elf PUBLIC
    USE_HAL_DRIVER
    STM32F103xB
)

# 链接库
target_link_libraries(${PROJECT_NAME}.elf
    -lc
    -lm
    -lnosys
)

# 构建后生成hex和bin文件
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    COMMENT "Generating HEX and BIN files"
)

# 设置构建类型优化选项
set(CMAKE_C_FLAGS_RELEASE "-Os")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g")
set(CMAKE_ASM_FLAGS_RELEASE "-Os")
set(CMAKE_ASM_FLAGS_DEBUG "-g")