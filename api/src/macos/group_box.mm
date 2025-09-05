// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/group_box.hpp>

#include "macos.hpp"

namespace nux {

// ------------------------------------------------------------ nux::group_box

// Constructors and Destructor ------------------------------------------------

group_box::group_box (
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              enclosing_layout.grab_enclosing_window_handle()
                  .nux_window_handle,
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
              parent_widget_handle.widget_handle,
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

void
group_box::get_preferred_size (
    int& width,
    int& height
)
const noexcept
{
    m_content_layout.get_preferred_size(
        width,
        height
    );
} // function -----------------------------------------------------------------

int
group_box::get_left_overhead ()
const noexcept
{
    return m_content_layout.get_left_margin() * 2 - 1;
} // function -----------------------------------------------------------------

int
group_box::get_right_overhead ()
const noexcept
{
    return m_content_layout.get_right_margin() * 2 - 1;
} // function -----------------------------------------------------------------

int
group_box::get_top_overhead ()
const noexcept
{
    auto nsbox{reinterpret_cast<NSBox*>(grab_native_handle().widget_handle)};
    return m_content_layout.get_top_margin()
        + [nsbox convertRect: [nsbox titleRect] fromView: nil].size.height
        + 10;
} // function -----------------------------------------------------------------

int
group_box::get_bottom_overhead ()
const noexcept
{
    return m_content_layout.get_bottom_margin() - 1;
} // function -----------------------------------------------------------------

nux::string
group_box::get_title ()
const
{
    return impl::to_nux_string(
        [reinterpret_cast<NSBox*>(grab_native_handle().widget_handle)
            title
        ]
    );
} // function -----------------------------------------------------------------

void
group_box::set_title (
    nux::string_view new_title
) {
    [reinterpret_cast<NSBox*>(grab_native_handle().widget_handle) setTitle:
        impl::to_nsstring(new_title)
    ];

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
    m_content_layout.set_top_margin(5);
    m_content_layout.set_left_margin(5);
    m_content_layout.set_right_margin(5);
    m_content_layout.set_bottom_margin(5);
    m_content_layout.set_horizontal_padding(
        m_content_layout.get_left_margin() - 1
        + m_content_layout.get_right_margin() - 1
    );
    m_content_layout.set_vertical_padding(get_vertical_overhead());
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
