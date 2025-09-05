# Copyright (c) 2025 Daniel T. McGinnis
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.31)
project(Nux LANGUAGES C CXX)

add_custom_target(
    hellocs ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/hellocs
            ${CMAKE_CURRENT_BINARY_DIR}/hellocs
)

add_dependencies(
    hellocs
        nuxcs
)
