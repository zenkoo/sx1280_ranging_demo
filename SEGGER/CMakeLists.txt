cmake_minimum_required(VERSION 3.0)

project(segger C)

set(SEGGER_SRC ${PROJECT_SOURCE_DIR}/RTT/SEGGER_RTT_ASM_ARMv7M.S)
aux_source_directory(${PROJECT_SOURCE_DIR}/RTT SEGGER_SRC)
add_library(segger STATIC ${SEGGER_SRC})
target_include_directories(segger PRIVATE ${PROJECT_SOURCE_DIR}/RTT)
target_compile_definitions(segger PRIVATE ${STM32_DEF})

