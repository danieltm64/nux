// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/group_box.hpp>

#include "windows.hpp"

namespace nux {

namespace impl {

int
calculate_top_margin (
    HWND widget_handle
)
noexcept
{
    auto font_handle{
        reinterpret_cast<HFONT>(
            SendMessage(widget_handle, WM_GETFONT, 0, 0)
        )
    };

    HDC device_context{GetDC(widget_handle)};
    auto old_font_handle{
        reinterpret_cast<HFONT>(
            font_handle
                ? SelectObject(device_context, font_handle)
                : nullptr
        )
    };

    TEXTMETRIC tm;
    GetTextMetrics(device_context, &tm);

    if (old_font_handle) {
        SelectObject(device_context, old_font_handle);
    }
    ReleaseDC(widget_handle, device_context);

    auto dpi{GetDpiForWindow(widget_handle)};

    return to_pixval(tm.tmHeight, dpi);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// ------------------------------------------------------------ nux::group_box

// Constructors and Destructor ------------------------------------------------

group_box::group_box (
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              enclosing_layout.grab_enclosing_window_handle().window_handle,
              native_widget_kind::group_box
          )
      }
    , m_content_layout{
          enclosing_layout.grab_enclosing_window_handle(),
          layout::kind::flow,
          layout::axis::vertical,
          layout::direction::forward
      }
{
    initialize();
} // function -----------------------------------------------------------------

group_box::group_box (
    const widget_native_handle& parent_widget_handle,
    layout& enclosing_layout
)
    : widget{
        enclosing_layout,
        impl::create_widget(
            parent_widget_handle.parent_handle,
            native_widget_kind::group_box
        )
    }
    , m_content_layout{
          enclosing_layout.grab_enclosing_window_handle(),
          layout::kind::flow,
          layout::axis::vertical,
          layout::direction::forward
      }
{
    initialize();
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

void
group_box::get_preferred_size (
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

int
group_box::get_left_overhead ()
const noexcept
{
    return m_content_layout.get_left_margin();
} // function -----------------------------------------------------------------

int
group_box::get_right_overhead ()
const noexcept
{
    return m_content_layout.get_right_margin();
} // function -----------------------------------------------------------------

int
group_box::get_top_overhead ()
const noexcept
{
    return m_content_layout.get_top_margin();
} // function -----------------------------------------------------------------

int
group_box::get_bottom_overhead ()
const noexcept
{
    return m_content_layout.get_bottom_margin();
} // function -----------------------------------------------------------------

nux::string
group_box::get_title ()
const
{
    std::wstring title_wstring;
    title_wstring.resize(
        GetWindowTextLengthW(grab_native_handle().widget_handle)
    );
    GetWindowTextW(
        grab_native_handle().widget_handle,
        title_wstring.data(),
        title_wstring.size() + 1
    );
    return impl::to_nux_string(title_wstring);
} // function -----------------------------------------------------------------

void
group_box::set_title (
    nux::string_view new_title
) {
    std::wstring title_wstring{impl::to_wstring(new_title)};
    SetWindowTextW(grab_native_handle().widget_handle, title_wstring.data());

    if (is_dynamically_sized()) {
        apply_preferred_size();
    }
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

void
group_box::set_size_forcefully (
    int new_width,
    int new_height
)
noexcept
{
    widget::set_size_forcefully(new_width, new_height);
    m_content_layout.set_size_forcefully(new_width, new_height);
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

void
group_box::initialize ()
noexcept
{
    m_content_layout.set_top_margin(
        impl::calculate_top_margin(grab_native_handle().widget_handle)
    );
    m_content_layout.set_left_margin(4);
    m_content_layout.set_right_margin(4);
    m_content_layout.set_bottom_margin(4);
    m_content_layout.set_horizontal_padding(0);
    m_content_layout.set_vertical_padding(0);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
