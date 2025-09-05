// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/radio_button.hpp>

#include "qt.hpp"

namespace nux {

// --------------------------------------------------------- nux::radio_button

// Constructors and Destructor ------------------------------------------------

radio_button::radio_button (
    layout& enclosing_layout,
    check_group<radio_button>& group
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              enclosing_layout.grab_enclosing_window_handle()
                  .nux_main_window_handle,
              native_widget_kind::radio_button
          )
      }
    , m_group{group}
{
    initialize();
} // function -----------------------------------------------------------------

radio_button::radio_button (
    const widget_native_handle& parent_widget_handle,
    layout& enclosing_layout,
    check_group<radio_button>& group
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              parent_widget_handle.widget_handle,
              native_widget_kind::radio_button
          )
      }
    , m_group{group}
{
    initialize();
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

void
radio_button::get_preferred_size (
    int& width,
    int& height
)
const noexcept
{
    QSize size_hint{
        static_cast<QRadioButton*>(
            grab_native_handle().widget_handle
        )->sizeHint()
    };
    width = size_hint.width();
    height = size_hint.height();
} // function -----------------------------------------------------------------

nux::string
radio_button::get_text ()
const
{
    return impl::to_nux_string(
        static_cast<QRadioButton*>(grab_native_handle().widget_handle)->text()
    );
} // function -----------------------------------------------------------------

void
radio_button::set_text (
    nux::string_view new_text
) {
    static_cast<QRadioButton*>(grab_native_handle().widget_handle)->setText(
        impl::to_qstring(new_text)
    );

    if (is_dynamically_sized()) {
        apply_preferred_size();
    }
} // function -----------------------------------------------------------------

bool
radio_button::is_checked ()
{
    return static_cast<QRadioButton*>(grab_native_handle().widget_handle)
        ->isChecked();
} // function -----------------------------------------------------------------

void
radio_button::set_checked (
    bool new_checked
) {
    static_cast<QRadioButton*>(grab_native_handle().widget_handle)
        ->setChecked(new_checked);
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

void
radio_button::initialize ()
{
    m_toggle_event_handler = impl::noop<>;
    QObject::connect(
        static_cast<QRadioButton*>(grab_native_handle().widget_handle),
        &QRadioButton::toggled,
        [this] () {
            m_toggle_event_handler();
        }
    );
    m_group.grab_elements().push_back(this);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
