// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/application.h>
#include "handles.hpp"

NUXC_EXTERNC
nux_application_t*
nux_application_create (
    int argc,
    char** argv
) {
    return new nux_application_t{nux::application{argc, argv}};
}

NUXC_EXTERNC
void
nux_application_destroy (
    nux_application_t* application
) {
    delete application;
}

NUXC_EXTERNC
nux_encoding_t
nux_application_get_encoding ()
{
    return nux_impl_map(nux::application::get_encoding());
}

NUXC_EXTERNC
int
nux_application_run (
    nux_application_t* application
) {
    return application->handle.run();
}
