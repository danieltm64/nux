// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_CORE_H_INCLUDED
#define NUXC_CORE_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>

// Export Macros --------------------------------------------------------------

#if defined(__cplusplus)
#   define NUXC_EXTERNC extern "C"
#else
#   define NUXC_EXTERNC
#endif

#if NUXC_CONFIG_IS_DYNAMIC == true
#   include <nuxc_export.h>
#   define NUXC_CONDITIONAL_EXPORT NUXC_EXTERNC NUXC_EXPORT
#else
#   define NUXC_CONDITIONAL_EXPORT NUXC_EXTERNC
#endif

// Utility Macros -------------------------------------------------------------

#define NUXC_UNUSED(x) ((void)x)

// Character Types ------------------------------------------------------------

#if defined(NUXC_STRING_TYPE_STD_STRING)
typedef char nuxchar_t;
#elif defined(NUXC_STRING_TYPE_STD_U8STRING)
typedef unsigned char nuxchar_t;
#elif defined(NUXC_STRING_TYPE_STD_U16STRING)
typedef uint16_t nuxchar_t;
#endif

// Swift Interop --------------------------------------------------------------

#ifdef NUXC_SWIFT
#define NUXC_ENUM(type, name) enum name : type
#else
#define NUXC_ENUM(type, name) enum name
#endif

#endif
