// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/group_box.hpp>

#include "qt.hpp"

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
                  .nux_main_window_handle,
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
              parent_widget_handle.parent_handle, // TODO: Windows uses parent_widget_handle.parent_handle, what's up with that?
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

void
group_box::get_preferred_size (
    int& width,
    int& height
)
const noexcept
{
    m_content_layout.get_preferred_size(width, height);
    width += m_content_layout.get_left_margin()
        + m_content_layout.get_right_margin();
    height += m_content_layout.get_top_margin()
        + m_content_layout.get_bottom_margin();
} // function -----------------------------------------------------------------

nux::string
group_box::get_title ()
const
{
    return impl::to_nux_string(
        static_cast<QGroupBox*>(grab_native_handle().widget_handle)->title()
    );
} // function -----------------------------------------------------------------

void
group_box::set_title (
    nux::string_view new_title
) {
    static_cast<QGroupBox*>(grab_native_handle().widget_handle)->setTitle(
        impl::to_qstring(new_title)
    );

    if (is_dynamically_sized()) {
        apply_preferred_size();
    }
} // function -----------------------------------------------------------------

// Protected functions --------------------------------------------------------

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
    const int margin{20};
    const int half_margin{margin / 2};
    m_content_layout.set_top_margin(margin + half_margin);
    m_content_layout.set_left_margin(half_margin);
    m_content_layout.set_right_margin(half_margin);
    m_content_layout.set_bottom_margin(half_margin);
    m_content_layout.set_horizontal_padding(0);
    m_content_layout.set_vertical_padding(0);
} // function -----------------------------------------------------------------


} // namespace ----------------------------------------------------------------
