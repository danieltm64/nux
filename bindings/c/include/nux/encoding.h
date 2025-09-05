// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_ENCODING_H_INCLUDED
#define NUXC_ENCODING_H_INCLUDED

#include <nux/core.h>

typedef NUXC_ENUM(int32_t, nux_encoding_t) {
    NUXC_ENCODING_UTF8,
    NUXC_ENCODING_UTF16
} nux_encoding_t;

#endif
