cmake_minimum_required(VERSION 3.13)

include(pico-sdk/pico_sdk_init.cmake)

project(pico_uart C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(pico_uart
    src/main.c
    src/shell.c
    src/commands.c
    src/led.c
    src/dht11.c
)
target_include_directories(pico_uart PRIVATE
    include
)

target_link_libraries(pico_uart
    pico_stdlib
)

pico_enable_stdio_usb(pico_uart 1)
pico_enable_stdio_uart(pico_uart 1)

pico_add_extra_outputs(pico_uart)