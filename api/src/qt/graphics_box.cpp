// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/graphics_box.hpp>

#include "qt.hpp"

namespace nux {

// --------------------------------------------------------- nux::graphics_box

// Constructors and Destructor ------------------------------------------------

graphics_box::graphics_box (
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
          enclosing_layout.grab_enclosing_window_handle().nux_main_window_handle,
              native_widget_kind::graphics_box
          )
      }
{
	initialize();
} // function -----------------------------------------------------------------

graphics_box::graphics_box (
    const widget_native_handle& parent_widget_handle,
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              parent_widget_handle.widget_handle,
              native_widget_kind::graphics_box
          )
      }
{
	initialize();
} // function -----------------------------------------------------------------

graphics_box::~graphics_box ()
noexcept
{
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
graphics_box::clear (
    float red,
    float green,
    float blue,
    float alpha
) {
    auto nux_opengl_widget{
        static_cast<impl::nux_opengl_widget*>(
            grab_native_handle().widget_handle
        )
    };
    nux_opengl_widget->clear(red, green, blue, alpha);
} // function -----------------------------------------------------------------

void
graphics_box::present ()
{
    auto nux_opengl_widget{
        static_cast<impl::nux_opengl_widget*>(
            grab_native_handle().widget_handle
        )
    };
    nux_opengl_widget->glFlush();
} // function -----------------------------------------------------------------

void
graphics_box::render ()
{
} // function -----------------------------------------------------------------

void
graphics_box::handle_resize_event ()
{
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

void
graphics_box::initialize ()
{
    auto nux_opengl_widget{
        static_cast<impl::nux_opengl_widget*>(
            grab_native_handle().widget_handle
        )
    };
    nux_opengl_widget->set_wrapper(this);
    m_graphics_handle = &nux_opengl_widget->graphics_handle;
    m_render_event_handler = impl::noop<>;
} // function -----------------------------------------------------------------

void
graphics_box::render_core ()
{
    auto nux_opengl_widget{
        static_cast<impl::nux_opengl_widget*>(
            grab_native_handle().widget_handle
        )
    };
    QSize size{nux_opengl_widget->size()};
    m_projection = matrix4x4<float>::build_orthographic(
        size.width(),
        size.height()
    );
    m_render_event_handler();
} // function -----------------------------------------------------------------

void
graphics_box::render_path (
    const vector_path& path,
    const paint& render_paint,
    bool fill
) {
    auto nux_opengl_widget{
        static_cast<impl::nux_opengl_widget*>(
            grab_native_handle().widget_handle
        )
    };
    QOpenGLExtraFunctions& qgl{nux_opengl_widget->grab_opengl_functions()};
    const auto& vertices{path.grab_vertices()};
    if (vertices.empty()) {
        return;
    }

    qgl.glUseProgram(m_graphics_handle->shader_program);

    const impl::buffer& path_buffer{path.grab_buffer()};
    if (!path_buffer.is_ready()) {
        path_buffer.upload(*m_graphics_handle, path.grab_vertices());
    }
    qgl.glBindVertexArray(path_buffer.grab_native_handle().vao);

    qgl.glUniformMatrix4fv(
        qgl.glGetUniformLocation(m_graphics_handle->shader_program, "u_projection"),
        1,
        GL_FALSE,
        m_projection.get_data_ptr()
    );

    qgl.glUniform1i(
        qgl.glGetUniformLocation(m_graphics_handle->shader_program, "u_paint_type"),
        static_cast<int>(render_paint.type)
    );
    qgl.glUniform4fv(
        qgl.glGetUniformLocation(m_graphics_handle->shader_program, "u_color"),
        1,
        render_paint.color.get_data_ptr()
    );
    qgl.glUniform1f(
        qgl.glGetUniformLocation(m_graphics_handle->shader_program, "u_opacity"),
        render_paint.global_opacity
    );

    if (render_paint.type != paint_type::solid) {
        gvector2d<float> world_space_gradient_start{
            render_paint.gradient_start + vertices.front()
        };
        gvector2d<float> world_space_gradient_end{
            render_paint.gradient_end + vertices.front()
        };

        gvector2d<float> gradient_direction{world_space_gradient_end - world_space_gradient_start};
        gradient_direction.normalize();

        float minProj = std::numeric_limits<float>::max();
        float maxProj = std::numeric_limits<float>::lowest();
        for (const gvector2d<float>& current_vertex : vertices) {
            float proj{
                dot_product(
                    current_vertex - world_space_gradient_start,
                    gradient_direction
                )
            };
            minProj = std::min(minProj, proj);
            maxProj = std::max(maxProj, proj);
        }

        if (render_paint.type == paint_type::radial_gradient) {
            qgl.glUniform2fv(
                qgl.glGetUniformLocation(m_graphics_handle->shader_program, "u_gradient_start"),
                1,
                render_paint.gradient_start.get_data_ptr()
            );
            qgl.glUniform2fv(
                qgl.glGetUniformLocation(m_graphics_handle->shader_program, "u_gradient_end"),
                1,
                render_paint.gradient_end.get_data_ptr()
            );
        } else {
            qgl.glUniform2fv(
                qgl.glGetUniformLocation(m_graphics_handle->shader_program, "u_gradient_start"),
                1,
                world_space_gradient_start.get_data_ptr()
            );
            qgl.glUniform2fv(
                qgl.glGetUniformLocation(m_graphics_handle->shader_program, "u_gradient_end"),
                1,
                world_space_gradient_end.get_data_ptr()
            );
        }
        qgl.glUniform1f(qgl.glGetUniformLocation(m_graphics_handle->shader_program, "u_proj_min"), minProj);
        qgl.glUniform1f(qgl.glGetUniformLocation(m_graphics_handle->shader_program, "u_proj_max"), maxProj);

        std::vector<gvector4d<float>> colors;
        std::vector<float> stops;
        for (const auto& current_stop : render_paint.gradient_stops) {
            colors.push_back(current_stop.color);
            stops.push_back(current_stop.position);
        }

        qgl.glUniform4fv(
            qgl.glGetUniformLocation(m_graphics_handle->shader_program, "u_gradient_colors"),
            static_cast<GLsizei>(colors.size()),
            reinterpret_cast<const GLfloat*>(colors.data())
        );
        qgl.glUniform1fv(
            qgl.glGetUniformLocation(m_graphics_handle->shader_program, "u_gradient_stops"),
            static_cast<GLsizei>(stops.size()),
            stops.data()
        );
        qgl.glUniform1i(
            qgl.glGetUniformLocation(m_graphics_handle->shader_program, "u_gradient_color_count"),
            static_cast<GLint>(colors.size())
        );
    }

    qgl.glDrawArrays(
        fill ? GL_TRIANGLE_STRIP : GL_LINE_STRIP,
        0,
        static_cast<GLsizei>(path_buffer.get_size())
    );
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
