// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/group_box.h>
#include "handles.hpp"
#include "../include/nux/core.h"

NUXC_EXTERNC
nux_group_box_t*
nux_group_box_create (
    nux_window_element_t* parent
) {
    auto element{nux_impl_map(parent)};

    if (
        auto enclosing_layout{dynamic_cast<nux::layout*>(element)};
        enclosing_layout
    ) {
        auto result{
            new nux_group_box_t{
                nux::group_box{*enclosing_layout},
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
            new nux_group_box_t{
                nux::group_box{
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
nux_group_box_destroy (
    nux_group_box_t* group_box
) {
    delete group_box;
}

NUXC_EXTERNC
nux_widget_t*
nux_group_box_upcast (
    nux_group_box_t* group_box
) {
    return nux_impl_map(static_cast<nux::widget*>(nux_impl_map(group_box)));
}

NUXC_EXTERNC
nux_layout_t*
nux_group_box_grab_content_layout (
    nux_group_box_t* group_box
) {
    return nux_impl_map(group_box->handle.grab_content_layout());
}

NUXC_EXTERNC
const nuxchar_t*
nux_group_box_get_title (
    nux_group_box_t* group_box,
    int* size
) {
    group_box->title = group_box->handle.get_title();
    if (size) {
        *size = group_box->title.size();
    }
    return reinterpret_cast<const nuxchar_t*>(group_box->title.data());
}

NUXC_EXTERNC
void
nux_group_box_set_title (
    nux_group_box_t* group_box,
    const nuxchar_t* new_title
) {
    group_box->handle.set_title(
        reinterpret_cast<nux::string_view::const_pointer>(new_title)
    );
}

NUXC_EXTERNC
void
nux_group_box_add_widget (
    nux_group_box_t* group_box,
    nux_widget_t* child
) {
    auto& content_layout_handle{nux_impl_map(group_box)->grab_content_layout()};
    auto child_handle{nux_impl_map(child)};
    content_layout_handle.grab_children().push_back(
        std::unique_ptr<nux::widget>{child_handle}
    );
    content_layout_handle.update();
}
