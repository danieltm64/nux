// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/radio_button.h>
#include "handles.hpp"

NUXC_EXTERNC
nux_radio_button_t*
nux_radio_button_create (
    nux_window_element_t* parent,
    nux_check_group_t* group
) {
    auto element{nux_impl_map(parent)};

    if (
        auto enclosing_layout{dynamic_cast<nux::layout*>(element)};
        enclosing_layout
    ) {
        auto result{
            new nux_radio_button_t{
                nux::radio_button{
                    *enclosing_layout,
                    *reinterpret_cast<nux::check_group<nux::radio_button>*>(
                        &group->handle
                    )
                },
                nux::string{},
                nullptr,
                nullptr
            }
        };
        result->handle.set_toggle_event_handler(
            [result] () {
                if (result->toggle_event_handler) {
                    result->toggle_event_handler(
                        result,
                        result->toggle_event_user_data
                    );
                }
            }
        );
        return result;
    }

    if (
        auto enclosing_group_box{dynamic_cast<nux::group_box*>(element)};
        enclosing_group_box
    ) {
        auto result{
            new nux_radio_button_t{
                nux::radio_button{
                    enclosing_group_box->grab_native_handle(),
                    enclosing_group_box->grab_content_layout(),
                    *reinterpret_cast<nux::check_group<nux::radio_button>*>(
                        &group->handle
                    )
                },
                nux::string{},
                nullptr,
                nullptr
            }
        };
        result->handle.set_toggle_event_handler(
            [result] () {
                if (result->toggle_event_handler) {
                    result->toggle_event_handler(
                        result,
                        result->toggle_event_user_data
                    );
                }
            }
        );
        return result;
    }

    return nullptr;
}

NUXC_EXTERNC
void
nux_radio_button_destroy (
    nux_radio_button_t* radio_button
) {
    delete radio_button;
}

NUXC_EXTERNC
nux_widget_t*
nux_radio_button_upcast (
    nux_radio_button_t* radio_button
) {
    return nux_impl_map(static_cast<nux::widget*>(nux_impl_map(radio_button)));
}

NUXC_EXTERNC
const nuxchar_t*
nux_radio_button_get_text (
    nux_radio_button_t* radio_button,
    int* size
) {
    radio_button->text = radio_button->handle.get_text();
    if (size) {
        *size = radio_button->text.size();
    }
    return reinterpret_cast<const nuxchar_t*>(radio_button->text.data());
}

NUXC_EXTERNC
void
nux_radio_button_set_text (
    nux_radio_button_t* radio_button,
    const nuxchar_t* new_text
) {
    radio_button->handle.set_text(
        reinterpret_cast<nux::string_view::const_pointer>(new_text)
    );
}

NUXC_EXTERNC
bool
nux_radio_button_is_checked (
    nux_radio_button_t* radio_button
) {
    return radio_button->handle.is_checked();
}

NUXC_EXTERNC
void
nux_radio_button_set_checked (
    nux_radio_button_t* radio_button,
    bool checked
) {
    radio_button->handle.set_checked(checked);
}

NUXC_EXTERNC
nux_radio_button_toggle_event_handler_t
nux_radio_button_get_toggle_event_handler (
    nux_radio_button_t* radio_button
) {
    return radio_button->toggle_event_handler;
}

NUXC_EXTERNC
void
nux_radio_button_set_toggle_event_handler (
    nux_radio_button_t* radio_button,
    nux_radio_button_toggle_event_handler_t event_handler,
    void* user_data
) {
    radio_button->toggle_event_handler = event_handler;
    radio_button->toggle_event_user_data = user_data;
}
