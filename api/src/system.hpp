// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/core.hpp>

#if defined(NUX_OS_WINDOWS)
#   include "windows/windows.hpp"
#elif defined(NUX_OS_MACOS)
#   include "macos/macos.hpp"
#elif defined(NUX_OS_LINUX_BASED)
#   include "qt/qt.hpp"
#endif
