// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include "windows.hpp"

namespace nux {

namespace impl {

std::wstring
to_wstring (
    nux::string_view input
) {
#if defined(NUX_STRING_TYPE_STD_U16STRING)
        return std::wstring{reinterpret_cast<const wchar_t*>(input.data())};
#else
        if (input.empty()) {
            return std::wstring{};
        }

        int utf16_length{
            MultiByteToWideChar(
                CP_UTF8,
                MB_ERR_INVALID_CHARS,
                reinterpret_cast<const char*>(input.data()),
                -1,
                NULL,
                0
            )
        };

        wchar_t* utf16_buffer{
            static_cast<wchar_t*>(malloc(utf16_length * sizeof(wchar_t)))
        };
        if (!utf16_buffer) {
            return std::wstring{};
        }

        MultiByteToWideChar(
            CP_UTF8,
            MB_ERR_INVALID_CHARS,
            reinterpret_cast<const char*>(input.data()),
            -1,
            utf16_buffer,
            utf16_length
        );
        std::wstring result{utf16_buffer};
        free(utf16_buffer);

        return result;
#endif
} // function -----------------------------------------------------------------

nux::string
to_nux_string (
    std::wstring_view input
) {
#if defined(NUX_STRING_TYPE_STD_U16STRING)
        return nux::string{
            reinterpret_cast<nux::string::const_pointer>(input.data())
        };
#else
        if (input.empty()) {
            return nux::string{};
        }

        int utf8_length{
            WideCharToMultiByte(
                CP_UTF8,
                WC_ERR_INVALID_CHARS,
                input.data(),
                -1,
                NULL,
                0,
                NULL,
                NULL
            )
        };

        auto utf8_buffer{static_cast<char*>(malloc(utf8_length))};
        if (!utf8_buffer) {
            return nux::string{};
        }

        WideCharToMultiByte(
            CP_UTF8,
            WC_ERR_INVALID_CHARS,
            input.data(),
            -1,
            utf8_buffer,
            utf8_length,
            NULL,
            NULL
        );
        nux::string result{
            reinterpret_cast<nux::string::const_pointer>(
                utf8_buffer
            )
        };
        free(utf8_buffer);

        return result;
#endif
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
