// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/label.hpp>

#include "windows.hpp"

namespace nux {

// ---------------------------------------------------------------- nux::label

// Constructors and Destructor ------------------------------------------------

label::label (
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              enclosing_layout.grab_enclosing_window_handle().window_handle,
              native_widget_kind::label
          )
      }
{
} // function -----------------------------------------------------------------

label::label (
    const widget_native_handle& parent_widget_handle,
    layout& enclosing_layout
)
    : widget{
        enclosing_layout,
        impl::create_widget(
            parent_widget_handle.widget_handle,
            native_widget_kind::label
        )
    }
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

void
label::get_preferred_size (
    int& width,
    int& height
)
const noexcept
{
    HWND widget_handle{grab_native_handle().widget_handle};
    HDC device_context{GetDC(widget_handle)};
    HFONT current_font{
        reinterpret_cast<HFONT>(
            SendMessageW(widget_handle, WM_GETFONT, 0, 0)
        )
    };
    HFONT old_font{
        static_cast<HFONT>(
            SelectObject(device_context, current_font)
        )
    };

    std::wstring text_wstring;
    text_wstring.resize(
        GetWindowTextLengthW(grab_native_handle().widget_handle)
    );
    GetWindowTextW(
        grab_native_handle().widget_handle,
        text_wstring.data(),
        text_wstring.size() + 1
    );
    SIZE ideal_size;
    GetTextExtentPoint32W(
        device_context,
        text_wstring.data(),
        text_wstring.size(),
        &ideal_size
    );

    SelectObject(device_context, old_font);
    ReleaseDC(widget_handle, device_context);

    auto dpi{get_parent_dpi()};
    width = impl::to_pixval(static_cast<int>(ideal_size.cx), dpi);
    height = impl::to_pixval(static_cast<int>(ideal_size.cy), dpi);
} // function -----------------------------------------------------------------

nux::string
label::get_text ()
const
{
    std::wstring text_wstring;
    text_wstring.resize(
        GetWindowTextLengthW(grab_native_handle().widget_handle)
    );
    GetWindowTextW(
        grab_native_handle().widget_handle,
        text_wstring.data(),
        text_wstring.size() + 1
    );
    return impl::to_nux_string(text_wstring);
} // function -----------------------------------------------------------------

void
label::set_text (
    nux::string_view new_text
) {
    std::wstring text_wstring{impl::to_wstring(new_text)};
    SetWindowTextW(grab_native_handle().widget_handle, text_wstring.data());

    if (is_dynamically_sized()) {
        apply_preferred_size();
    }
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
