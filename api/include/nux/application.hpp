// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_APPLICATION_HPP_INCLUDED
#define NUX_APPLICATION_HPP_INCLUDED

#include <nux/general.hpp>
#include <nux/application_native_handle.hpp>

#include <stdexcept>

namespace nux {

class NUX_CONDITIONAL_EXPORT_CLASS application {
public:
    // Constructors and Destructor --------------------------------------------

    NUX_CONDITIONAL_EXPORT
    application (
        int argc,
        char** argv
    );

    NUX_CONDITIONAL_EXPORT
    ~application ()
    noexcept;

    // Copy Operations --------------------------------------------------------

    application (
        const application& other
    )
    = delete;

    application&
    operator = (
        const application& other
    )
    = delete;

    // Move Operations --------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    application (
        application&& other
    )
    noexcept;

    NUX_CONDITIONAL_EXPORT
    application&
    operator = (
        application&& other
    )
    noexcept;

    // Accessors --------------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    static
    encoding
    get_encoding ()
    noexcept;

    NUX_CONDITIONAL_EXPORT
    application_native_handle&
    grab_native_handle ()
    noexcept;

    NUX_CONDITIONAL_EXPORT
    const application_native_handle&
    grab_native_handle ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    bool
    is_running ()
    const noexcept;

    // Core -------------------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    int
    run ();

    // Friends ----------------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    friend
    application*
    app ()
    noexcept;

private:
    // Private Data -----------------------------------------------------------

    static application* g_app;

    application_native_handle* m_native_handle;
    bool m_is_running;
}; // class -------------------------------------------------------------------

// Free Functions -------------------------------------------------------------

NUX_CONDITIONAL_EXPORT
application*
app ()
noexcept;

} // namespace ----------------------------------------------------------------

#endif
