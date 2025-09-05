// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

use embed_resource::*;

fn main () {
    #[cfg(windows)] embed_resource::compile(
        "manifest.rc",
        embed_resource::NONE
    );
}
