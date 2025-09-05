// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_CLOSE_EVENT_H_INCLUDED
#define NUXC_CLOSE_EVENT_H_INCLUDED

#include <nux/core.h>

typedef struct nux_close_event_t nux_close_event_t;

NUXC_CONDITIONAL_EXPORT
nux_close_event_t*
nux_close_event_create (
    bool initial_should_close
);

NUXC_CONDITIONAL_EXPORT
void
nux_close_event_destroy (
    nux_close_event_t* close_event
);

NUXC_CONDITIONAL_EXPORT
bool
nux_close_event_should_close (
    nux_close_event_t* close_event
);

NUXC_CONDITIONAL_EXPORT
void
nux_close_event_set_should_close (
    nux_close_event_t* close_event,
    bool new_value
);

#endif
