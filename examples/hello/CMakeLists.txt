# Copyright (c) 2025 Daniel T. McGinnis
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.31)
project(Nux LANGUAGES C CXX)

add_executable(
    hello
        src/main.cpp
)
target_link_libraries(
    hello
        nux16
)
set_target_properties(
    hello PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_custom_command(
        TARGET hello POST_BUILD
            COMMAND mt.exe
                -nologo
                -manifest "${CMAKE_CURRENT_SOURCE_DIR}/../../api/manifest.manifest"
                -outputresource:"$<TARGET_FILE:hello>\\;1"
            COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE:nux16>
                ${CMAKE_CURRENT_BINARY_DIR}/Debug/$<TARGET_FILE_NAME:nux16>
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_options(
        hello PRIVATE
            "LINKER:/MANIFEST:EMBED"
            "LINKER:/MANIFESTINPUT:${CMAKE_CURRENT_SOURCE_DIR}/../../api/manifest.manifest"
    )
endif ()
