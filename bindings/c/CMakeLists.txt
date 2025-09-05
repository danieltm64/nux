# Copyright (c) 2025 Daniel T. McGinnis
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.31)
project(Nux LANGUAGES C CXX)

function (add_nuxc string_type)
    include(GenerateExportHeader)

    if (string_type STREQUAL "std::u16string")
        set(nux nux16)
        set(nuxc nux16c)
    else ()
        set(nux nux8)
        set(nuxc nux8c)
    endif ()

    add_library(
        ${nuxc} SHARED
            src/definitions.cpp
    )
    target_include_directories(
        ${nuxc} PUBLIC
            include
            ${PROJECT_BINARY_DIR}/exports
    )
    set_target_properties(
        ${nuxc} PROPERTIES
            LINKER_LANGUAGE CXX
            CXX_STANDARD 23
            CXX_STANDARD_REQUIRED TRUE
            CXX_EXTENSIONS OFF
            PREFIX "lib"
    )
    target_compile_definitions(
        ${nuxc} PUBLIC
            NUXC_CONFIG_IS_STATIC=false
            NUXC_CONFIG_IS_DYNAMIC=true
    )
    target_link_libraries(
        ${nuxc} PUBLIC
            ${nux}
    )
    generate_export_header(
        ${nuxc}
            EXPORT_FILE_NAME exports/nuxc_export.h
            BASE_NAME NUXC
    )
    add_dependencies(
        ${nuxc}
            nux-bindings
    )
    check_ipo_supported(RESULT lto_supported OUTPUT lto_support_error)
    if (lto_supported)
        set_target_properties(
            ${nuxc} PROPERTIES
                INTERPROCEDURAL_OPTIMIZATION TRUE
        )
    endif ()

    if (${string_type} STREQUAL "std::string")
        target_compile_definitions(
            ${nuxc} PUBLIC
                NUXC_STRING_TYPE_STD_STRING
        )
    elseif (${string_type} STREQUAL "std::u8string")
        target_compile_definitions(
            ${nuxc} PUBLIC
                NUXC_STRING_TYPE_STD_U8STRING
        )
    elseif (${string_type} STREQUAL "std::u16string")
        target_compile_definitions(
            ${nuxc} PUBLIC
                NUXC_STRING_TYPE_STD_U16STRING
        )
    else ()
        message(
            SEND_ERROR
                "The string_type variable has the value '${string_type}' "
                "but it can only take on the values "
                "'std::string', 'std::u8string' and 'std::u16string'."
        )
    endif ()

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
    elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(
            NUXCS_RID_OPERATING_SYSTEM
                "osx"
        )
    elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        set(
            NUXCS_RID_OPERATING_SYSTEM
                "linux"
        )
    else ()
        message(
            SEND_ERROR
                "You are trying to build Nux on an unsupported operating system. "
                "You are currently on '${CMAKE_SYSTEM_NAME}'."
        )
    endif ()

    add_custom_command(
        TARGET ${nuxc} POST_BUILD
            # For C# binding:
            COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE:${nuxc}>
                ${CMAKE_CURRENT_BINARY_DIR}/../cs/Nux/runtimes/${NUXCS_RID_OPERATING_SYSTEM}-${NUXCS_RID_PROCESSOR}/native/$<TARGET_FILE_NAME:${nuxc}>
            # For Rust binding:
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/include
                ${CMAKE_CURRENT_BINARY_DIR}/include
            COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE:${nuxc}>
                ${CMAKE_CURRENT_BINARY_DIR}/../rs/$<TARGET_FILE_NAME:${nuxc}>
            COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_LINKER_FILE:${nuxc}>
                ${CMAKE_CURRENT_BINARY_DIR}/../rs/$<TARGET_LINKER_FILE_NAME:${nuxc}>
            # For Swift binding:
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/include
                ${CMAKE_CURRENT_BINARY_DIR}/../swift/Nux/vendor/include
            COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_LINKER_FILE:${nuxc}>
                ${CMAKE_CURRENT_BINARY_DIR}/../swift/Nux/vendor/$<TARGET_LINKER_FILE_NAME:${nuxc}>
            # For C example:
            COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE:nux8>
                ${CMAKE_CURRENT_BINARY_DIR}/../../examples/helloc/Debug/$<TARGET_FILE_NAME:nux8>
            COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE:nux16>
                ${CMAKE_CURRENT_BINARY_DIR}/../../examples/helloc/Debug/$<TARGET_FILE_NAME:nux16>
            COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE:${nuxc}>
                ${CMAKE_CURRENT_BINARY_DIR}/../../examples/helloc/Debug/$<TARGET_FILE_NAME:${nuxc}>
            COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE:${nuxc}>
                ${CMAKE_CURRENT_BINARY_DIR}/../../examples/helloc/$<TARGET_FILE_NAME:${nuxc}>
            # For Rust example:
            COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE:${nuxc}>
                ${CMAKE_CURRENT_BINARY_DIR}/../../examples/hellors/hellors/target/debug/$<TARGET_FILE_NAME:${nuxc}>
            # For Swift example:
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/include
                ${CMAKE_CURRENT_BINARY_DIR}/../../examples/helloswift/helloswift/vendor/include
            COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_LINKER_FILE:${nuxc}>
                ${CMAKE_CURRENT_BINARY_DIR}/../../examples/helloswift/helloswift/vendor/$<TARGET_LINKER_FILE_NAME:${nuxc}>
    )
endfunction()

add_nuxc("std::u16string")
add_nuxc("std::u8string")
