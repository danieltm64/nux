// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/check_box.hpp>

#include "windows.hpp"

namespace nux {

// ------------------------------------------------------------ nux::check_box

// Constructors and Destructor ------------------------------------------------

check_box::check_box (
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              enclosing_layout.grab_enclosing_window_handle().window_handle,
              native_widget_kind::check_box
          )
      }
{
    initialize();
} // function -----------------------------------------------------------------

check_box::check_box (
    const widget_native_handle& parent_widget_handle,
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              parent_widget_handle.widget_handle,
              native_widget_kind::check_box
          )
      }
{
    initialize();
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

void
check_box::get_preferred_size (
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
check_box::get_text ()
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
check_box::set_text (
    nux::string_view new_text
) {
    std::wstring text_wstring{impl::to_wstring(new_text)};
    SetWindowTextW(grab_native_handle().widget_handle, text_wstring.data());

    if (is_dynamically_sized()) {
        apply_preferred_size();
    }
} // function -----------------------------------------------------------------

bool
check_box::is_checked ()
{
    return Button_GetCheck(grab_native_handle().widget_handle);
} // function -----------------------------------------------------------------

void
check_box::set_checked (
    bool new_checked
) {
    bool old_checked{is_checked()};
    auto handle{grab_native_handle().widget_handle};
    Button_SetCheck(handle, new_checked ? BST_CHECKED : BST_UNCHECKED);
    if (old_checked != new_checked) {
        m_toggle_event_handler();
    }
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

void
check_box::initialize ()
{
    m_toggle_event_handler = impl::noop<>;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
