// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

use std::{env, fs, path};

fn main () {
    let cargo_manifest_dir = std::env::var("CARGO_MANIFEST_DIR").unwrap();
    println!("cargo:rustc-link-search=native={}/..", cargo_manifest_dir);
    println!("cargo:rustc-link-lib=dylib=nux8c");
    let bindings = bindgen::Builder::default()
        .clang_arg("-std=c17")
        .clang_arg("-I../../c/include")
        .clang_arg("-I../../c/exports")
        .clang_arg("-DNUXC_CONFIG_IS_DYNAMIC=true")
        .clang_arg("-DNUXC_STRING_TYPE_STD_U8STRING")
        .header("../../c/include/nux/application.h")
        .header("../../c/include/nux/check_box.h")
        .header("../../c/include/nux/check_group.h")
        .header("../../c/include/nux/close_event.h")
        .header("../../c/include/nux/core.h")
        .header("../../c/include/nux/event.h")
        .header("../../c/include/nux/graphics_box.h")
        .header("../../c/include/nux/group_box.h")
        .header("../../c/include/nux/gvector2d.h")
        .header("../../c/include/nux/gvector3d.h")
        .header("../../c/include/nux/gvector4d.h")
        .header("../../c/include/nux/label.h")
        .header("../../c/include/nux/layout.h")
        .header("../../c/include/nux/paint.h")
        .header("../../c/include/nux/push_button.h")
        .header("../../c/include/nux/radio_button.h")
        .header("../../c/include/nux/vector_path.h")
        .header("../../c/include/nux/widget.h")
        .header("../../c/include/nux/window.h")
        .header("../../c/include/nux/window_element.h")
        .generate()
        .expect("Unable to generate bindings.")
        .write_to_file("src/bindings.rs")
        .expect("Unable to write bindings.")
    ;
    /*
    let out_dir = env::var("OUT_DIR").unwrap();
    fs::copy(
        path::Path::new("../libnuxu8.dylib"),
        path::Path::new(&out_dir).join("libnuxu8.dylib")
    ).unwrap();
    fs::copy(
        path::Path::new("../libnuxu8c.dylib"),
        path::Path::new(&out_dir).join("libnuxu8c.dylib")
    ).unwrap();
    */
}
