// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/check_box.h>
#include "handles.hpp"

NUXC_EXTERNC
nux_check_box_t*
nux_check_box_create (
    nux_window_element_t* parent
) {
    auto element{nux_impl_map(parent)};

    if (
        auto enclosing_layout{dynamic_cast<nux::layout*>(element)};
        enclosing_layout
    ) {
        auto result{
            new nux_check_box_t{
                nux::check_box{*enclosing_layout},
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
            new nux_check_box_t{
                nux::check_box{
                    enclosing_group_box->grab_native_handle(),
                    enclosing_group_box->grab_content_layout()
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
nux_check_box_destroy (
    nux_check_box_t* check_box
) {
    delete check_box;
}

NUXC_EXTERNC
nux_widget_t*
nux_check_box_upcast (
    nux_check_box_t* check_box
) {
    return nux_impl_map(static_cast<nux::widget*>(nux_impl_map(check_box)));
}

NUXC_EXTERNC
const nuxchar_t*
nux_check_box_get_text (
    nux_check_box_t* check_box,
    int* size
) {
    check_box->text = check_box->handle.get_text();
    if (size) {
        *size = check_box->text.size();
    }
    return reinterpret_cast<const nuxchar_t*>(check_box->text.data());
}

NUXC_EXTERNC
void
nux_check_box_set_text (
    nux_check_box_t* check_box,
    const nuxchar_t* new_text
) {
    check_box->handle.set_text(
        reinterpret_cast<nux::string_view::const_pointer>(new_text)
    );
}

NUXC_EXTERNC
bool
nux_check_box_is_checked (
    nux_check_box_t* check_box
) {
    return check_box->handle.is_checked();
}

NUXC_EXTERNC
void
nux_check_box_set_checked (
    nux_check_box_t* check_box,
    bool checked
) {
    check_box->handle.set_checked(checked);
}

NUXC_EXTERNC
nux_check_box_toggle_event_handler_t
nux_check_box_get_toggle_event_handler (
    nux_check_box_t* check_box
) {
    return check_box->toggle_event_handler;
}

NUXC_EXTERNC
void
nux_check_box_set_toggle_event_handler (
    nux_check_box_t* check_box,
    nux_check_box_toggle_event_handler_t event_handler,
    void* user_data
) {
    check_box->toggle_event_handler = event_handler;
    check_box->toggle_event_user_data = user_data;
}
