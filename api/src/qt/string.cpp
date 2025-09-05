// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include "qt.hpp"

namespace nux {

namespace impl {

QString
to_qstring (
    nux::string_view input
) {
#if defined(NUX_STRING_TYPE_STD_U16STRING)
    return QString::fromUtf16(input.data(), input.size());
#else
    return QString::fromUtf8(input.data(), input.size());
#endif
} // function -----------------------------------------------------------------

nux::string
to_nux_string (
    QStringView input
) {
#if defined(NUX_STRING_TYPE_STD_U16STRING)
    return input.toString().toStdU16String();
#elif defined(NUX_STRING_TYPE_STD_U8STRING)
    return reinterpret_cast<const char8_t*>(input.toString().toUtf8().data());
#else
    return input.toString().toStdString();
#endif
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
