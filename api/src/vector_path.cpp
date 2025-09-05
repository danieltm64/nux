// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/vector_path.hpp>

#include "system.hpp"

namespace nux {

namespace impl {

buffer_native_handle&
buffer::grab_native_handle ()
noexcept
{
    return *m_native_handle;
} // function -----------------------------------------------------------------

const buffer_native_handle&
buffer::grab_native_handle ()
const noexcept
{
    return *m_native_handle;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// ---------------------------------------------------------- nux::vector_path

// Core -----------------------------------------------------------------------

void
vector_path::begin_path (
    float x,
    float y
) {
    move_to(x, y);
} // function -----------------------------------------------------------------

void
vector_path::line_to (
    float x,
    float y
) {
    m_commands.push_back(
        {
            path_command_type::line_to,
            gvector2d<float>{x, y},
            {},
            {}
        }
    );
} // function -----------------------------------------------------------------

void
vector_path::quad_to (
    float cx,
    float cy,
    float x,
    float y
) {
    m_commands.push_back(
        {
            path_command_type::quad_to,
            gvector2d<float>{x, y},
            gvector2d<float>{cx, cy},
            {}
        }
    );
} // function -----------------------------------------------------------------

void
vector_path::cubic_to (
    float cx1,
    float cy1,
    float cx2,
    float cy2,
    float x,
    float y
) {
    m_commands.push_back(
        {
            path_command_type::cubic_to,
            gvector2d<float>(x, y),
            gvector2d<float>(cx1, cy1),
            gvector2d<float>(cx2, cy2)
        }
    );
} // function -----------------------------------------------------------------

void
vector_path::close ()
{
    m_commands.push_back(
        {
            path_command_type::close,
            {},
            {},
            {}
        }
    );
} // function -----------------------------------------------------------------

void
vector_path::end_path ()
{
    tessellate();
    convert_fan_to_strip();
} // function -----------------------------------------------------------------

vector_path
vector_path::build_rectangle (
    float x,
    float y,
    float width,
    float height,
    float radius
) {
    vector_path result;
    if (radius == 0.0f) {
        result.begin_path(x, y);
        result.line_to(x + width, y);
        result.line_to(x + width, y + height);
        result.line_to(x, y + height);
        result.close();
        result.end_path();
    } else {
        radius = std::min<float>(radius, std::min<float>(width, height) * 0.5f);
        const float kappa_radius = 0.5522848f * radius;

        result.begin_path(x + radius, y);
        result.line_to(x + width - radius, y);
        result.cubic_to(
            x + width - radius + kappa_radius,
            y,
            x + width,
            y + radius - kappa_radius,
            x + width,
            y + radius
        );
        result.line_to(x + width, y + height - radius);
        result.cubic_to(
            x + width,
            y + height - radius + kappa_radius,
            x + width - radius + kappa_radius,
            y + height,
            x + width - radius,
            y + height
        );
        result.line_to(x + radius, y + height);
        result.cubic_to(
            x + radius - kappa_radius,
            y + height,
            x,
            y + height - radius + kappa_radius,
            x,
            y + height - radius
        );
        result.line_to(x, y + radius);
        result.cubic_to(
            x,
            y + radius - kappa_radius,
            x + radius - kappa_radius,
            y,
            x + radius,
            y
        );
        result.close();
        result.end_path();
    }
    return result;
} // function -----------------------------------------------------------------

vector_path
vector_path::build_circle (
    float center_x,
    float center_y,
    float radius
) {
    constexpr float kappa = 0.5522848f;
    const float kappa_radius = kappa * radius;
    vector_path result;
    result.begin_path(center_x + radius, center_y);
    result.cubic_to(
        center_x + radius,
        center_y + kappa_radius,
        center_x + kappa_radius,
        center_y + radius,
        center_x,
        center_y + radius
    );
    result.cubic_to(
        center_x - kappa_radius,
        center_y + radius,
        center_x - radius,
        center_y + kappa_radius,
        center_x - radius,
        center_y
    );
    result.cubic_to(
        center_x - radius,
        center_y - kappa_radius,
        center_x - kappa_radius,
        center_y - radius,
        center_x,
        center_y - radius
    );
    result.cubic_to(
        center_x + kappa_radius,
        center_y - radius,
        center_x + radius,
        center_y - kappa_radius,
        center_x + radius,
        center_y
    );
    result.close();
    result.end_path();
    return result;
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

const std::vector<gvector2d<float>>&
vector_path::grab_vertices ()
const
{
    return m_tessellated_vertices;
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

void
vector_path::move_to (
    float x,
    float y
) {
    m_commands.push_back(
        {
            path_command_type::move_to,
            gvector2d<float>{x, y},
            {},
            {}
        }
    );
} // function -----------------------------------------------------------------

void
vector_path::tessellate ()
{
    gvector2d<float> current_position{0.0f, 0.0f};
    gvector2d<float> start_position{0.0f, 0.0f};

    for (const auto& current_command : m_commands) {
        switch (current_command.type) {
            case path_command_type::move_to: {
                current_position = start_position = current_command.point;
                m_tessellated_vertices.push_back(current_position);
                break;
            }
            case path_command_type::line_to: {
                m_tessellated_vertices.push_back(current_command.point);
                current_position = current_command.point;
                break;
            }
            case path_command_type::quad_to: {
                tessellate_quadratic(
                    current_position,
                    current_command.control1,
                    current_command.point
                );
                current_position = current_command.point;
                break;
            }
            case path_command_type::cubic_to: {
                tessellate_cubic(
                    current_position,
                    current_command.control1,
                    current_command.control2,
                    current_command.point
                );
                current_position = current_command.point;
                break;
            }
            case path_command_type::close: {
                if (
                    distance_between(current_position, start_position)
                        > 0.001f
                ) {
                    m_tessellated_vertices.push_back(start_position);
                }
                break;
            }
        }
    }
} // function -----------------------------------------------------------------

void
vector_path::tessellate_quadratic (
    const gvector2d<float>& p0,
    const gvector2d<float>& p1,
    const gvector2d<float>& p2
) {
    const int segments = 20;
    for (int i = 1; i <= segments; ++i) {
        float t = static_cast<float>(i) / segments;
        float u = 1.0f - t;
        gvector2d<float> point{
            u * u * p0
                + 2.0f * u * t * p1
                + t * t * p2
        };
        m_tessellated_vertices.push_back(point);
    }
} // function -----------------------------------------------------------------

void
vector_path::tessellate_cubic (
    const gvector2d<float>& p0,
    const gvector2d<float>& p1,
    const gvector2d<float>& p2,
    const gvector2d<float>& p3
) {
    const int segments = 30;
    for (int i = 1; i <= segments; ++i) {
        float t = static_cast<float>(i) / segments;
        float u = 1.0f - t;
        gvector2d<float> point{
            u * u * u * p0
                + 3.0f * u * u * t * p1
                + 3.0f * u * t * t * p2
                + t * t * t * p3
        };
        m_tessellated_vertices.push_back(point);
    }
} // function -----------------------------------------------------------------

void
vector_path::convert_fan_to_strip ()
{
    std::vector<gvector2d<float>> result;
    size_t n{m_tessellated_vertices.size()};
    if (n < 3) {
        return;
    }

    result.push_back(m_tessellated_vertices[0]);
    result.push_back(m_tessellated_vertices[1]);

    size_t left{2};
    size_t right{n - 1};
    bool take_from_right{true};
    while (left <= right) {
        if (take_from_right) {
            result.push_back(m_tessellated_vertices[right--]);
        } else {
            result.push_back(m_tessellated_vertices[left++]);
        }
        take_from_right = !take_from_right;
    }

    m_tessellated_vertices = std::move(result);
} // function -----------------------------------------------------------------

impl::buffer&
vector_path::grab_buffer ()
noexcept
{
    return m_buffer;
} // function -----------------------------------------------------------------

const impl::buffer&
vector_path::grab_buffer ()
const noexcept
{
    return m_buffer;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
