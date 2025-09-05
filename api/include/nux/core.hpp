// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_CORE_HPP_INCLUDED
#define NUX_CORE_HPP_INCLUDED

// Operating Systems ----------------------------------------------------------

#if defined(_WIN32) \
    || defined(_WIN64) \
    || defined(__WIN32__) \
    || defined(__TOS_WIN__) \
    || defined(__WINDOWS__)

#   define NUX_OS_WINDOWS
#   define NUX_OS_NAME "Windows"

#elif defined(__APPLE__) \
    || defined(__MACH__)

#   define NUX_OS_MACOS
#   define NUX_OS_NAME "macOS"

#elif defined(__linux__) \
|| defined(linux) \
|| defined(__linux)

#   define NUX_OS_LINUX_BASED
#   define NUX_OS_NAME "Linux-based"

#endif

// Compilers ------------------------------------------------------------------

#define NUX_DO_PRAGMA(p) _Pragma(#p)

#if defined(__clang__)

#   define NUX_COMPILER_CLANG
#   define NUX_COMPILER_NAME "Clang"

#   define NUX_DISABLE_WARNING_PUSH NUX_DO_PRAGMA(GCC diagnostic push)
#   define NUX_DISABLE_WARNING_POP NUX_DO_PRAGMA(GCC diagnostic pop)
#   define NUX_DISABLE_WARNING(id) NUX_DO_PRAGMA(GCC diagnostic ignored id)

#   define NUX_WARNING_ID_MACRO_REDEFINED "-Wmacro-redefined"
#   define NUX_WARNING_ID_END_OF_NON_VOID "-Wreturn-type"

#elif defined(__GNUC__)

#   define NUX_COMPILER_GCC
#   define NUX_COMPILER_NAME "GCC"

#   define NUX_DISABLE_WARNING_PUSH NUX_DO_PRAGMA(GCC diagnostic push)
#   define NUX_DISABLE_WARNING_POP NUX_DO_PRAGMA(GCC diagnostic pop)
#   define NUX_DISABLE_WARNING(id) NUX_DO_PRAGMA(GCC diagnostic ignored id)

#   define NUX_WARNING_ID_MACRO_REDEFINED "-Wbuiltin-macro-redefined"
#   define NUX_WARNING_ID_END_OF_NON_VOID "-Wreturn-type"

#elif defined(_MSC_VER)

#   define NUX_COMPILER_MSVC
#   define NUX_COMPILER_NAME "Visual C++"

#   define NUX_DISABLE_WARNING_PUSH NUX_DO_PRAGMA(warning(push))
#   define NUX_DISABLE_WARNING_POP NUX_DO_PRAGMA(warning(pop))
#   define NUX_DISABLE_WARNING(id) NUX_DO_PRAGMA(warning(disable: id))

#   define NUX_WARNING_ID_MACRO_REDEFINED 4005
#   define NUX_WARNING_ID_END_OF_NON_VOID

#else

#   define NUX_COMPILER_UNSUPPORTED
#   define NUX_COMPILER_NAME "<Unsupported>"

#endif

// Export Macros --------------------------------------------------------------

#if NUX_CONFIG_IS_DYNAMIC == true
#   include <nux_export.hpp>
#   define NUX_CONDITIONAL_EXPORT NUX_EXPORT
#else
#   define NUX_CONDITIONAL_EXPORT
#endif

#if defined(NUX_COMPILER_GCC)
#   define NUX_CONDITIONAL_EXPORT_CLASS NUX_CONDITIONAL_EXPORT
#else
#   define NUX_CONDITIONAL_EXPORT_CLASS
#endif

// Utility Macros -------------------------------------------------------------

#define NUX_UNUSED(x)

#endif
