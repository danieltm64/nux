# Copyright (c) 2025 Daniel T. McGinnis
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.31)
project(Nux LANGUAGES C CXX)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(
        NUX_SCRIPT_FILE_EXTENSION
            ".bat"
    )
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin" OR ${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(
        NUX_SCRIPT_FILE_EXTENSION
            ".sh"
    )
endif ()
add_custom_target(
    nuxrs ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/nux
            ${CMAKE_CURRENT_BINARY_DIR}/nux
)
add_custom_command(
    TARGET nuxrs POST_BUILD
    COMMAND "./build${NUX_SCRIPT_FILE_EXTENSION}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/nux
)
add_dependencies(
    nuxrs
        nux8c
        nux-bindings
)
