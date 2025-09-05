// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_CHECK_GROUP_H_INCLUDED
#define NUXC_CHECK_GROUP_H_INCLUDED

#include <nux/core.h>

typedef struct nux_check_group_t nux_check_group_t;

NUXC_CONDITIONAL_EXPORT
nux_check_group_t*
nux_check_group_create ();

NUXC_CONDITIONAL_EXPORT
void
nux_check_group_destroy (
    nux_check_group_t* check_group
);

#endif
