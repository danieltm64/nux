# Copyright (c) 2025 Daniel T. McGinnis
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.31)
project(Nux LANGUAGES C CXX)

set(NUX_DEV ON)

option(NUX_BUILD_C "Build the C binding and example." ON)
option(NUX_BUILD_CS "Build the C# binding and example." ON)
option(NUX_BUILD_RS "Build the Rust binding and example." ON)
option(NUX_BUILD_SWIFT "Build the Swift binding and example." ON)

add_subdirectory(api)
add_subdirectory(bindings)
add_subdirectory(examples)
