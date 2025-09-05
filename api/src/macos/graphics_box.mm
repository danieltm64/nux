// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/graphics_box.hpp>

#include "macos.hpp"

namespace nux {

namespace impl {

NSOpenGLView*
get_nsopenglview (
    graphics_box* gb
) {
	return static_cast<NSOpenGLView*>(gb->grab_native_handle().widget_handle);
} // function -----------------------------------------------------------------

GLuint
compile_shader (
    GLenum type,
    const char* source
) {
    GLuint shader{glCreateShader(type)};
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetShaderInfoLog(shader, 512, nullptr, info_log);
        throw std::runtime_error{
            "Shader compilation error: " + std::string(info_log)
        };
    }
    return shader;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// --------------------------------------------------------- nux::graphics_box

// Constructors and Destructor ------------------------------------------------

graphics_box::graphics_box (
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              enclosing_layout.grab_enclosing_window_handle()
                  .nux_window_handle,
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
    glDeleteBuffers(1, &m_graphics_handle->m_vbo);
    glDeleteVertexArrays(1, &m_graphics_handle->m_vao);
    glDeleteProgram(m_graphics_handle->m_shader_program);
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
graphics_box::clear (
    float red,
    float green,
    float blue,
    float alpha
) {
    auto opengl_view{impl::get_nsopenglview(this)};
    [[opengl_view openGLContext] makeCurrentContext];
    glClearColor(red, green, blue, alpha);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
} // function -----------------------------------------------------------------

void
graphics_box::present ()
{
    auto opengl_view{impl::get_nsopenglview(this)};
	[[opengl_view openGLContext] makeCurrentContext];
    [[opengl_view openGLContext] flushBuffer];
} // function -----------------------------------------------------------------

void
graphics_box::render ()
{
    auto opengl_view{impl::get_nsopenglview(this)};
	[[opengl_view openGLContext] makeCurrentContext];
    NSSize size{[opengl_view bounds].size};
    m_projection = matrix4x4<float>::build_orthographic(
        size.width,
        size.height
    );
    m_render_event_handler();
    [[opengl_view openGLContext] flushBuffer];
} // function -----------------------------------------------------------------

void
graphics_box::handle_resize_event ()
{
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

void
graphics_box::initialize ()
{
    m_graphics_handle = new graphics_native_handle;

    m_render_event_handler = impl::noop<>;

	auto opengl_view{impl::get_nsopenglview(this)};
	[[opengl_view openGLContext] makeCurrentContext];

    // Configure Blending:

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Configure Shaders:

    const char* vertex_shader_source = R"glsl(
#version 400 core
layout(location = 0) in vec2 position;

out vec2 v_world_position;

uniform mat4 u_projection;

void main()
{
    v_world_position = position;
    gl_Position = u_projection * vec4(position, 0.0, 1.0);
}
)glsl";

    const char* fragment_shader_source = R"glsl(
#version 400 core

in vec2 v_world_position;

out vec4 FragColor;

uniform vec4 u_color;
uniform int u_paint_type;
uniform vec2 u_gradient_start;
uniform vec2 u_gradient_end;
uniform vec4 u_gradient_colors[8];
uniform float u_gradient_stops[8];
uniform int u_gradient_color_count;
uniform float u_opacity;
uniform float u_proj_min;
uniform float u_proj_max;

vec4 sampleGradient(float t) {
    vec4 finalColor = u_gradient_colors[0];
    for (int i = 0; i < u_gradient_color_count - 1; i++) {
        float currentStop = u_gradient_stops[i];
        float nextStop = u_gradient_stops[i + 1];
        if (t >= currentStop && t <= nextStop) {
            float segmentT = (t - currentStop) / (nextStop - currentStop);
            finalColor = mix(u_gradient_colors[i], u_gradient_colors[i + 1], segmentT);
            break;
        }
    }
    if (t > u_gradient_stops[u_gradient_color_count - 1]) {
        finalColor = u_gradient_colors[u_gradient_color_count - 1];
    }
    return finalColor;
}

vec4 sampleLinearGradient() {
    vec2 gradDir = u_gradient_end - u_gradient_start;
    float gradLength = length(gradDir);
    if (gradLength < 0.001) {
        return u_gradient_colors[0];
    }
    vec2 gradNorm = gradDir / gradLength;
    float proj = dot(v_world_position - u_gradient_start, gradNorm);
    float t = clamp((proj - u_proj_min) / (u_proj_max - u_proj_min), 0.0, 1.0);
    return sampleGradient(t);
}

vec4 sampleRadialGradient() {
    if (u_gradient_color_count == 1) {
        return u_gradient_colors[0];
    }
    float distance = length(v_world_position - u_gradient_start);
    float gradientRadius = u_gradient_end.x;
    if (distance > gradientRadius) {
        return vec4(0, 0, 0, 0);
    }
    float t = clamp(distance / gradientRadius, 0.0, 1.0);
    return sampleGradient(t);
}

void main()
{
    vec4 color;
    switch (u_paint_type) {
        case 0:
            color = u_color;
            break;
        case 1:
            color = sampleLinearGradient();
            break;
        case 2:
            color = sampleRadialGradient();
            break;
    }
    FragColor = vec4(color.rgb, color.a * u_opacity);
}
)glsl";
    GLuint vertex_shader{
        impl::compile_shader(
            GL_VERTEX_SHADER,
            vertex_shader_source
        )
    };
    GLuint fragment_shader{
        impl::compile_shader(
            GL_FRAGMENT_SHADER,
            fragment_shader_source
        )
    };

    m_graphics_handle->m_shader_program = glCreateProgram();
    glAttachShader(m_graphics_handle->m_shader_program, vertex_shader);
    glAttachShader(m_graphics_handle->m_shader_program, fragment_shader);
    glLinkProgram(m_graphics_handle->m_shader_program);

    GLint success;
    glGetProgramiv(m_graphics_handle->m_shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetProgramInfoLog(m_graphics_handle->m_shader_program, 512, nullptr, info_log);
        throw std::runtime_error{
            "Shader linking error: " + std::string(info_log)
        };
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // Configure Buffers:

    glGenVertexArrays(1, &m_graphics_handle->m_vao);
    glGenBuffers(1, &m_graphics_handle->m_vbo);

    glBindVertexArray(m_graphics_handle->m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_graphics_handle->m_vbo);

    glVertexAttribPointer(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        2 * sizeof (float),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_MULTISAMPLE);

    GLint surfaceOpacity{0};
    [[opengl_view openGLContext] setValues: &surfaceOpacity forParameter: NSOpenGLCPSurfaceOpacity];
} // function -----------------------------------------------------------------

void
graphics_box::render_path (
    const vector_path& path,
    const paint& render_paint,
    bool fill
) {
    const auto& vertices{path.grab_vertices()};
    if (vertices.empty()) {
        return;
    }

    glUseProgram(m_graphics_handle->m_shader_program);

    const impl::buffer& path_buffer{path.grab_buffer()};
    if (!path_buffer.is_ready()) {
        path_buffer.upload(*m_graphics_handle, path.grab_vertices());
    }
    glBindVertexArray(path_buffer.grab_native_handle().vao);

    glUniformMatrix4fv(
        glGetUniformLocation(m_graphics_handle->m_shader_program, "u_projection"),
        1,
        GL_FALSE,
        m_projection.get_data_ptr()
    );

    glUniform1i(
        glGetUniformLocation(m_graphics_handle->m_shader_program, "u_paint_type"),
        static_cast<int>(render_paint.type)
    );
    glUniform4fv(
        glGetUniformLocation(m_graphics_handle->m_shader_program, "u_color"),
        1,
        render_paint.color.get_data_ptr()
    );
    glUniform1f(
        glGetUniformLocation(m_graphics_handle->m_shader_program, "u_opacity"),
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
            glUniform2fv(
                glGetUniformLocation(m_graphics_handle->m_shader_program, "u_gradient_start"),
                1,
                render_paint.gradient_start.get_data_ptr()
            );
            glUniform2fv(
                glGetUniformLocation(m_graphics_handle->m_shader_program, "u_gradient_end"),
                1,
                render_paint.gradient_end.get_data_ptr()
            );
        } else {
            glUniform2fv(
                glGetUniformLocation(m_graphics_handle->m_shader_program, "u_gradient_start"),
                1,
                world_space_gradient_start.get_data_ptr()
            );
            glUniform2fv(
                glGetUniformLocation(m_graphics_handle->m_shader_program, "u_gradient_end"),
                1,
                world_space_gradient_end.get_data_ptr()
            );
        }
        glUniform1f(glGetUniformLocation(m_graphics_handle->m_shader_program, "u_proj_min"), minProj);
        glUniform1f(glGetUniformLocation(m_graphics_handle->m_shader_program, "u_proj_max"), maxProj);

        std::vector<gvector4d<float>> colors;
        std::vector<float> stops;
        for (const auto& current_stop : render_paint.gradient_stops) {
            colors.push_back(current_stop.color);
            stops.push_back(current_stop.position);
        }

        glUniform4fv(
            glGetUniformLocation(m_graphics_handle->m_shader_program, "u_gradient_colors"),
            static_cast<GLsizei>(colors.size()),
            reinterpret_cast<const GLfloat*>(colors.data())
        );
        glUniform1fv(
            glGetUniformLocation(m_graphics_handle->m_shader_program, "u_gradient_stops"),
            static_cast<GLsizei>(stops.size()),
            stops.data()
        );
        glUniform1i(
            glGetUniformLocation(m_graphics_handle->m_shader_program, "u_gradient_color_count"),
            static_cast<GLint>(colors.size())
        );
    }

    glDrawArrays(
        fill ? GL_TRIANGLE_STRIP : GL_LINE_STRIP,
        0,
        static_cast<GLsizei>(vertices.size())
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
} // function -------------------------------------------------------------

} // namespace ----------------------------------------------------------------
