// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/push_button.hpp>

#include "windows.hpp"

namespace nux {

// ---------------------------------------------------------- nux::push_button

// Constructors and Destructor ------------------------------------------------

push_button::push_button (
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              enclosing_layout.grab_enclosing_window_handle().window_handle,
              native_widget_kind::push_button
          )
      }
{
    initialize();
} // function -----------------------------------------------------------------

push_button::push_button (
    const widget_native_handle& parent_widget_handle,
    layout& enclosing_layout
)
    : widget{
        enclosing_layout,
        impl::create_widget(
            parent_widget_handle.widget_handle,
            native_widget_kind::push_button
        )
    }
{
    initialize();
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

void
push_button::get_preferred_size (
    int& width,
    int& height
)
const noexcept
{
    SIZE ideal_size{0L, 0L};
    Button_GetIdealSize(grab_native_handle().widget_handle, &ideal_size);
    auto dpi{get_parent_dpi()};
    width = impl::to_pixval(static_cast<int>(ideal_size.cx), dpi) + 16;
    height = impl::to_pixval(static_cast<int>(ideal_size.cy), dpi) + 8;
} // function -----------------------------------------------------------------

nux::string
push_button::get_text ()
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
push_button::set_text (
    nux::string_view new_text
) {
    std::wstring text_wstring{impl::to_wstring(new_text)};
    SetWindowTextW(grab_native_handle().widget_handle, text_wstring.data());

    if (is_dynamically_sized()) {
        apply_preferred_size();
    }
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

void
push_button::initialize ()
{
    m_trigger_event_handler = impl::noop<>;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
