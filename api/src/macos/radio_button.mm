// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/radio_button.hpp>

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
                  .nux_window_handle,
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
    get_preferred_size_generically(
        grab_native_handle(),
        width,
        height
    );
} // function -----------------------------------------------------------------

nux::string
radio_button::get_text ()
const
{
    return impl::to_nux_string(
        [reinterpret_cast<NSButton*>(grab_native_handle().widget_handle)
            title
        ]
    );
} // function -----------------------------------------------------------------

void
radio_button::set_text (
    nux::string_view new_text
) {
    [reinterpret_cast<NSButton*>(grab_native_handle().widget_handle) setTitle:
        impl::to_nsstring(new_text)
    ];

    if (is_dynamically_sized()) {
        apply_preferred_size();
    }
} // function -----------------------------------------------------------------

bool
radio_button::is_checked ()
{
    auto nsbutton{
        reinterpret_cast<NSButton*>(grab_native_handle().widget_handle)
    };
    return [nsbutton state]
        == NSControlStateValueOn;
} // function -----------------------------------------------------------------

void
radio_button::set_checked (
    bool new_checked
) {
    bool old_checked{is_checked()};
    auto nsbutton{
        reinterpret_cast<NSButton*>(grab_native_handle().widget_handle)
    };
    NSControlStateValue new_state{
        new_checked
            ? NSControlStateValueOn
            : NSControlStateValueOff
    };
    [nsbutton setState: new_state];
    if (new_checked) {
        m_group.set_active_element(*this);
    }
    if (old_checked != new_checked) {
        m_toggle_event_handler();
    }
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

void
radio_button::initialize ()
{
    m_toggle_event_handler = impl::noop<>;
    m_group.grab_elements().push_back(this);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
