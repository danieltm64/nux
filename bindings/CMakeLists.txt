# Copyright (c) 2025 Daniel T. McGinnis
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.31)
project(Nux LANGUAGES C CXX)

if (NUX_BUILD_C OR NUX_BUILD_CS OR NUX_BUILD_RS OR NUX_BUILD_SWIFT)
    add_custom_target(
        nux-bindings ALL
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/../api/include
                ${CMAKE_CURRENT_BINARY_DIR}/../api/include
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/../api/src
                ${CMAKE_CURRENT_BINARY_DIR}/../api/src
            COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/../api/manifest.manifest
                ${CMAKE_CURRENT_BINARY_DIR}/manifest.manifest
            COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/../api/manifest.rc
                ${CMAKE_CURRENT_BINARY_DIR}/manifest.rc
    )
    add_subdirectory(c)
endif ()

if (NUX_BUILD_CS)
    add_subdirectory(cs)
endif ()

if (NUX_BUILD_RS)
    add_subdirectory(rs)
endif ()

if (NUX_BUILD_SWIFT)
    add_subdirectory(swift)
endif ()
