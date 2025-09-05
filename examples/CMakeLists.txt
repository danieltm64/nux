# Copyright (c) 2025 Daniel T. McGinnis
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.31)
project(Nux LANGUAGES C CXX)

add_subdirectory(hello)

if (NUX_BUILD_C)
add_subdirectory(helloc)
endif ()

if (NUX_BUILD_CS)
add_subdirectory(hellocs)
endif ()

if (NUX_BUILD_RS)
add_subdirectory(hellors)
endif ()

if (NUX_BUILD_SWIFT)
add_subdirectory(helloswift)
endif ()
