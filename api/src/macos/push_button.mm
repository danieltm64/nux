// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/push_button.hpp>

#include "macos.hpp"

namespace nux {

// ---------------------------------------------------------- nux::push_button

// Constructors and Destructor ------------------------------------------------

push_button::push_button (
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              enclosing_layout.grab_enclosing_window_handle()
                  .nux_window_handle,
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
    get_preferred_size_generically(
        grab_native_handle(),
        width,
        height
    );
} // function -----------------------------------------------------------------

nux::string
push_button::get_text ()
const
{
    return impl::to_nux_string(
        [reinterpret_cast<NSButton*>(grab_native_handle().widget_handle)
            title
        ]
    );
} // function -----------------------------------------------------------------

void
push_button::set_text (
    nux::string_view new_text
) {
    [reinterpret_cast<NSButton*>(grab_native_handle().widget_handle) setTitle:
        impl::to_nsstring(new_text)
    ];

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
