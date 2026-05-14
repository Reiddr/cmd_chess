cmake_minimum_required(VERSION 3.10)
project(cmd-chess C)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra)
include_directories(include)

set(CMAKE_C_EXTENSIONS OFF)

# Build the static library libtermdraw.a
add_library(termdraw STATIC
    src/term_draw.c
)

# Build the main executable
add_executable(main
    src/main.c
)

# Link the library to the executable
target_link_libraries(main termdraw)

# Output directories similar to your Makefile
set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set_target_properties(termdraw PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
