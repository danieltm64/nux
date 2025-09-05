// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include "macos.hpp"

namespace nux {

namespace impl {

NSString*
to_nsstring (
    nux::string_view input
) {
#if defined(NUX_STRING_TYPE_STD_U16STRING)
        return [
            [NSString alloc]
                initWithCharacters: reinterpret_cast<const unichar*>(input.data())
                length: input.size()
        ];
#else
        return [
            NSString stringWithUTF8String:
                reinterpret_cast<const char*>(input.data())
        ];
#endif
} // function -----------------------------------------------------------------

nux::string
to_nux_string (
    NSString* input
) {
#if defined(NUX_STRING_TYPE_STD_U16STRING)
        return reinterpret_cast<const char16_t*>(
            [[input dataUsingEncoding: NSUTF16StringEncoding] bytes]
        ) + 1;
#else
        return reinterpret_cast<nux::string::const_pointer>(
            [input UTF8String]
        );
#endif
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
