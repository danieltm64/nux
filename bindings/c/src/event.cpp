// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/event.h>
#include "handles.hpp"

NUXC_EXTERNC
nux_event_t*
nux_event_create (
    nux_event_type_t initial_event_type
) {
    return new nux_event_t{nux::event{nux_impl_map(initial_event_type)}};
}

NUXC_EXTERNC
void
nux_event_destroy (
    nux_event_t* event
) {
    delete event;
}

NUXC_EXTERNC
nux_event_type_t
nux_event_get_event_type (
    nux_event_t* event
) {
    return nux_impl_map(event->handle.get_event_type());
}
