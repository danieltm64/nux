// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/label.h>
#include "handles.hpp"

NUXC_EXTERNC
nux_label_t*
nux_label_create (
    nux_window_element_t* parent
) {
    auto element{nux_impl_map(parent)};

    if (
        auto enclosing_layout{dynamic_cast<nux::layout*>(element)};
        enclosing_layout
    ) {
        auto result{
            new nux_label_t{
                nux::label{*enclosing_layout},
                nux::string{}
            }
        };
        return result;
    }

    if (
        auto enclosing_group_box{dynamic_cast<nux::group_box*>(element)};
        enclosing_group_box
    ) {
        auto result{
            new nux_label_t{
                nux::label{
                    enclosing_group_box->grab_native_handle(),
                    enclosing_group_box->grab_content_layout()
                },
                nux::string{}
            }
        };
        return result;
    }

    return nullptr;
}

NUXC_EXTERNC
void
nux_label_destroy (
    nux_label_t* label
) {
    delete label;
}

NUXC_EXTERNC
nux_widget_t*
nux_label_upcast (
    nux_label_t* label
) {
    return nux_impl_map(static_cast<nux::widget*>(nux_impl_map(label)));
}

NUXC_EXTERNC
const nuxchar_t*
nux_label_get_text (
    nux_label_t* label,
    int* size
) {
    label->text = label->handle.get_text();
    if (size) {
        *size = label->text.size();
    }
    return reinterpret_cast<const nuxchar_t*>(label->text.data());
}

NUXC_EXTERNC
void
nux_label_set_text (
    nux_label_t* label,
    const nuxchar_t* new_text
) {
    label->handle.set_text(
        reinterpret_cast<nux::string_view::const_pointer>(new_text)
    );
}
