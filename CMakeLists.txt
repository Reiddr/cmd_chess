cmake_minimum_required(VERSION 3.10)

project(cmd-chess C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Werror)
include_directories(include)

add_library(termdraw STATIC
    src/term_draw.c
)

add_executable(main
    src/main.c
)

target_link_libraries(main termdraw)

set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set_target_properties(termdraw PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
