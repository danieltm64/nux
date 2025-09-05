// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/application.hpp>
#include <nux/window.hpp>
#include <nux/label.hpp>
#include <nux/group_box.hpp>
#include <nux/graphics_box.hpp>
#include <nux/push_button.hpp>
#include <nux/check_box.hpp>
#include <nux/radio_button.hpp>

#include <iostream>

class main_window
    : public nux::window
{
public:
    main_window ()
        : window{
              u"¯\\_(ツ)_/¯",
              800,
              600,
              nux::window_mode::standard
          }
        , m_rectangle{
              nux::vector_path::build_rectangle(
                  10.0f,
                  10.0f,
                  80.0f,
                  80.0,
                  10.0f
              )
          }
        , m_linear_gradient_paint{
              nux::paint::build_linear_gradient(
                  nux::gvector2d<float>{0.0f, 0.0f},
                  nux::gvector2d<float>{100.0f, 100.0f},
                  {
                      { 0.0f, nux::gvector4d<float>{1.0f, 0.0f, 0.0f, 1.0f} },
                      { 0.5f, nux::gvector4d<float>{0.0f, 1.0f, 0.0f, 1.0f} },
                      { 1.0f, nux::gvector4d<float>{0.0f, 0.0f, 1.0f, 1.0f} }
                  }
              )
          }
        , m_circle{
              nux::vector_path::build_circle(50, 50, 25)
          }
        , m_radial_gradient_paint{
              nux::paint::build_radial_gradient(
                  nux::gvector2d<float>{50.0f, 50.0f},
                  25,
                  {
                      { 0.0f, nux::gvector4d<float>{1.0f, 1.0f, 1.0f, 1.0f} },
                      { 1.0f, nux::gvector4d<float>{1.0f, 1.0f, 1.0f, 0.0f} }
                  }
              )
          }
    {
        auto& root_layout{grab_root_layout()};
        root_layout.set_kind(nux::layout::kind::fixed);

        m_group_box = root_layout.add_widget<nux::group_box>();
        m_group_box->set_title(u"Vector Graphics");

        m_group_box->grab_content_layout().set_kind(nux::layout::kind::fixed);

        m_graphics_box = m_group_box->add_widget<nux::graphics_box>();
        m_graphics_box->set_render_event_handler(
            [this] () {
                m_graphics_box->clear(
                    m_clear_color.x,
                    m_clear_color.y,
                    m_clear_color.z,
                    m_clear_color.w
                );
                m_graphics_box->fill_path(m_rectangle, m_linear_gradient_paint);
                m_graphics_box->fill_path(m_circle, m_radial_gradient_paint);
            }
        );

        m_hello_label = root_layout.add_widget<nux::label>();
        m_hello_label->set_text(u"Made in C++");
        m_enable_toggle_button = root_layout.add_widget<nux::check_box>();
        m_enable_toggle_button->set_text(u"Enable Toggle button");
        m_enable_toggle_button->set_toggle_event_handler(
            [this] () {
                m_toggle_button->set_enabled(m_enable_toggle_button->is_checked());
            }
        );

        m_toggle_button = root_layout.add_widget<nux::push_button>();
        m_toggle_button->set_text(u"Toggle");
        m_toggle_button->set_trigger_event_handler(
            [this] () {
                if (m_option1->is_checked()) {
                    m_option2->set_checked(true);
                } else {
                    m_option1->set_checked(true);
                }
            }
        );

        m_option1 = root_layout.add_widget<nux::radio_button>(m_option_group1);
        m_option1->set_text(u"Yellow Background");
        m_option1->set_toggle_event_handler(
            [this] () {
                m_clear_color = {1.0f, 1.0f, 0.0f, 1.0f};
            }
        );

        m_option2 = root_layout.add_widget<nux::radio_button>(m_option_group1);
        m_option2->set_text(u"Orange Background");
        m_option2->set_toggle_event_handler(
            [this] () {
                m_clear_color = {1.0f, 0.65f, 0.0f, 1.0f};
            }
        );

        m_enable_toggle_button->set_checked(true);
        m_option1->set_checked(true);

        int x{10};
        int y{0};
        int max_width{0};
        int max_height{0};

        m_group_box->set_position(x, (y += 10));
        m_group_box->set_size(
            100 + m_group_box->get_horizontal_overhead(),
            100 + m_group_box->get_vertical_overhead()
        );
        y += m_group_box->get_height();
        max_width = std::max(max_width, m_group_box->get_x() + m_group_box->get_width());
        max_height = std::max(max_height, m_group_box->get_y() + m_group_box->get_height());

        m_graphics_box->set_position(0, 0);
        m_graphics_box->set_size(100, 100);

        m_hello_label->set_position(x, (y += 10));
        y += m_hello_label->get_height();
        max_width = std::max(max_width, m_hello_label->get_x() + m_hello_label->get_width());
        max_height = std::max(max_height, m_hello_label->get_y() + m_hello_label->get_height());

        x = m_group_box->get_x() + m_group_box->get_width() + 10;
        y = 0;

        m_enable_toggle_button->set_position(x, y += 10);
        y += m_enable_toggle_button->get_height();
        max_width = std::max(max_width, m_enable_toggle_button->get_x() + m_enable_toggle_button->get_width());
        max_height = std::max(max_height, m_enable_toggle_button->get_y() + m_enable_toggle_button->get_height());

        m_toggle_button->set_position(x, y += 10);
        y += m_toggle_button->get_height();
        max_width = std::max(max_width, m_toggle_button->get_x() + m_toggle_button->get_width());
        max_height = std::max(max_height, m_toggle_button->get_y() + m_toggle_button->get_height());

        m_option1->set_position(x, y += 10);
        y += m_option1->get_height();
        max_width = std::max(max_width, m_option1->get_x() + m_option1->get_width());
        max_height = std::max(max_height, m_option1->get_y() + m_option1->get_height());

        m_option2->set_position(x, y += 10);
        y += m_option2->get_height();
        max_width = std::max(max_width, m_option2->get_x() + m_option2->get_width());
        max_height = std::max(max_height, m_option2->get_y() + m_option2->get_height());

        set_size(max_width + 10, max_height + 10);
        center();
        root_layout.show();
    }

    void
    handle_close_event (
        nux::close_event& ev
    )
    override
    {
        nux::string_view confirm{u"Confirm"};
        if (get_title() != confirm) {
            set_title(confirm);
            ev.set_should_close(false);
        }
    }

private:
    nux::group_box* m_group_box;
    nux::graphics_box* m_graphics_box;
    nux::vector_path m_rectangle;
    nux::paint m_linear_gradient_paint;
    nux::vector_path m_circle;
    nux::paint m_radial_gradient_paint;
    nux::label* m_hello_label;
    nux::check_box* m_enable_toggle_button;
    nux::push_button* m_toggle_button;
    nux::check_group<nux::radio_button> m_option_group1;
    nux::radio_button* m_option1;
    nux::radio_button* m_option2;
    nux::gvector4d<float> m_clear_color;
};

int
main (
    int argc,
    char** argv
) {
    nux::application app{argc, argv};

    if (nux::application::get_encoding() == nux::encoding::utf8) {
        std::cout << "UTF-8" << std::endl;
    } else {
        std::cout << "UTF-16" << std::endl;
    }

    main_window mw;
    mw.show();

    return app.run();
}
