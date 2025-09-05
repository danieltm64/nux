// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/close_event.h>
#include "handles.hpp"

NUXC_EXTERNC
nux_close_event_t*
nux_close_event_create (
    bool initial_should_close
) {
    return new nux_close_event_t{nux::close_event{initial_should_close}};
}

NUXC_EXTERNC
void
nux_close_event_destroy (
    nux_close_event_t* event
) {
    delete event;
}

NUXC_EXTERNC
bool
nux_close_event_should_close (
    nux_close_event_t* close_event
) {
    return close_event->handle.should_close();
}

NUXC_EXTERNC
void
nux_close_event_set_should_close (
    nux_close_event_t* close_event,
    bool new_value
) {
    close_event->handle.set_should_close(new_value);
}
