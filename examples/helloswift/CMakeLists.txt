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
    helloswift ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/helloswift
            ${CMAKE_CURRENT_BINARY_DIR}/helloswift
        COMMAND "${CMAKE_CURRENT_BINARY_DIR}/helloswift/build${NUX_SCRIPT_FILE_EXTENSION}"
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/helloswift
        COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:nux8>
            ${CMAKE_CURRENT_BINARY_DIR}/helloswift/.build/debug/$<TARGET_FILE_NAME:nux8>
        COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:nux8c>
            ${CMAKE_CURRENT_BINARY_DIR}/helloswift/.build/debug/$<TARGET_FILE_NAME:nux8c>
)

add_dependencies(
    helloswift
        nuxswift
)
