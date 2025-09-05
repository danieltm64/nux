// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_GTK_HPP_INCLUDED
#define NUX_GTK_HPP_INCLUDED

#include <nux/application.hpp>
#include <nux/string.hpp>
#include <nux/widget.hpp>
#include "../unicode.hpp"

#include <vector>

#include <QApplication>
#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QGroupBox>
#include <qopenglcontext.h>

namespace nux {

namespace impl
{

class nux_main_window
    : public QMainWindow
{
public:
    // Constructors and Destructor --------------------------------------------

    explicit
    nux_main_window (
        QWidget* parent = nullptr,
        Qt::WindowFlags flags = Qt::WindowFlags()
    );

    ~nux_main_window ()
    override = default;

protected:
    // Protected Functions ----------------------------------------------------

    void
    keyPressEvent (
        QKeyEvent* event
    )
    override;

    void
    keyReleaseEvent (
        QKeyEvent* event
    )
    override;

    void
    resizeEvent (
        QResizeEvent* event
    )
    override;

    void
    closeEvent (
        QCloseEvent* event
    )
    override;
}; // class -------------------------------------------------------------------

widget*
find_widget (
    QWidget* widget_handle,
    const std::vector<std::unique_ptr<window_element>>& window_elements
);

} // namespace ----------------------------------------------------------------

class window;
class graphics_box;

class NUX_CONDITIONAL_EXPORT_CLASS application_native_handle {
public:
    // Public Data ------------------------------------------------------------

    int argc;
    char** argv;
    std::unique_ptr<QApplication> qt_application;
    std::vector<
        std::pair<impl::nux_main_window*, window*>
    > window_associations;
    QButtonGroup button_group;
}; // class -------------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS window_native_handle {
public:
    // Public Data ------------------------------------------------------------

    impl::nux_main_window* nux_main_window_handle;
}; // class -------------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS layout_native_handle {
}; // class -------------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS widget_native_handle {
public:
    QWidget* parent_handle;
    QWidget* widget_handle;
}; // class -------------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS graphics_native_handle {
public:
    // Public Data ------------------------------------------------------------

    QOpenGLExtraFunctions* qgl;
    GLuint shader_program;
}; // class -------------------------------------------------------------------

namespace impl {

class NUX_CONDITIONAL_EXPORT_CLASS buffer_native_handle {
public:
    // Public Data ------------------------------------------------------------

    QOpenGLExtraFunctions* qgl;
    GLuint buffer;
    GLuint vao;
    std::size_t size;
}; // class -------------------------------------------------------------------

class nux_opengl_widget
    : public QOpenGLWidget
    , public QOpenGLExtraFunctions
{
public:
    // Constructors and Destructor --------------------------------------------

    nux_opengl_widget (
        QWidget* parent = nullptr
    );

    ~nux_opengl_widget ()
    override;

    // Accessors --------------------------------------------------------------

    QOpenGLExtraFunctions&
    grab_opengl_functions ()
    noexcept;

    void
    set_wrapper (
        graphics_box* wrapper
    )
    noexcept;

    // Core -------------------------------------------------------------------

    void
    clear (
        float red,
        float green,
        float blue,
        float alpha
    );

    // Public Data ------------------------------------------------------------

    graphics_native_handle graphics_handle;

protected:
    // Protected Functions ----------------------------------------------------

    void
    initializeGL ()
    override;

    void
    paintGL ()
    override;

    void
    resizeGL (
        int width,
        int height
    )
    override;

private:
    // Private Data -----------------------------------------------------------

    graphics_box* m_wrapper;
}; // class -------------------------------------------------------------------

QString
to_qstring (
    nux::string_view input
);

nux::string
to_nux_string (
    QStringView input
);

widget_native_handle
create_widget (
    QWidget* parent_handle,
    native_widget_kind kind
)
noexcept;

} // namespace ----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif
