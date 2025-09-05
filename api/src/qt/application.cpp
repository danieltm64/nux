// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/application.hpp>

#include "qt.hpp"

namespace nux {

// ---------------------------------------------------------- nux::application

// Constructors and Destructor ------------------------------------------------

application::application (
    int argc,
    char** argv
)
    : m_native_handle{new application_native_handle{}}
    , m_is_running{false}
{
    g_app = this;

    QSurfaceFormat surface_format;
    surface_format.setVersion(4, 0);
    surface_format.setProfile(QSurfaceFormat::CoreProfile);
    surface_format.setDepthBufferSize(24);
    surface_format.setStencilBufferSize(8);
    surface_format.setSamples(4);
    surface_format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    QSurfaceFormat::setDefaultFormat(surface_format);

    m_native_handle->argc = argc;
    m_native_handle->argv = argv;

    m_native_handle->qt_application
        = std::make_unique<QApplication>(argc, argv);
} // function -----------------------------------------------------------------

application::~application ()
noexcept
{
    delete m_native_handle;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

int
application::run ()
{
    m_is_running = true;
    int result{m_native_handle->qt_application->exec()};
    m_is_running = false;
    return result;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
