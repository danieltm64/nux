// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_EVENT_H_INCLUDED
#define NUXC_EVENT_H_INCLUDED

#include <nux/core.h>

typedef struct nux_event_t nux_event_t;

typedef NUXC_ENUM(int32_t, nux_event_type_t) {
    NUXC_EVENT_TYPE_KEY_EVENT,
    NUXC_EVENT_TYPE_CLOSE_EVENT,
} nux_event_type_t;


NUXC_CONDITIONAL_EXPORT
nux_event_t*
nux_event_create (
    nux_event_type_t initial_event_type
);

NUXC_CONDITIONAL_EXPORT
void
nux_event_destroy (
    nux_event_t* event
);

NUXC_CONDITIONAL_EXPORT
nux_event_type_t
nux_event_get_event_type (
    nux_event_t* event
);

#endif
