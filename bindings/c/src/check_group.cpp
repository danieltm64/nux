// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/check_group.h>
#include "handles.hpp"

NUXC_EXTERNC
nux_check_group_t*
nux_check_group_create ()
{
    return new nux_check_group_t{nux::check_group<nux::widget>{}};
}

NUXC_EXTERNC
void
nux_check_group_destroy (
    nux_check_group_t *check_group
) {
    delete check_group;
}
