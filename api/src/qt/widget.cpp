// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include "qt.hpp"

namespace nux {

namespace impl {

void
debug_callback (
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar *message,
    const void *userParam
) {
    std::cout << message << std::endl;
}

GLuint
compile_shader (
    GLenum type,
    const char* source,
    QOpenGLExtraFunctions& qgl
) {
    GLuint shader{qgl.glCreateShader(type)};
    qgl.glShaderSource(shader, 1, &source, nullptr);
    qgl.glCompileShader(shader);

    GLint success;
    qgl.glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_log[512];
        qgl.glGetShaderInfoLog(shader, 512, nullptr, info_log);
        throw std::runtime_error{
            "Shader compilation error: " + std::string(info_log)
        };
    }
    return shader;
} // function -----------------------------------------------------------------

// ---------------------------------------------- nux::impl::nux_opengl_widget

// Constructors and Destructor ------------------------------------------------

nux_opengl_widget::nux_opengl_widget (
    QWidget* parent
)
    : QOpenGLWidget{parent}
{
} // function -----------------------------------------------------------------

nux_opengl_widget::~nux_opengl_widget ()
{
    makeCurrent();
    doneCurrent();
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

QOpenGLExtraFunctions&
nux_opengl_widget::grab_opengl_functions ()
noexcept
{
    return *this;
} // function -----------------------------------------------------------------

void
nux_opengl_widget::set_wrapper (
    graphics_box* wrapper
)
noexcept
{
    m_wrapper = wrapper;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
nux_opengl_widget::initializeGL ()
{
    initializeOpenGLFunctions();
    graphics_handle.qgl = this;
    connect(
        this,
        &QOpenGLWidget::frameSwapped,
        this,
        static_cast<void (QWidget::*)()>(&QWidget::update)
    );

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
            vertex_shader_source,
            *this
        )
    };
    GLuint fragment_shader{
        impl::compile_shader(
            GL_FRAGMENT_SHADER,
            fragment_shader_source,
            *this
        )
    };

    graphics_handle.shader_program = glCreateProgram();
    glAttachShader(graphics_handle.shader_program, vertex_shader);
    glAttachShader(graphics_handle.shader_program, fragment_shader);
    glLinkProgram(graphics_handle.shader_program);

    GLint success;
    glGetProgramiv(graphics_handle.shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetProgramInfoLog(graphics_handle.shader_program, 512, nullptr, info_log);
        throw std::runtime_error{
            "Shader linking error: " + std::string(info_log)
        };
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glEnable(GL_MULTISAMPLE);
} // function -----------------------------------------------------------------

void
nux_opengl_widget::paintGL ()
{
    m_wrapper->render_core();
} // function -----------------------------------------------------------------

void
nux_opengl_widget::resizeGL (
    int width,
    int height
) {
    glViewport(0, 0, width, height);
} // function -----------------------------------------------------------------

void
nux_opengl_widget::clear (
    float red,
    float green,
    float blue,
    float alpha
) {
    glClearColor(red, green, blue, alpha);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
} // function -----------------------------------------------------------------

widget_native_handle
create_widget (
    QWidget* parent_handle,
    native_widget_kind kind
)
noexcept
{
    QWidget* result;
    switch (kind) {
        case native_widget_kind::label:
            result = new QLabel(parent_handle);
            break;
        case native_widget_kind::push_button:
            result = new QPushButton(parent_handle);
            break;
        case native_widget_kind::check_box:
            result = new QCheckBox(parent_handle);
            break;
        case native_widget_kind::radio_button:
            result = new QRadioButton(parent_handle);
            break;
        case native_widget_kind::graphics_box:
            result = new nux_opengl_widget(parent_handle);
            break;
        case native_widget_kind::group_box:
            result = new QGroupBox(parent_handle);
            break;
    }
    return {parent_handle, result};
} // function -----------------------------------------------------------------

widget*
find_widget (
    QWidget* widget_handle,
    const std::vector<std::unique_ptr<window_element>>& window_elements
) {
    widget* target{nullptr};
    for (const auto& current_window_element : window_elements) {
        auto layout_ptr{dynamic_cast<layout*>(current_window_element.get())};
        if (layout_ptr) {
            target = find_widget(widget_handle, layout_ptr->grab_children());
            if (target) {
                return target;
            }
        } else {
            target = static_cast<widget*>(current_window_element.get());
            if (
                target->grab_native_handle().widget_handle == widget_handle
            ) {
                return target;
            } else {
                auto group_box_ptr{
                    dynamic_cast<group_box*>(current_window_element.get())
                };
                if (group_box_ptr) {
                    target = find_widget(
                        widget_handle,
                        group_box_ptr->grab_content_layout().grab_children()
                    );
                    if (target) {
                        return target;
                    }
                }
            }
        }
    }
    return nullptr;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// --------------------------------------------------------------- nux::widget

// Constructors and Destructor ------------------------------------------------

widget::widget (
    layout& enclosing_layout
)
    : m_native_handle{
          new widget_native_handle{
              enclosing_layout.grab_enclosing_window_handle()
                  .nux_main_window_handle,
              nullptr
          }
      }
    , m_enclosing_layout{&enclosing_layout}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

void
widget::get_position (
    int& x,
    int& y
)
const noexcept
{
    QPoint position{m_native_handle->widget_handle->pos()};
    x = position.x();
    y = position.y();
} // function -----------------------------------------------------------------

void
widget::get_size (
    int& width,
    int& height
)
const noexcept
{
    QSize size{m_native_handle->widget_handle->size()};
    width = size.width();
    height = size.height();
} // function -----------------------------------------------------------------

bool
widget::is_enabled ()
const noexcept
{
    return grab_native_handle().widget_handle->isEnabled();
} // function -----------------------------------------------------------------

void
widget::set_enabled (
    bool new_enabled
)
noexcept
{
    grab_native_handle().widget_handle->setEnabled(new_enabled);
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
widget::show ()
noexcept
{
    m_native_handle->widget_handle->show();
} // function -----------------------------------------------------------------

void
widget::hide ()
noexcept
{
    m_native_handle->widget_handle->hide();
} // function -----------------------------------------------------------------

void
widget::handle_dpi_update_event (
    int NUX_UNUSED(old_dpi),
    int NUX_UNUSED(new_dpi)
) {
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

widget::widget (
    layout& enclosing_layout,
    widget_native_handle&& widget_handle
)
    : m_enclosing_layout{&enclosing_layout}
{
    m_native_handle = new widget_native_handle{std::move(widget_handle)};
} // function -----------------------------------------------------------------

void
widget::set_position_forcefully (
    int new_x,
    int new_y
)
noexcept
{
    QPoint position{new_x, new_y};
    m_native_handle->widget_handle->move(position.x(), position.y());
} // function -----------------------------------------------------------------

void
widget::set_size_forcefully (
    int new_width,
    int new_height
)
noexcept
{
    QSize size{new_width, new_height};
    m_native_handle->widget_handle->resize(size.width(), size.height());
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
