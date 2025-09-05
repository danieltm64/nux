// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/application.hpp>

#include "system.hpp"

namespace nux {

// ---------------------------------------------------------- nux::application

// Move Operations ------------------------------------------------------------

application::application (
    application &&other
)
noexcept
{
    std::swap(m_native_handle, other.m_native_handle);
    std::swap(m_is_running, other.m_is_running);
} // function -----------------------------------------------------------------

application&
application::operator = (
    application &&other
)
noexcept
{
    std::swap(m_native_handle, other.m_native_handle);
    std::swap(m_is_running, other.m_is_running);
    return *this;
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

encoding
application::get_encoding ()
noexcept
{
#if defined(NUX_STRING_TYPE_STD_U16STRING)
    return encoding::utf16;
#else
    return encoding::utf8;
#endif
} // function -----------------------------------------------------------------

application_native_handle&
application::grab_native_handle ()
noexcept
{
    return *m_native_handle;
} // function -----------------------------------------------------------------

const application_native_handle&
application::grab_native_handle ()
const noexcept
{
    return *m_native_handle;
} // function -----------------------------------------------------------------

bool
application::is_running ()
const noexcept
{
    return m_is_running;
} // function -----------------------------------------------------------------

// Private Data ---------------------------------------------------------------

application* application::g_app;

// Free Functions -------------------------------------------------------------

application*
app ()
noexcept
{
    return application::g_app;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
