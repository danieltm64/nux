# Copyright (c) 2025 Daniel T. McGinnis
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.31)
project(Nux LANGUAGES C CXX)

add_executable(
    helloc
        src/main.c
)
target_link_libraries(
    helloc
        nux16c
)
set_target_properties(
    helloc PROPERTIES
        LINKER_LANGUAGE C
        C_STANDARD 17
        C_STANDARD_REQUIRED TRUE
        C_EXTENSIONS OFF
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_custom_command(
        TARGET helloc POST_BUILD
            COMMAND mt.exe
                -nologo
                -manifest "${CMAKE_CURRENT_BINARY_DIR}/manifest.manifest"
                -outputresource:"$<TARGET_FILE:helloc>\\;1"
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_link_options(
        helloc PRIVATE
            "LINKER:/MANIFEST:EMBED"
            "LINKER:/MANIFESTINPUT:${CMAKE_CURRENT_BINARY_DIR}/manifest.manifest"
    )
endif ()
