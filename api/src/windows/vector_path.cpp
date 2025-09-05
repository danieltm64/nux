// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/vector_path.hpp>

#include "windows.hpp"

namespace nux {

namespace impl {

// --------------------------------------------------------------- nux::buffer

// Constructors and Destructor ------------------------------------------------

buffer::buffer ()
    : m_native_handle{new buffer_native_handle{nullptr, 0}}
{
} // function -----------------------------------------------------------------

buffer::~buffer ()
noexcept
{
    if (m_native_handle->buffer) {
        m_native_handle->buffer->Release();
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
    const UINT size{
        static_cast<UINT>(
            sizeof (gvector2d<float>) * vertices.size()
        )
    };

    D3D11_BUFFER_DESC buffer_desc;
    buffer_desc.ByteWidth = size;
    buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
    buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    buffer_desc.MiscFlags = 0;
    buffer_desc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA subresource_data;
    subresource_data.pSysMem = vertices.data();
    subresource_data.SysMemPitch = 0;
    subresource_data.SysMemSlicePitch = 0;

    if (
        FAILED(
            graphics_handle.device->CreateBuffer(
                &buffer_desc,
                &subresource_data,
                &m_native_handle->buffer
            )
        )
    ) {
        throw std::runtime_error{"Buffer creation failed."};
    }

    m_native_handle->size = vertices.size();
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
