// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/group_box.hpp>

#include "system.hpp"

namespace nux {

// ------------------------------------------------------------ nux::group_box

// Accessors ------------------------------------------------------------------

layout&
group_box::grab_content_layout ()
noexcept
{
    return m_content_layout;
} // function -----------------------------------------------------------------

const layout&
group_box::grab_content_layout ()
const noexcept
{
    return m_content_layout;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
group_box::show ()
noexcept
{
    widget::show();
    m_content_layout.show();
} // function -----------------------------------------------------------------

void
group_box::hide ()
noexcept
{
    widget::hide();
    m_content_layout.hide();
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
