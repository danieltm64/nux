// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

use std::rc::*;
use std::cell::*;
use std::cmp::*;
use std::env;
use nux::WindowElement;
use nux::Widget;

fn handle_close_event (
    window: &mut nux::Window,
    close_event: &mut nux::CloseEvent
) {
    let confirm = "Confirm";
    if window.get_title() != confirm {
        window.set_title(confirm);
        close_event.set_should_close(false);
    }
}

fn main () {
    let mut app = nux::Application::new(env::args().collect());
    println!("Encoding: {}", nux::Application::get_encoding());

    let mut main_window = nux::Window::new(
        "¯\\_(ツ)_/¯",
        800,
        600,
        nux::WindowMode::Standard
    );
    main_window.on_close(handle_close_event);

    let mut root_layout = main_window.grab_root_layout();
    root_layout.set_kind(nux::LayoutKind::Fixed);

    let mut group_box = main_window.grab_root_layout().add_widget::<
        nux::GroupBox
    >();
    group_box.grab_content_layout().set_kind(nux::LayoutKind::Fixed);
    group_box.set_title("Vector Graphics");

    let mut graphics_box = group_box.add_widget::<nux::GraphicsBox>();

    let clear_color = nux::GVector4D::new(1.0, 0.0, 0.0, 1.0);

    let rectangle = nux::VectorPath::build_rectangle(
        10.0,
        10.0,
        80.0,
        80.0,
        10.0
    );
    let gradient_stops1 = vec![
        nux::GradientStop::new(0.0, nux::GVector4D::new(1.0, 0.0, 0.0, 1.0)),
        nux::GradientStop::new(0.5, nux::GVector4D::new(0.0, 1.0, 0.0, 1.0)),
        nux::GradientStop::new(1.0, nux::GVector4D::new(0.0, 0.0, 1.0, 1.0))
    ];
    let linear_gradient_paint = nux::Paint::build_linear_gradient(
        nux::GVector2D::new(0.0, 0.0),
        nux::GVector2D::new(100.0, 100.0),
        &gradient_stops1,
        1.0
    );

    let circle = nux::VectorPath::build_circle(
        50.0,
        50.0,
        25.0
    );
    let gradient_stops2 = vec![
        nux::GradientStop::new(0.0, nux::GVector4D::new(1.0, 1.0, 1.0, 1.0)),
        nux::GradientStop::new(1.0, nux::GVector4D::new(1.0, 1.0, 1.0, 0.0))
    ];
    let radial_gradient_paint = nux::Paint::build_radial_gradient(
        nux::GVector2D::new(50.0, 50.0),
        25.0,
        &gradient_stops2,
        1.0
    );

    let mut label = root_layout.add_widget::<nux::Label>();
    label.set_text("Made in Rust");

    let mut enable_toggle_button = root_layout.add_widget::<nux::CheckBox>();
    enable_toggle_button.set_text("Enable Toggle button");

    let mut toggle_button = root_layout.add_widget::<nux::PushButton>();
    toggle_button.set_text("Toggle");

    let mut group = nux::CheckGroup::new();

    let mut option1 = root_layout.add_radio_button(&group);
    option1.set_text("Yellow Background");

    let mut option2 = root_layout.add_radio_button(&group);
    option2.set_text("Orange Background");

    {
        let enable_toggle_button_clone = enable_toggle_button.clone();
        let toggle_button_clone = toggle_button.clone();
        enable_toggle_button.on_toggle(
            move || {
                toggle_button_clone.set_enabled(enable_toggle_button_clone.is_checked());
            }
        );
    }
    {
        let toggle_button_clone = toggle_button.clone();
        let option1_clone = option1.clone();
        let option2_clone = option2.clone();
        toggle_button.on_trigger(
            move || {
                if (option1_clone.is_checked()) {
                    option2_clone.set_checked(true);
                } else {
                    option1_clone.set_checked(true);
                }
            }
        );
    }
    {
        let option1_clone = option1.clone();
        let clear_color_clone = clear_color.clone();
        option1.on_toggle(
            move || {
                clear_color_clone.set_x(1.0);
                clear_color_clone.set_y(1.0);
                clear_color_clone.set_z(0.0);
                clear_color_clone.set_w(1.0);
            }
        )
    }
    {
        let option2_clone = option2.clone();
        let clear_color_clone = clear_color.clone();
        option2.on_toggle(
            move || {
                clear_color_clone.set_x(1.0);
                clear_color_clone.set_y(0.65);
                clear_color_clone.set_z(0.0);
                clear_color_clone.set_w(1.0);
            }
        )
    }
    {
        let clear_color_clone = clear_color.clone();
        let rectangle_clone = rectangle.clone();
        let linear_gradient_paint_clone = linear_gradient_paint.clone();
        let circle_clone = circle.clone();
        let radial_gradient_paint_clone = radial_gradient_paint.clone();
        let graphics_box_clone = graphics_box.clone();
        graphics_box.on_render(
            move || {
                graphics_box_clone.clear(clear_color_clone.get_x(), clear_color_clone.get_y(), clear_color_clone.get_z(), clear_color_clone.get_w());
                graphics_box_clone.fill_path(&rectangle_clone, &linear_gradient_paint_clone);
                graphics_box_clone.fill_path(&circle_clone, &radial_gradient_paint_clone);
            }
        );
    }

    enable_toggle_button.set_checked(true);
    option1.set_checked(true);

    let mut x = 10;
    let mut y = 0;
    let mut max_width = 0;
    let mut max_height = 0;

    y += 10;
    group_box.set_x(x);
    group_box.set_y(y);
    group_box.set_width(100 + group_box.get_horizontal_overhead());
    group_box.set_height(100 + group_box.get_vertical_overhead());
    y += group_box.get_height();
    max_width = max(max_width, group_box.get_x() + group_box.get_width());
    max_height = max(max_height, group_box.get_y() + group_box.get_height());

    graphics_box.set_x(0);
    graphics_box.set_y(0);
    graphics_box.set_width(100);
    graphics_box.set_height(100);

    y += 10;
    label.set_x(x);
    label.set_y(y);
    y += label.get_height();
    max_width = max(max_width, label.get_x() + label.get_width());
    max_height = max(max_height, label.get_y() + label.get_height());

    x = group_box.get_x() + group_box.get_width() + 10;
    y = 0;

    y += 10;
    enable_toggle_button.set_x(x);
    enable_toggle_button.set_y(y);
    y += enable_toggle_button.get_height();
    max_width = max(max_width, enable_toggle_button.get_x() + enable_toggle_button.get_width());
    max_height = max(max_height, enable_toggle_button.get_y() + enable_toggle_button.get_height());

    y += 10;
    toggle_button.set_x(x);
    toggle_button.set_y(y);
    y += toggle_button.get_height();
    max_width = max(max_width, toggle_button.get_x() + toggle_button.get_width());
    max_height = max(max_height, toggle_button.get_y() + toggle_button.get_height());

    y += 10;
    option1.set_x(x);
    option1.set_y(y);
    y += option1.get_height();
    max_width = max(max_width, option1.get_x() + option1.get_width());
    max_height = max(max_height, option1.get_y() + option1.get_height());

    y += 10;
    option2.set_x(x);
    option2.set_y(y);
    y += option2.get_height();
    max_width = max(max_width, option2.get_x() + option2.get_width());
    max_height = max(max_height, option2.get_y() + option2.get_height());

    main_window.set_size(max_width + 10, max_height + 10);
    main_window.center();
    root_layout.show();
    main_window.show();

    app.run();
}
