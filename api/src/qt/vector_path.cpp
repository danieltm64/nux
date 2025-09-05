// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/vector_path.hpp>

#include "qt.hpp"

namespace nux {

namespace impl {

// --------------------------------------------------------------- nux::buffer

// Constructors and Destructor ------------------------------------------------

buffer::buffer ()
    : m_native_handle{new buffer_native_handle{0, 0}}
{
} // function -----------------------------------------------------------------

buffer::~buffer ()
noexcept
{
    if (m_native_handle->buffer) {
        m_native_handle->qgl->glDeleteBuffers(1, &m_native_handle->buffer);
    }
    delete m_native_handle;
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

bool
buffer::is_ready ()
const noexcept
{
    return m_native_handle->buffer;
} // function -----------------------------------------------------------------

std::size_t
buffer::get_size ()
const noexcept
{
    return m_native_handle->size;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
buffer::upload (
    graphics_native_handle& graphics_handle,
    const std::vector<gvector2d<float>>& vertices
)
const
{
    auto qgl{graphics_handle.qgl};
    m_native_handle->qgl = qgl;

    qgl->glGenVertexArrays(1, &m_native_handle->vao);
    qgl->glBindVertexArray(m_native_handle->vao);

    qgl->glGenBuffers(1, &m_native_handle->buffer);
    qgl->glBindBuffer(GL_ARRAY_BUFFER, m_native_handle->buffer);

    qgl->glEnableVertexAttribArray(0);
    qgl->glVertexAttribPointer(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        2 * sizeof (float),
        (void*)0
    );
    qgl->glBufferData(
        GL_ARRAY_BUFFER,
        static_cast<GLsizei>(vertices.size() * sizeof (gvector2d<float>)),
        vertices.data(),
        GL_STATIC_DRAW
    );

    qgl->glBindVertexArray(0);

    m_native_handle->size = vertices.size();
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
