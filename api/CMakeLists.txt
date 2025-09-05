# Copyright (c) 2025 Daniel T. McGinnis
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.31)
project(Nux LANGUAGES C CXX)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    enable_language(OBJCXX)
endif ()

function (add_nux string_type)
    set(
        NUX_SOURCES
            src/definitions.cpp
    )

    include(GenerateExportHeader)

    if (string_type STREQUAL "std::u16string")
        set(nux nux16)
    else ()
        set(nux nux8)
    endif ()

    add_library(
        ${nux} SHARED
            ${NUX_SOURCES}
    )
    target_include_directories(
        ${nux} PUBLIC
            include
            ${PROJECT_BINARY_DIR}/exports
    )
    set_target_properties(
        ${nux} PROPERTIES
            LINKER_LANGUAGE CXX
            CXX_STANDARD 23
            CXX_STANDARD_REQUIRED TRUE
            CXX_EXTENSIONS OFF
            PREFIX "lib"
    )
    target_compile_definitions(
        ${nux} PUBLIC
            NUX_CONFIG_IS_STATIC=false
            NUX_CONFIG_IS_DYNAMIC=true
    )
    generate_export_header(
        ${nux}
            EXPORT_FILE_NAME exports/nux_export.hpp
            BASE_NAME NUX
    )
    include(CheckIPOSupported)
    check_ipo_supported(RESULT lto_supported OUTPUT lto_support_error)
    if (lto_supported)
        set_target_properties(
            ${nux} PROPERTIES
                INTERPROCEDURAL_OPTIMIZATION TRUE
        )
    endif ()
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(
            ${nux} PUBLIC
                /W4
                #/WX
        )
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(
            ${nux} PUBLIC
                -Wall
                -Wextra
                -Wuninitialized
                -pedantic
                #-Werror
                -fanalyzer
        )
    else ()
        target_compile_options(
            ${nux} PUBLIC
                -Wall
                -Wextra
                -Wuninitialized
                -pedantic
                #-Werror
                -Wno-deprecated-declarations
                #--analyze
        )
    endif ()

    if (${string_type} STREQUAL "std::string")
        target_compile_definitions(
            ${nux} PUBLIC
                NUX_STRING_TYPE_STD_STRING
        )
    elseif (${string_type} STREQUAL "std::u8string")
        target_compile_definitions(
            ${nux} PUBLIC
                NUX_STRING_TYPE_STD_U8STRING
        )
    elseif (${string_type} STREQUAL "std::u16string")
        target_compile_definitions(
            ${nux} PUBLIC
                NUX_STRING_TYPE_STD_U16STRING
        )
    else ()
        message(
            SEND_ERROR
                "The string_type variable has the value '${string_type}' "
                "but it can only take on the values "
                "'std::string', 'std::u8string' and 'std::u16string'."
        )
    endif ()
    message(STATUS "The nux::string alias is set to ${string_type}.")

    string(TOUPPER ${CMAKE_SYSTEM_PROCESSOR} NUXCS_RID_PROCESSOR)
    if (${NUXCS_RID_PROCESSOR} MATCHES "^(AARCH64|ARM64)")
        set(
            NUXCS_RID_PROCESSOR
                "arm64"
        )
    elseif (${NUXCS_RID_PROCESSOR} MATCHES "^(X86_64|AMD64)")
        set(
            NUXCS_RID_PROCESSOR
                "x64"
        )
    else ()
        message(
            SEND_ERROR
                "You are trying to build Nux on an "
                "unsupported processor architecture. "
                "You are currently on '${CMAKE_SYSTEM_PROCESSOR}'."
        )
    endif ()

    if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        set(
            NUXCS_RID_OPERATING_SYSTEM
                "win"
        )
        target_link_libraries(
            ${nux} PUBLIC
                comctl32
                d3d11
                dxgi
                dxguid
                d3dcompiler
        )
        if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
            target_compile_options(
                ${nux} PUBLIC
                    /utf-8
            )
        endif ()
    elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(
            NUXCS_RID_OPERATING_SYSTEM
                "osx"
        )
        target_link_libraries(
            ${nux} PUBLIC
                "-framework AppKit"
                "-framework OpenGL"
        )
        set_source_files_properties(
            src/definitions.cpp PROPERTIES
                LANGUAGE OBJCXX
        )
    elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        set(
            NUXCS_RID_OPERATING_SYSTEM
                "linux"
        )
        find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)
        target_link_libraries(
            ${nux}
                Qt6::Core
                Qt6::Gui
                Qt6::Widgets
                Qt6::OpenGLWidgets
        )
    else ()
        message(
            SEND_ERROR
                "You are trying to build Nux on an unsupported operating system. "
                "You are currently on '${CMAKE_SYSTEM_NAME}'."
        )
    endif ()

    add_custom_command(
        TARGET ${nux} POST_BUILD
            # For C# binding:
            COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE:${nux}>
                ${CMAKE_CURRENT_BINARY_DIR}/../bindings/cs/Nux/runtimes/${NUXCS_RID_OPERATING_SYSTEM}-${NUXCS_RID_PROCESSOR}/native/$<TARGET_FILE_NAME:${nux}>
            # For Rust binding:
            COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE:${nux}>
                ${CMAKE_CURRENT_BINARY_DIR}/../bindings/rs/$<TARGET_FILE_NAME:${nux}>
            COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_LINKER_FILE:${nux}>
                ${CMAKE_CURRENT_BINARY_DIR}/../bindings/rs/$<TARGET_LINKER_FILE_NAME:${nux}>
            # For C++ example:
            COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE:${nux}>
                ${CMAKE_CURRENT_BINARY_DIR}/../examples/hello/$<TARGET_FILE_NAME:${nux}>
            # For C example:
            COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE:${nux}>
                ${CMAKE_CURRENT_BINARY_DIR}/../examples/helloc/$<TARGET_FILE_NAME:${nux}>
            COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/manifest.manifest
                ${CMAKE_CURRENT_BINARY_DIR}/../examples/helloc/manifest.manifest
            # For C# example:
            COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/manifest.manifest
                ${CMAKE_CURRENT_BINARY_DIR}/../examples/hellocs/hellocs/manifest.manifest
            # For Rust example:
            COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE:${nux}>
                ${CMAKE_CURRENT_BINARY_DIR}/../examples/hellors/hellors/target/debug/$<TARGET_FILE_NAME:${nux}>
            COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/manifest.manifest
                ${CMAKE_CURRENT_BINARY_DIR}/../examples/hellors/hellors/manifest.manifest
            COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/manifest.rc
                ${CMAKE_CURRENT_BINARY_DIR}/../examples/hellors/hellors/manifest.rc
            # For Swift example:
            COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/manifest.manifest
                ${CMAKE_CURRENT_BINARY_DIR}/../examples/helloswift/helloswift/manifest.manifest
    )
endfunction()

add_nux("std::u16string")
add_nux("std::u8string")
