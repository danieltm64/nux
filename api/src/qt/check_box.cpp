// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/check_box.hpp>

#include "qt.hpp"

namespace nux {

// ------------------------------------------------------------ nux::check_box

// Constructors and Destructor ------------------------------------------------

check_box::check_box (
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              enclosing_layout.grab_enclosing_window_handle()
                  .nux_main_window_handle,
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
    QSize size_hint{
        static_cast<QCheckBox*>(
            grab_native_handle().widget_handle
        )->sizeHint()
    };
    width = size_hint.width();
    height = size_hint.height();
} // function -----------------------------------------------------------------

nux::string
check_box::get_text ()
const
{
    return impl::to_nux_string(
        static_cast<QCheckBox*>(grab_native_handle().widget_handle)->text()
    );
} // function -----------------------------------------------------------------

void
check_box::set_text (
    nux::string_view new_text
) {
    static_cast<QCheckBox*>(grab_native_handle().widget_handle)->setText(
        impl::to_qstring(new_text)
    );

    if (is_dynamically_sized()) {
        apply_preferred_size();
    }
} // function -----------------------------------------------------------------

bool
check_box::is_checked ()
{
    return static_cast<QCheckBox*>(grab_native_handle().widget_handle)
        ->isChecked();
} // function -----------------------------------------------------------------

void
check_box::set_checked (
    bool new_checked
) {
    static_cast<QCheckBox*>(grab_native_handle().widget_handle)
        ->setChecked(new_checked);
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
check_box::initialize ()
{
    m_toggle_event_handler = impl::noop<>;
    QObject::connect(
        static_cast<QCheckBox*>(grab_native_handle().widget_handle),
        &QCheckBox::toggled,
        [this] () {
            m_toggle_event_handler();
        }
    );
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
