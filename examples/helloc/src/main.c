// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/application.h>
#include <nux/window.h>
#include <nux/label.h>
#include <nux/group_box.h>
#include <nux/graphics_box.h>
#include <nux/push_button.h>
#include <nux/check_box.h>
#include <nux/radio_button.h>

#include <stdio.h>
#include <string.h>

int
max (
    int a,
    int b
) {
    return a > b ? a : b;
}

nux_group_box_t* group_box;
nux_graphics_box_t* graphics_box;
nux_vector_path_t* rectangle;
nux_gvector4d_t* stops_array1_colors[3];
nux_gradient_stop_t* stops_array1[3];
nux_paint_t* linear_gradient_paint;
nux_vector_path_t* circle;
nux_gvector4d_t* stops_array2_colors[2];
nux_gradient_stop_t* stops_array2[2];
nux_paint_t* radial_gradient_paint;
nux_label_t* hello_label;

nux_check_box_t* enable_toggle_button;
nux_push_button_t* toggle_button;
nux_check_group_t* group1;
nux_radio_button_t* option1;
nux_radio_button_t* option2;
float clear_color[4];

void
window_close_event_handler (
    nux_window_t* window,
    nux_close_event_t* ev,
    void* user_data
) {
    NUXC_UNUSED(user_data);
    const nuxchar_t* confirm = u"Confirm";
    if (memcmp(nux_window_get_title(window, NULL), confirm, strlen((const char*)confirm))) {
        nux_window_set_title(window, confirm);
        nux_close_event_set_should_close(ev, false);
    }
}

void
graphics_box_render_event_handler (
    nux_graphics_box_t* graphics_box,
    void* user_data
) {
    NUXC_UNUSED(user_data);
    nux_graphics_box_clear(
        graphics_box,
        clear_color[0],
        clear_color[1],
        clear_color[2],
        clear_color[3]
    );
    nux_graphics_box_fill_path(graphics_box, rectangle, linear_gradient_paint);
    nux_graphics_box_fill_path(graphics_box, circle, radial_gradient_paint);
}

void
check_box_toggle_event_handler (
    nux_check_box_t* check_box,
    void* user_data
) {
    NUXC_UNUSED(user_data);
    nux_widget_set_enabled(NUXC_WIDGET(toggle_button), nux_check_box_is_checked(check_box));
}

void
push_button_trigger_event_handler (
    nux_push_button_t* push_button,
    void* user_data
) {
    NUXC_UNUSED(push_button);
    NUXC_UNUSED(user_data);
    if (nux_radio_button_is_checked(option1)) {
        nux_radio_button_set_checked(option2, true);
    } else {
        nux_radio_button_set_checked(option1, true);
    }
}

void
option1_toggle_event_handler (
    nux_radio_button_t* radio_button,
    void* user_data
) {
    NUXC_UNUSED(radio_button);
    NUXC_UNUSED(user_data);
    clear_color[0] = 1.0f;
    clear_color[1] = 1.0f;
    clear_color[2] = 0.0f;
    clear_color[3] = 1.0f;
}

void
option2_toggle_event_handler (
    nux_radio_button_t* radio_button,
    void* user_data
) {
    NUXC_UNUSED(radio_button);
    NUXC_UNUSED(user_data);
    clear_color[0] = 1.0f;
    clear_color[1] = 0.65f;
    clear_color[2] = 0.0f;
    clear_color[3] = 1.0f;
}

int
main (
    int argc,
    char** argv
) {
    // Initialization:

    nux_application_t* app = nux_application_create(argc, argv);
    nux_encoding_t encoding = nux_application_get_encoding();
    if (encoding == NUXC_ENCODING_UTF8) {
        printf("UTF-8\n");
    } else if (encoding == NUXC_ENCODING_UTF16) {
        printf("UTF-16\n");
    } else {
        printf("Unknown encoding.\n");
    }

    nux_window_t* window = nux_window_create(
        u"¯\\_(ツ)_/¯",
        800,
        600,
        NUXC_WINDOW_MODE_STANDARD
    );
    nux_window_set_close_event_handler(window, window_close_event_handler, NULL);

    nux_layout_t* root_layout = nux_window_grab_root_layout(window);
    nux_layout_set_kind(root_layout, NUXC_LAYOUT_KIND_FIXED);

    group_box = nux_group_box_create(NUXC_WINDOW_ELEMENT(root_layout));
    nux_layout_set_kind(nux_group_box_grab_content_layout(group_box), NUXC_LAYOUT_KIND_FIXED);

    nux_layout_add_widget(root_layout, NUXC_WIDGET(group_box));
    nux_group_box_set_title(group_box, u"Vector Graphics");

    graphics_box = nux_graphics_box_create(NUXC_WINDOW_ELEMENT(group_box));

    rectangle = nux_vector_path_build_rectangle(
        10.0f,
        10.0f,
        80.0f,
        80.0f,
        10.0f
    );
    stops_array1[0] = nux_gradient_stop_create(0.0f, stops_array1_colors[0] = nux_gvector4d_create(1.0f, 0.0f, 0.0f, 1.0f));
    stops_array1[1] = nux_gradient_stop_create(0.5f, stops_array1_colors[1] = nux_gvector4d_create(0.0f, 1.0f, 0.0f, 1.0f));
    stops_array1[2] = nux_gradient_stop_create(1.0f, stops_array1_colors[2] = nux_gvector4d_create(0.0f, 0.0f, 1.0f, 1.0f));
    linear_gradient_paint = nux_paint_build_linear_gradient(
        nux_gvector2d_create(0.0f, 0.0f),
        nux_gvector2d_create(100.0f, 100.0f),
        stops_array1,
        3,
        1.0f
    );

    circle = nux_vector_path_build_circle(50, 50, 25);
    stops_array2[0] = nux_gradient_stop_create(0.0f, stops_array2_colors[0] = nux_gvector4d_create(1.0f, 1.0f, 1.0f, 1.0f));
    stops_array2[1] = nux_gradient_stop_create(1.0f, stops_array2_colors[1] = nux_gvector4d_create(1.0f, 1.0f, 1.0f, 0.0f));
    radial_gradient_paint = nux_paint_build_radial_gradient(
        nux_gvector2d_create(50.0f, 50.0f),
        25,
        stops_array2,
        2,
        1.0f
    );

    nux_graphics_box_set_render_event_handler(graphics_box, graphics_box_render_event_handler, NULL);
    nux_group_box_add_widget(group_box, NUXC_WIDGET(graphics_box));

    hello_label = nux_label_create(NUXC_WINDOW_ELEMENT(root_layout));
    nux_layout_add_widget(root_layout, NUXC_WIDGET(hello_label));
    nux_label_set_text(hello_label, u"Made in C");

    enable_toggle_button = nux_check_box_create(NUXC_WINDOW_ELEMENT(root_layout));
    nux_layout_add_widget(root_layout, NUXC_WIDGET(enable_toggle_button));
    nux_check_box_set_text(enable_toggle_button, u"Enable Toggle button");
    nux_check_box_set_toggle_event_handler(enable_toggle_button, check_box_toggle_event_handler, NULL);

    toggle_button = nux_push_button_create(NUXC_WINDOW_ELEMENT(root_layout));
    nux_layout_add_widget(root_layout, NUXC_WIDGET(toggle_button));
    nux_push_button_set_text(toggle_button, u"Toggle");
    nux_push_button_set_trigger_event_handler(toggle_button, push_button_trigger_event_handler, NULL);

    group1 = nux_check_group_create();

    option1 = nux_radio_button_create(NUXC_WINDOW_ELEMENT(root_layout), group1);
    nux_layout_add_widget(root_layout, NUXC_WIDGET(option1));
    nux_radio_button_set_text(option1, u"Yellow Background");
    nux_radio_button_set_toggle_event_handler(option1, option1_toggle_event_handler, NULL);

    option2 = nux_radio_button_create(NUXC_WINDOW_ELEMENT(root_layout), group1);
    nux_layout_add_widget(root_layout, NUXC_WIDGET(option2));
    nux_radio_button_set_text(option2, u"Orange Background");
    nux_radio_button_set_toggle_event_handler(option2, option2_toggle_event_handler, NULL);

    nux_check_box_set_checked(enable_toggle_button, true);
    nux_radio_button_set_checked(option1, true);

    int x = 10;
    int y = 0;
    int max_width = 0;
    int max_height = 0;

    nux_window_element_set_position(NUXC_WINDOW_ELEMENT(group_box), x, y += 10);
    nux_window_element_set_size(
        NUXC_WINDOW_ELEMENT(group_box),
        100 + nux_window_element_get_horizontal_overhead(NUXC_WINDOW_ELEMENT(group_box)),
        100 + nux_window_element_get_vertical_overhead(NUXC_WINDOW_ELEMENT(group_box))
    );
    y += nux_window_element_get_height(NUXC_WINDOW_ELEMENT(group_box));
    max_width = max(max_width, nux_window_element_get_x(NUXC_WINDOW_ELEMENT(group_box)) + nux_window_element_get_width(NUXC_WINDOW_ELEMENT(group_box)));
    max_height = max(max_height, nux_window_element_get_y(NUXC_WINDOW_ELEMENT(group_box)) + nux_window_element_get_height(NUXC_WINDOW_ELEMENT(group_box)));

    nux_window_element_set_position(NUXC_WINDOW_ELEMENT(graphics_box), 0, 0);
    nux_window_element_set_size(NUXC_WINDOW_ELEMENT(graphics_box), 100, 100);

    nux_window_element_set_position(NUXC_WINDOW_ELEMENT(hello_label), x, (y += 10));
    y += nux_window_element_get_height(NUXC_WINDOW_ELEMENT(hello_label));
    max_width = max(max_width, nux_window_element_get_x(NUXC_WINDOW_ELEMENT(hello_label)) + nux_window_element_get_width(NUXC_WINDOW_ELEMENT(hello_label)));
    max_height = max(max_height, nux_window_element_get_y(NUXC_WINDOW_ELEMENT(hello_label)) + nux_window_element_get_height(NUXC_WINDOW_ELEMENT(hello_label)));

    x = nux_window_element_get_x(NUXC_WINDOW_ELEMENT(group_box)) + nux_window_element_get_width(NUXC_WINDOW_ELEMENT(group_box)) + 10;
    y = 0;

    nux_window_element_set_position(NUXC_WINDOW_ELEMENT(enable_toggle_button), x, y += 10);
    y += nux_window_element_get_height(NUXC_WINDOW_ELEMENT(enable_toggle_button));
    max_width = max(max_width, nux_window_element_get_x(NUXC_WINDOW_ELEMENT(enable_toggle_button)) + nux_window_element_get_width(NUXC_WINDOW_ELEMENT(enable_toggle_button)));
    max_height = max(max_height, nux_window_element_get_y(NUXC_WINDOW_ELEMENT(enable_toggle_button)) + nux_window_element_get_height(NUXC_WINDOW_ELEMENT(enable_toggle_button)));

    nux_window_element_set_position(NUXC_WINDOW_ELEMENT(toggle_button), x, y += 10);
    y += nux_window_element_get_height(NUXC_WINDOW_ELEMENT(toggle_button));
    max_width = max(max_width, nux_window_element_get_x(NUXC_WINDOW_ELEMENT(toggle_button)) + nux_window_element_get_width(NUXC_WINDOW_ELEMENT(toggle_button)));
    max_height = max(max_height, nux_window_element_get_y(NUXC_WINDOW_ELEMENT(toggle_button)) + nux_window_element_get_height(NUXC_WINDOW_ELEMENT(toggle_button)));

    nux_window_element_set_position(NUXC_WINDOW_ELEMENT(option1), x, y += 10);
    y += nux_window_element_get_height(NUXC_WINDOW_ELEMENT(option1));
    max_width = max(max_width, nux_window_element_get_x(NUXC_WINDOW_ELEMENT(option1)) + nux_window_element_get_width(NUXC_WINDOW_ELEMENT(option1)));
    max_height = max(max_height, nux_window_element_get_y(NUXC_WINDOW_ELEMENT(option1)) + nux_window_element_get_height(NUXC_WINDOW_ELEMENT(option1)));

    nux_window_element_set_position(NUXC_WINDOW_ELEMENT(option2), x, y += 10);
    y += nux_window_element_get_height(NUXC_WINDOW_ELEMENT(option2));
    max_width = max(max_width, nux_window_element_get_x(NUXC_WINDOW_ELEMENT(option2)) + nux_window_element_get_width(NUXC_WINDOW_ELEMENT(option2)));
    max_height = max(max_height, nux_window_element_get_y(NUXC_WINDOW_ELEMENT(option2)) + nux_window_element_get_height(NUXC_WINDOW_ELEMENT(option2)));

    nux_window_set_size(window, max_width + 10, max_height + 10);

    nux_window_center(window);
    nux_layout_show(root_layout);

    nux_window_show(window);

    // Run the application
    int result = nux_application_run(app);

    // Cleanup:

    nux_window_destroy(window);
    nux_application_destroy(app);

    nux_check_group_destroy(group1);

    nux_paint_destroy(radial_gradient_paint);
    for (int i = 0; i < 2; ++i) {
        nux_gradient_stop_destroy(stops_array2[i]);
        nux_gvector4d_destroy(stops_array2_colors[i]);
    }
    nux_vector_path_destroy(circle);

    nux_paint_destroy(linear_gradient_paint);
    for (int i = 0; i < 3; ++i) {
        nux_gradient_stop_destroy(stops_array1[i]);
        nux_gvector4d_destroy(stops_array1_colors[i]);
    }
    nux_vector_path_destroy(rectangle);

    // Return what the application object provided
    return result;
}
