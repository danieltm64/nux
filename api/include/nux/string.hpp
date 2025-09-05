// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_STRING_HPP_INCLUDED
#define NUX_STRING_HPP_INCLUDED

#include <nux/core.hpp>

#include <string>
#include <string_view>

namespace nux {

#if defined(NUX_STRING_TYPE_STD_STRING)

using string = std::string;
using string_view = std::string_view;

#elif defined(NUX_STRING_TYPE_STD_U8STRING)

using string = std::u8string;
using string_view = std::u8string_view;

#elif defined(NUX_STRING_TYPE_STD_U16STRING)

using string = std::u16string;
using string_view = std::u16string_view;

#else

static_assert(false, "You must define the string type that Nux will use.");

#endif

using char_t = nux::string::value_type;

} // namespace ----------------------------------------------------------------

#endif
