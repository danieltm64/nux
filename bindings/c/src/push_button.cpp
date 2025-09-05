// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/push_button.h>
#include "handles.hpp"

NUXC_EXTERNC
nux_push_button_t*
nux_push_button_create (
    nux_window_element_t* parent
) {
    auto element{nux_impl_map(parent)};

    if (
        auto enclosing_layout{dynamic_cast<nux::layout*>(element)};
        enclosing_layout
    ) {
        auto result{
            new nux_push_button_t{
                nux::push_button{*enclosing_layout},
                nux::string{},
                nullptr,
                nullptr
            }
        };
        result->handle.set_trigger_event_handler(
            [result] () {
                if (result->trigger_event_handler) {
                    result->trigger_event_handler(
                        result,
                        result->trigger_event_user_data
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
            new nux_push_button_t{
                nux::push_button{
                    enclosing_group_box->grab_native_handle(),
                    enclosing_group_box->grab_content_layout()
                },
                nux::string{},
                nullptr,
                nullptr
            }
        };
        result->handle.set_trigger_event_handler(
            [result] () {
                if (result->trigger_event_handler) {
                    result->trigger_event_handler(
                        result,
                        result->trigger_event_user_data
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
nux_push_button_destroy (
    nux_push_button_t* push_button
) {
    delete push_button;
}

NUXC_EXTERNC
nux_widget_t*
nux_push_button_upcast (
    nux_push_button_t* push_button
) {
    return nux_impl_map(static_cast<nux::widget*>(nux_impl_map(push_button)));
}

NUXC_EXTERNC
const nuxchar_t*
nux_push_button_get_text (
    nux_push_button_t* push_button,
    int* size
) {
    push_button->text = push_button->handle.get_text();
    if (size) {
        *size = push_button->text.size();
    }
    return reinterpret_cast<const nuxchar_t*>(push_button->text.data());
}

NUXC_EXTERNC
void
nux_push_button_set_text (
    nux_push_button_t* push_button,
    const nuxchar_t* new_text
) {
    push_button->handle.set_text(
        reinterpret_cast<nux::string_view::const_pointer>(new_text)
    );
}

NUXC_EXTERNC
nux_push_button_trigger_event_handler_t
nux_push_button_get_trigger_event_handler (
    nux_push_button_t* push_button
) {
    return push_button->trigger_event_handler;
}

NUXC_EXTERNC
void
nux_push_button_set_trigger_event_handler (
    nux_push_button_t* push_button,
    nux_push_button_trigger_event_handler_t event_handler,
    void* user_data
) {
    push_button->trigger_event_handler = event_handler;
    push_button->trigger_event_user_data = user_data;
}
