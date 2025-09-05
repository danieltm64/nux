// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/label.hpp>

#include "qt.hpp"

namespace nux {

// ---------------------------------------------------------------- nux::label

// Constructors and Destructor ------------------------------------------------

label::label (
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              enclosing_layout.grab_enclosing_window_handle()
                  .nux_main_window_handle,
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
    QSize size_hint{
        static_cast<QLabel*>(
            grab_native_handle().widget_handle
        )->sizeHint()
    };
    width = size_hint.width();
    height = size_hint.height();
} // function -----------------------------------------------------------------

nux::string
label::get_text ()
const
{
    return impl::to_nux_string(
        static_cast<QLabel*>(grab_native_handle().widget_handle)->text()
    );
} // function -----------------------------------------------------------------

void
label::set_text (
    nux::string_view new_text
) {
    static_cast<QLabel*>(grab_native_handle().widget_handle)->setText(
        impl::to_qstring(new_text)
    );

    if (is_dynamically_sized()) {
        apply_preferred_size();
    }
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
