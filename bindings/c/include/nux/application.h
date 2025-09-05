// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_APPLICATION_H_INCLUDED
#define NUXC_APPLICATION_H_INCLUDED

#include <nux/encoding.h>

typedef struct nux_application_t nux_application_t;

NUXC_CONDITIONAL_EXPORT
nux_application_t*
nux_application_create (
    int argc,
    char** argv
);

NUXC_CONDITIONAL_EXPORT
void
nux_application_destroy (
    nux_application_t* application
);

NUXC_CONDITIONAL_EXPORT
nux_encoding_t
nux_application_get_encoding ();

NUXC_CONDITIONAL_EXPORT
int
nux_application_run (
    nux_application_t* application
);

#endif
