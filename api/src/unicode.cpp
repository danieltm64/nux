// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include "unicode.hpp"

#include "system.hpp"

namespace nux {

namespace impl {

// Free Functions -------------------------------------------------------------

int
initialize_utf8_sequence (
    char8_t leading_code_unit,
    char32_t& initial_code_point_value
) {
    if (is_standalone_byte(leading_code_unit)) {
        initial_code_point_value = leading_code_unit;
        return 1;
    } else if ((leading_code_unit >> 5) == 0b110) {
        initial_code_point_value = leading_code_unit & 0b0001'1111u;
        return 2;
    } else if ((leading_code_unit >> 4) == 0b1110) {
        initial_code_point_value = leading_code_unit & 0b0000'1111u;
        return 3;
    } else if ((leading_code_unit >> 3) == 0b11110) {
        initial_code_point_value = leading_code_unit & 0b0000'0111u;
        return 4;
    } else {
        throw invalid_unicode_encoding{};
    }
} // function -----------------------------------------------------------------

int
initialize_utf16_sequence (
    char16_t leading_code_unit,
    char32_t& initial_code_point_value
) {
    if (is_leading_surrogate(leading_code_unit)) {
        initial_code_point_value = (leading_code_unit - 0xD800u);
        initial_code_point_value <<= 10;
        return 2;
    } else if (is_trailing_surrogate(leading_code_unit)) {
        throw invalid_unicode_encoding{};
    } else {
        initial_code_point_value = leading_code_unit;
        return 1;
    }
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// Exceptions -----------------------------------------------------------------

// --------------------------------------------------- nux::invalid_code_point

// Core -----------------------------------------------------------------------

const char*
invalid_code_point::what ()
const noexcept
{
    return "Invalid code point.";
} // function -----------------------------------------------------------------

// --------------------------------------------- nux::invalid_unicode_encoding

// Core -----------------------------------------------------------------------

const char*
invalid_unicode_encoding::what ()
const noexcept
{
    return "The data read from the stream or string is not valid "
           "UTF-8 or UTF-16. UTF-32 is not affected because it is "
           "not a variable length encoding.";
} // function -----------------------------------------------------------------

// ---------------------------------------------------- nux::iterated_past_end

// Core -----------------------------------------------------------------------

const char*
iterated_past_end::what ()
const noexcept
{
    return "An attempt was made to iterate past the end of a string.";
} // function -----------------------------------------------------------------

// By Code Point --------------------------------------------------------------

// ---------------------------------- nux::by_code_point<char>::const_iterator

// Constructors and Destructor ------------------------------------------------

by_code_point<char>::const_iterator::const_iterator (
    std::string_view::const_iterator initial_current_iterator,
    std::string_view::const_iterator initial_end_iterator
)
noexcept
    : m_current_iterator{initial_current_iterator}
    , m_end_iterator{initial_end_iterator}
{
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

by_code_point<char>::const_iterator::reference
by_code_point<char>::const_iterator::operator * ()
const
{
    if (m_current_iterator == m_end_iterator) {
        throw iterated_past_end{};
    }
    return *m_current_iterator;
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator&
by_code_point<char>::const_iterator::operator ++ ()
{
    ++m_current_iterator;
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator
by_code_point<char>::const_iterator::operator ++ (
    int
) {
    const_iterator old_iterator{*this};
    ++m_current_iterator;
    return old_iterator;
} // function -----------------------------------------------------------------

const by_code_point<char>::const_iterator&
by_code_point<char>::const_iterator::operator += (
    by_code_point<char>::const_iterator::difference_type offset
) {
    m_current_iterator += offset;
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator&
by_code_point<char>::const_iterator::operator -- ()
noexcept
{
    --m_current_iterator;
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator
by_code_point<char>::const_iterator::operator -- (
    int
)
noexcept
{
    const_iterator old_iterator{*this};
    --m_current_iterator;
    return old_iterator;
} // function -----------------------------------------------------------------

const by_code_point<char>::const_iterator&
by_code_point<char>::const_iterator::operator -= (
    by_code_point<char>::const_iterator::difference_type offset
)
noexcept
{
    m_current_iterator -= offset;
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator
operator + (
    const by_code_point<char>::const_iterator& iterator,
    by_code_point<char>::const_iterator::difference_type offset
)
noexcept
{
    by_code_point<char>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.m_current_iterator += offset;
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator
operator + (
    by_code_point<char>::const_iterator::difference_type offset,
    const by_code_point<char>::const_iterator& iterator
)
noexcept
{
    by_code_point<char>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.m_current_iterator += offset;
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator
operator - (
    const by_code_point<char>::const_iterator& iterator,
    by_code_point<char>::const_iterator::difference_type offset
)
noexcept
{
    by_code_point<char>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.m_current_iterator -= offset;
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator
operator - (
    by_code_point<char>::const_iterator::difference_type offset,
    const by_code_point<char>::const_iterator& iterator
)
noexcept
{
    by_code_point<char>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.m_current_iterator -= offset;
    return result_iterator;
} // function -----------------------------------------------------------------

bool
operator == (
    const by_code_point<char>::const_iterator& iterator1,
    const by_code_point<char>::const_iterator& iterator2
)
noexcept
{
    return
        iterator1.m_current_iterator == iterator2.m_current_iterator
            && iterator1.m_end_iterator == iterator2.m_end_iterator;
} // function -----------------------------------------------------------------

bool
operator != (
    const by_code_point<char>::const_iterator& iterator1,
    const by_code_point<char>::const_iterator& iterator2
)
noexcept
{
    return
        iterator1.m_current_iterator != iterator2.m_current_iterator
            || iterator1.m_end_iterator != iterator2.m_end_iterator;
} // function -----------------------------------------------------------------

// -------------------------------------------------- nux::by_code_point<char>

// Constructors and Destructor ------------------------------------------------

by_code_point<char>::by_code_point (
    std::string_view string_to_iterate
)
noexcept
    : m_begin_iterator{string_to_iterate.cbegin()}
    , m_end_iterator{string_to_iterate.cend()}
{
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

by_code_point<char>::const_iterator
by_code_point<char>::begin ()
const noexcept
{
    return cbegin();
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator
by_code_point<char>::end ()
const noexcept
{
    return cend();
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator
by_code_point<char>::cbegin ()
const noexcept
{
    return const_iterator{m_begin_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator
by_code_point<char>::cend ()
const noexcept
{
    return const_iterator{m_end_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<char>::const_reverse_iterator
by_code_point<char>::crbegin ()
const noexcept
{
    return const_reverse_iterator{cend()};
} // function -----------------------------------------------------------------

by_code_point<char>::const_reverse_iterator
by_code_point<char>::crend ()
const noexcept
{
    return const_reverse_iterator{cbegin()};
} // function -----------------------------------------------------------------

// -------------------- nux::by_code_point<char8_t>::const_iterator::reference

// Constructors and Destructor ------------------------------------------------

by_code_point<char8_t>::const_iterator::reference::reference (
    std::u8string_view::const_iterator initial_current_iterator,
    std::u8string_view::const_iterator initial_end_iterator
)
noexcept
    : m_current_iterator{initial_current_iterator}
    , m_end_iterator{initial_end_iterator}
{
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

by_code_point<char8_t>::const_iterator::reference::operator char32_t ()
const
{
    char8_t code_unit{*m_current_iterator};
    char32_t code_point;
    auto sequence_length{
        impl::initialize_utf8_sequence(code_unit, code_point)
    };
    code_point = finish_sequence(
        sequence_length,
        code_point,
        m_current_iterator
    );
    return code_point;
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

char32_t
by_code_point<char8_t>::const_iterator::reference::finish_sequence (
    int sequence_length,
    char32_t initial_code_point_value,
    std::u8string_view::const_iterator i
)
const
{
    char32_t result{initial_code_point_value};
    if (sequence_length == 1) {
        return result;
    }
    char8_t code_unit;
    while (--sequence_length > 0) {
        if (i + 1 == m_end_iterator) {
            throw iterated_past_end{};
        }
        code_unit = *(i + 1);
        if (!is_trailing_byte(code_unit)) {
            throw invalid_unicode_encoding{};
        }
        ++i;
        result <<= 6;
        result |= code_unit & 0b0011'1111u;
    }
    return result;
} // function -----------------------------------------------------------------

// ------------------------------- nux::by_code_point<char8_t>::const_iterator

// Constructors and Destructor ------------------------------------------------

by_code_point<char8_t>::const_iterator::const_iterator (
    std::u8string_view::const_iterator initial_current_iterator,
    std::u8string_view::const_iterator initial_end_iterator
)
noexcept
    : m_current_iterator{initial_current_iterator}
    , m_end_iterator{initial_end_iterator}
{
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

by_code_point<char8_t>::const_iterator::reference
by_code_point<char8_t>::const_iterator::operator * ()
const
{
    if (m_current_iterator == m_end_iterator) {
        throw iterated_past_end{};
    }
    return reference{m_current_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator&
by_code_point<char8_t>::const_iterator::operator ++ ()
{
    advance();
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator
by_code_point<char8_t>::const_iterator::operator ++ (
    int
) {
    const_iterator old_iterator{*this};
    advance();
    return old_iterator;
} // function -----------------------------------------------------------------

const by_code_point<char8_t>::const_iterator&
by_code_point<char8_t>::const_iterator::operator += (
    difference_type offset
) {
    advance(offset);
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator&
by_code_point<char8_t>::const_iterator::operator -- ()
noexcept
{
    retreat();
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator
by_code_point<char8_t>::const_iterator::operator -- (
    int
)
noexcept
{
    const_iterator old_iterator{*this};
    retreat();
    return old_iterator;
} // function -----------------------------------------------------------------

const by_code_point<char8_t>::const_iterator&
by_code_point<char8_t>::const_iterator::operator -= (
    difference_type offset
)
noexcept
{
    retreat(offset);
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator
operator + (
    const by_code_point<char8_t>::const_iterator& iterator,
    by_code_point<char8_t>::const_iterator::difference_type offset
)
noexcept
{
    by_code_point<char8_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.advance(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator
operator + (
    by_code_point<char8_t>::const_iterator::difference_type offset,
    const by_code_point<char8_t>::const_iterator& iterator
)
noexcept
{
    by_code_point<char8_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.advance(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator
operator - (
    const by_code_point<char8_t>::const_iterator& iterator,
    by_code_point<char8_t>::const_iterator::difference_type offset
)
noexcept
{
    by_code_point<char8_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.retreat(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator
operator - (
    by_code_point<char8_t>::const_iterator::difference_type offset,
    const by_code_point<char8_t>::const_iterator& iterator
)
noexcept
{
    by_code_point<char8_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.retreat(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

bool
operator == (
    const by_code_point<char8_t>::const_iterator& iterator1,
    const by_code_point<char8_t>::const_iterator& iterator2
)
noexcept
{
    return
        iterator1.m_current_iterator == iterator2.m_current_iterator
            && iterator1.m_end_iterator == iterator2.m_end_iterator;
} // function -----------------------------------------------------------------

bool
operator != (
    const by_code_point<char8_t>::const_iterator& iterator1,
    const by_code_point<char8_t>::const_iterator& iterator2
)
noexcept
{
    return
        iterator1.m_current_iterator != iterator2.m_current_iterator
            || iterator1.m_end_iterator != iterator2.m_end_iterator;
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

char32_t
by_code_point<char8_t>::const_iterator::finish_sequence (
    int sequence_length,
    char32_t initial_code_point_value,
    std::u8string_view::const_iterator i
)
const
{
    char32_t result{initial_code_point_value};
    if (sequence_length == 1) {
        return result;
    }
    char8_t code_unit;
    while (--sequence_length > 0) {
        if (i == m_end_iterator) {
            throw iterated_past_end{};
        }
        code_unit = *(i + 1);
        if (!is_trailing_byte(code_unit)) {
            throw invalid_unicode_encoding{};
        }
        ++i;
        result <<= 6;
        result |= code_unit & 0b0011'1111u;
    }
    return result;
} // function -----------------------------------------------------------------

char32_t
by_code_point<char8_t>::const_iterator::finish_sequence (
    int sequence_length,
    char32_t initial_code_point_value,
    std::u8string_view::const_iterator& i
) {
    char32_t result{initial_code_point_value};
    if (sequence_length == 1) {
        ++i;
        return result;
    }
    char8_t code_unit;
    while (--sequence_length > 0) {
        if (i == m_end_iterator) {
            throw iterated_past_end{};
        }
        code_unit = *(i + 1);
        if (!is_trailing_byte(code_unit)) {
            throw invalid_unicode_encoding{};
        }
        ++i;
        result <<= 6;
        result |= code_unit & 0b0011'1111u;
    }
    ++i;
    return result;
} // function -----------------------------------------------------------------

void
by_code_point<char8_t>::const_iterator::advance ()
{
    char8_t code_unit{*m_current_iterator};
    char32_t code_point;
    auto sequence_length{
        impl::initialize_utf8_sequence(code_unit, code_point)
    };
    code_point = finish_sequence(
        sequence_length,
        code_point,
        m_current_iterator
    );
} // function -----------------------------------------------------------------

void
by_code_point<char8_t>::const_iterator::advance (
    difference_type offset
) {
    while (offset-- > 0) {
        advance();
    }
} // function -----------------------------------------------------------------

void
by_code_point<char8_t>::const_iterator::retreat ()
{
    char8_t code_unit{*(--m_current_iterator)};
    if (is_standalone_byte(code_unit)) {
        return;
    }
    while (is_trailing_byte(code_unit)) {
        code_unit = *(--m_current_iterator);
    }
} // function -----------------------------------------------------------------

void
by_code_point<char8_t>::const_iterator::retreat (
    difference_type offset
) {
    while (offset-- > 0) {
        retreat();
    }
} // function -----------------------------------------------------------------

// ----------------------------------------------- nux::by_code_point<char8_t>

// Constructors and Destructor ------------------------------------------------

by_code_point<char8_t>::by_code_point (
    std::u8string_view string_to_iterate
)
noexcept
    : m_begin_iterator{string_to_iterate.cbegin()}
    , m_end_iterator{string_to_iterate.cend()}
{
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

by_code_point<char8_t>::const_iterator
by_code_point<char8_t>::begin ()
const noexcept
{
    return cbegin();
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator
by_code_point<char8_t>::end ()
const noexcept
{
    return cend();
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator
by_code_point<char8_t>::cbegin ()
const noexcept
{
    return const_iterator{m_begin_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator
by_code_point<char8_t>::cend ()
const noexcept
{
    return const_iterator{m_end_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_reverse_iterator
by_code_point<char8_t>::crbegin ()
const noexcept
{
    return const_reverse_iterator{cend()};
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_reverse_iterator
by_code_point<char8_t>::crend ()
const noexcept
{
    return const_reverse_iterator{cbegin()};
} // function -----------------------------------------------------------------

// ------------------- nux::by_code_point<char16_t>::const_iterator::reference

// Constructors and Destructor ------------------------------------------------

by_code_point<char16_t>::const_iterator::reference::reference (
    std::u16string_view::const_iterator initial_current_iterator,
    std::u16string_view::const_iterator initial_end_iterator
)
noexcept
    : m_current_iterator{initial_current_iterator}
    , m_end_iterator{initial_end_iterator}
{
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

by_code_point<char16_t>::const_iterator::reference::operator char32_t ()
const
{
    char16_t code_unit{*m_current_iterator};
    char32_t code_point;
    auto sequence_length{
        impl::initialize_utf16_sequence(code_unit, code_point)
    };
    code_point = finish_sequence(
        sequence_length,
        code_point,
        m_current_iterator
    );
    return code_point;
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

char32_t
by_code_point<char16_t>::const_iterator::reference::finish_sequence (
    int sequence_length,
    char32_t initial_code_point_value,
    std::u16string_view::const_iterator i
)
const
{
    if (sequence_length == 2) {
        if (i + 1 == m_end_iterator) {
            throw iterated_past_end{};
        }
        char16_t code_unit{*(i + 1)};
        if (!is_trailing_surrogate(code_unit)) {
            throw invalid_unicode_encoding{};
        }
        ++i;
        return initial_code_point_value + (code_unit - 0xDC00) + 0x10000;
    } else {
        return initial_code_point_value;
    }
} // function -----------------------------------------------------------------

// ------------------------------ nux::by_code_point<char16_t>::const_iterator

// Constructors and Destructor ------------------------------------------------

by_code_point<char16_t>::const_iterator::const_iterator (
    std::u16string_view::const_iterator initial_current_iterator,
    std::u16string_view::const_iterator initial_end_iterator
)
noexcept
    : m_current_iterator{initial_current_iterator}
    , m_end_iterator{initial_end_iterator}
{
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

by_code_point<char16_t>::const_iterator::reference
by_code_point<char16_t>::const_iterator::operator * ()
const
{
    if (m_current_iterator == m_end_iterator) {
        throw iterated_past_end{};
    }
    return reference{m_current_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator&
by_code_point<char16_t>::const_iterator::operator ++ ()
{
    advance();
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator
by_code_point<char16_t>::const_iterator::operator ++ (
    int
) {
    const_iterator old_iterator{*this};
    advance();
    return old_iterator;
} // function -----------------------------------------------------------------

const by_code_point<char16_t>::const_iterator&
by_code_point<char16_t>::const_iterator::operator += (
    difference_type offset
) {
    advance(offset);
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator&
by_code_point<char16_t>::const_iterator::operator -- ()
noexcept
{
    retreat();
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator
by_code_point<char16_t>::const_iterator::operator -- (
    int
)
noexcept
{
    const_iterator old_iterator{*this};
    retreat();
    return old_iterator;
} // function -----------------------------------------------------------------

const by_code_point<char16_t>::const_iterator&
by_code_point<char16_t>::const_iterator::operator -= (
    difference_type offset
)
noexcept
{
    retreat(offset);
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator
operator + (
    const by_code_point<char16_t>::const_iterator& iterator,
    by_code_point<char16_t>::const_iterator::difference_type offset
)
noexcept
{
    by_code_point<char16_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.advance(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator
operator + (
    by_code_point<char16_t>::const_iterator::difference_type offset,
    const by_code_point<char16_t>::const_iterator& iterator
)
noexcept
{
    by_code_point<char16_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.advance(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator
operator - (
    const by_code_point<char16_t>::const_iterator& iterator,
    by_code_point<char16_t>::const_iterator::difference_type offset
)
noexcept
{
    by_code_point<char16_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.retreat(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator
operator - (
    by_code_point<char16_t>::const_iterator::difference_type offset,
    const by_code_point<char16_t>::const_iterator& iterator
)
noexcept
{
    by_code_point<char16_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.retreat(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

bool
operator == (
    const by_code_point<char16_t>::const_iterator& iterator1,
    const by_code_point<char16_t>::const_iterator& iterator2
)
noexcept
{
    return
        iterator1.m_current_iterator == iterator2.m_current_iterator
            && iterator1.m_end_iterator == iterator2.m_end_iterator;
} // function -----------------------------------------------------------------

bool
operator != (
    const by_code_point<char16_t>::const_iterator& iterator1,
    const by_code_point<char16_t>::const_iterator& iterator2
)
noexcept
{
    return
        iterator1.m_current_iterator != iterator2.m_current_iterator
            || iterator1.m_end_iterator != iterator2.m_end_iterator;
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

char32_t
by_code_point<char16_t>::const_iterator::finish_sequence (
    int sequence_length,
    char32_t initial_code_point_value,
    std::u16string_view::const_iterator i
)
const
{
    if (sequence_length == 2) {
        if (i == m_end_iterator) {
            throw iterated_past_end{};
        }
        char16_t code_unit{*(i + 1)};
        if (!is_trailing_surrogate(code_unit)) {
            throw invalid_unicode_encoding{};
        }
        ++i;
        return initial_code_point_value + (code_unit - 0xDC00) + 0x10000;
    } else {
        return initial_code_point_value;
    }
} // function -----------------------------------------------------------------

char32_t
by_code_point<char16_t>::const_iterator::finish_sequence (
    int sequence_length,
    char32_t initial_code_point_value,
    std::u16string_view::const_iterator& i
) {
    if (sequence_length == 2) {
        if (i == m_end_iterator) {
            throw iterated_past_end{};
        }
        char16_t code_unit{*(i + 1)};
        if (!is_trailing_surrogate(code_unit)) {
            throw invalid_unicode_encoding{};
        }
        ++i;
        return initial_code_point_value + (code_unit - 0xDC00) + 0x10000;
    } else {
        ++i;
        return initial_code_point_value;
    }
} // function -----------------------------------------------------------------

void
by_code_point<char16_t>::const_iterator::advance ()
{
    char16_t code_unit{*m_current_iterator};
    char32_t code_point;
    auto sequence_length{
        impl::initialize_utf16_sequence(code_unit, code_point)
    };
    code_point = finish_sequence(
        sequence_length,
        code_point,
        m_current_iterator
    );
} // function -----------------------------------------------------------------

void
by_code_point<char16_t>::const_iterator::advance (
    difference_type offset
) {
    while (offset-- > 0) {
        advance();
    }
} // function -----------------------------------------------------------------

void
by_code_point<char16_t>::const_iterator::retreat ()
{
    char16_t code_unit{*(--m_current_iterator)};
    if (is_trailing_surrogate(code_unit)) {
        --m_current_iterator;
    }
} // function -----------------------------------------------------------------

void
by_code_point<char16_t>::const_iterator::retreat (
    difference_type offset
) {
    while (offset-- > 0) {
        advance();
    }
} // function -----------------------------------------------------------------

// ---------------------------------------------- nux::by_code_point<char16_t>

// Constructors and Destructor ------------------------------------------------

by_code_point<char16_t>::by_code_point (
    std::u16string_view string_to_iterate
)
noexcept
    : m_begin_iterator{string_to_iterate.cbegin()}
    , m_end_iterator{string_to_iterate.cend()}
{
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

by_code_point<char16_t>::const_iterator
by_code_point<char16_t>::begin ()
const noexcept
{
    return cbegin();
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator
by_code_point<char16_t>::end ()
const noexcept
{
    return cend();
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator
by_code_point<char16_t>::cbegin ()
const noexcept
{
    return const_iterator{m_begin_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator
by_code_point<char16_t>::cend ()
const noexcept
{
    return const_iterator{m_end_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_reverse_iterator
by_code_point<char16_t>::crbegin ()
const noexcept
{
    return const_reverse_iterator{cend()};
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_reverse_iterator
by_code_point<char16_t>::crend ()
const noexcept
{
    return const_reverse_iterator{cbegin()};
} // function -----------------------------------------------------------------

// ------------------------------ nux::by_code_point<char32_t>::const_iterator

// Constructors and Destructor ------------------------------------------------

by_code_point<char32_t>::const_iterator::const_iterator (
    std::u32string_view::const_iterator initial_current_iterator,
    std::u32string_view::const_iterator initial_end_iterator
)
noexcept
    : m_current_iterator{initial_current_iterator}
    , m_end_iterator{initial_end_iterator}
{
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

by_code_point<char32_t>::const_iterator::reference
by_code_point<char32_t>::const_iterator::operator * ()
const
{
    if (m_current_iterator == m_end_iterator) {
        throw iterated_past_end{};
    }
    return *m_current_iterator;
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator&
by_code_point<char32_t>::const_iterator::operator ++ ()
{
    ++m_current_iterator;
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator
by_code_point<char32_t>::const_iterator::operator ++ (
    int
) {
    const_iterator old_iterator{*this};
    ++m_current_iterator;
    return old_iterator;
} // function -----------------------------------------------------------------

const by_code_point<char32_t>::const_iterator&
by_code_point<char32_t>::const_iterator::operator += (
    by_code_point<char32_t>::const_iterator::difference_type offset
) {
    m_current_iterator += offset;
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator&
by_code_point<char32_t>::const_iterator::operator -- ()
noexcept
{
    --m_current_iterator;
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator
by_code_point<char32_t>::const_iterator::operator -- (
    int
)
noexcept
{
    const_iterator old_iterator{*this};
    --m_current_iterator;
    return old_iterator;
} // function -----------------------------------------------------------------

const by_code_point<char32_t>::const_iterator&
by_code_point<char32_t>::const_iterator::operator -= (
    by_code_point<char32_t>::const_iterator::difference_type offset
)
noexcept
{
    m_current_iterator -= offset;
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator
operator + (
    const by_code_point<char32_t>::const_iterator& iterator,
    by_code_point<char32_t>::const_iterator::difference_type offset
)
noexcept
{
    by_code_point<char32_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.m_current_iterator += offset;
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator
operator + (
    by_code_point<char32_t>::const_iterator::difference_type offset,
    const by_code_point<char32_t>::const_iterator& iterator
)
noexcept
{
    by_code_point<char32_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.m_current_iterator += offset;
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator
operator - (
    const by_code_point<char32_t>::const_iterator& iterator,
    by_code_point<char32_t>::const_iterator::difference_type offset
)
noexcept
{
    by_code_point<char32_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.m_current_iterator -= offset;
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator
operator - (
    by_code_point<char32_t>::const_iterator::difference_type offset,
    const by_code_point<char32_t>::const_iterator& iterator
)
noexcept
{
    by_code_point<char32_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.m_current_iterator -= offset;
    return result_iterator;
} // function -----------------------------------------------------------------

bool
operator == (
    const by_code_point<char32_t>::const_iterator& iterator1,
    const by_code_point<char32_t>::const_iterator& iterator2
)
noexcept
{
    return
        iterator1.m_current_iterator == iterator2.m_current_iterator
            && iterator1.m_end_iterator == iterator2.m_end_iterator;
} // function -----------------------------------------------------------------

bool
operator != (
    const by_code_point<char32_t>::const_iterator& iterator1,
    const by_code_point<char32_t>::const_iterator& iterator2
)
noexcept
{
    return
        iterator1.m_current_iterator != iterator2.m_current_iterator
            || iterator1.m_end_iterator != iterator2.m_end_iterator;
} // function -----------------------------------------------------------------

// ---------------------------------------------- nux::by_code_point<char32_t>

// Constructors and Destructor ------------------------------------------------

by_code_point<char32_t>::by_code_point (
    std::u32string_view string_to_iterate
)
noexcept
    : m_begin_iterator{string_to_iterate.cbegin()}
    , m_end_iterator{string_to_iterate.cend()}
{
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

by_code_point<char32_t>::const_iterator
by_code_point<char32_t>::begin ()
const noexcept
{
    return cbegin();
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator
by_code_point<char32_t>::end ()
const noexcept
{
    return cend();
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator
by_code_point<char32_t>::cbegin ()
const noexcept
{
    return const_iterator{m_begin_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator
by_code_point<char32_t>::cend ()
const noexcept
{
    return const_iterator{m_end_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_reverse_iterator
by_code_point<char32_t>::crbegin ()
const noexcept
{
    return const_reverse_iterator{cend()};
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_reverse_iterator
by_code_point<char32_t>::crend ()
const noexcept
{
    return const_reverse_iterator{cbegin()};
} // function -----------------------------------------------------------------

// -------------------- nux::by_code_point<wchar_t>::const_iterator::reference

// Constructors and Destructor ------------------------------------------------

by_code_point<wchar_t>::const_iterator::reference::reference (
    std::wstring_view::const_iterator initial_current_iterator,
    std::wstring_view::const_iterator initial_end_iterator
)
noexcept
    : m_current_iterator{initial_current_iterator}
    , m_end_iterator{initial_end_iterator}
{
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

by_code_point<wchar_t>::const_iterator::reference::operator char32_t ()
const
{
    if constexpr (sizeof (wchar_t) == 2) {
        wchar_t code_unit{*m_current_iterator};
        char32_t code_point;
        auto sequence_length{
            impl::initialize_utf16_sequence(code_unit, code_point)
        };
        code_point = finish_sequence(
            sequence_length,
            code_point,
            m_current_iterator
        );
        return code_point;
    } else {
        return *m_current_iterator;
    }
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

char32_t
by_code_point<wchar_t>::const_iterator::reference::finish_sequence (
    int sequence_length,
    char32_t initial_code_point_value,
    std::wstring_view::const_iterator i
)
const
{
    if (sequence_length == 2) {
        if (i + 1 == m_end_iterator) {
            throw iterated_past_end{};
        }
        char16_t code_unit{static_cast<char16_t>(*(i + 1))};
        if (!is_trailing_surrogate(code_unit)) {
            throw invalid_unicode_encoding{};
        }
        ++i;
        return initial_code_point_value + (code_unit - 0xDC00) + 0x10000;
    } else {
        return initial_code_point_value;
    }
} // function -----------------------------------------------------------------

// ------------------------------- nux::by_code_point<wchar_t>::const_iterator

// Constructors and Destructor ------------------------------------------------

by_code_point<wchar_t>::const_iterator::const_iterator (
    std::wstring_view::const_iterator initial_current_iterator,
    std::wstring_view::const_iterator initial_end_iterator
)
noexcept
    : m_current_iterator{initial_current_iterator}
    , m_end_iterator{initial_end_iterator}
{
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

by_code_point<wchar_t>::const_iterator::reference
by_code_point<wchar_t>::const_iterator::operator * ()
const
{
    if (m_current_iterator == m_end_iterator) {
        throw iterated_past_end{};
    }
    return reference{m_current_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator&
by_code_point<wchar_t>::const_iterator::operator ++ ()
{
    advance();
    return *this;
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator
by_code_point<wchar_t>::const_iterator::operator ++ (
    int
) {
    const_iterator old_iterator{*this};
    advance();
    return old_iterator;
} // function -----------------------------------------------------------------

const by_code_point<wchar_t>::const_iterator&
by_code_point<wchar_t>::const_iterator::operator += (
    difference_type offset
) {
    advance(offset);
    return *this;
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator&
by_code_point<wchar_t>::const_iterator::operator -- ()
noexcept
{
    retreat();
    return *this;
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator
by_code_point<wchar_t>::const_iterator::operator -- (
    int
)
noexcept
{
    const_iterator old_iterator{*this};
    retreat();
    return old_iterator;
} // function -----------------------------------------------------------------

const by_code_point<wchar_t>::const_iterator&
by_code_point<wchar_t>::const_iterator::operator -= (
    difference_type offset
)
noexcept
{
    retreat(offset);
    return *this;
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator
operator + (
    const by_code_point<wchar_t>::const_iterator& iterator,
    by_code_point<wchar_t>::const_iterator::difference_type offset
)
noexcept
{
    by_code_point<wchar_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.advance(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator
operator + (
    by_code_point<wchar_t>::const_iterator::difference_type offset,
    const by_code_point<wchar_t>::const_iterator& iterator
)
noexcept
{
    by_code_point<wchar_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.advance(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator
operator - (
    const by_code_point<wchar_t>::const_iterator& iterator,
    by_code_point<wchar_t>::const_iterator::difference_type offset
)
noexcept
{
    by_code_point<wchar_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.retreat(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator
operator - (
    by_code_point<wchar_t>::const_iterator::difference_type offset,
    const by_code_point<wchar_t>::const_iterator& iterator
)
noexcept
{
    by_code_point<wchar_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.retreat(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

bool
operator == (
    const by_code_point<wchar_t>::const_iterator& iterator1,
    const by_code_point<wchar_t>::const_iterator& iterator2
)
noexcept
{
    return
        iterator1.m_current_iterator == iterator2.m_current_iterator
            && iterator1.m_end_iterator == iterator2.m_end_iterator;
} // function -----------------------------------------------------------------

bool
operator != (
    const by_code_point<wchar_t>::const_iterator& iterator1,
    const by_code_point<wchar_t>::const_iterator& iterator2
)
noexcept
{
    return
        iterator1.m_current_iterator != iterator2.m_current_iterator
            || iterator1.m_end_iterator != iterator2.m_end_iterator;
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

char32_t
by_code_point<wchar_t>::const_iterator::finish_sequence (
    int sequence_length,
    char32_t initial_code_point_value,
    std::wstring_view::const_iterator i
)
const
{
    if (sequence_length == 2) {
        if (i == m_end_iterator) {
            throw iterated_past_end{};
        }
        char16_t code_unit{static_cast<char16_t>(*(i + 1))};
        if (!is_trailing_surrogate(code_unit)) {
            throw invalid_unicode_encoding{};
        }
        ++i;
        return initial_code_point_value + (code_unit - 0xDC00) + 0x10000;
    } else {
        return initial_code_point_value;
    }
} // function -----------------------------------------------------------------

char32_t
by_code_point<wchar_t>::const_iterator::finish_sequence (
    int sequence_length,
    char32_t initial_code_point_value,
    std::wstring_view::const_iterator& i
) {
    if (sequence_length == 2) {
        if (i == m_end_iterator) {
            throw iterated_past_end{};
        }
        char16_t code_unit{static_cast<char16_t>(*(i + 1))};
        if (!is_trailing_surrogate(code_unit)) {
            throw invalid_unicode_encoding{};
        }
        ++i;
        return initial_code_point_value + (code_unit - 0xDC00) + 0x10000;
    } else {
        ++i;
        return initial_code_point_value;
    }
} // function -----------------------------------------------------------------

void
by_code_point<wchar_t>::const_iterator::advance ()
{
    if constexpr (sizeof (wchar_t) == 2) {
        char16_t code_unit{static_cast<char16_t>(*m_current_iterator)};
        char32_t code_point;
        auto sequence_length{
            impl::initialize_utf16_sequence(code_unit, code_point)
        };
        code_point = finish_sequence(
            sequence_length,
            code_point,
            m_current_iterator
        );
    } else {
        ++m_current_iterator;
    }
} // function -----------------------------------------------------------------

void
by_code_point<wchar_t>::const_iterator::advance (
    difference_type offset
) {
    if constexpr (sizeof (wchar_t) == 2) {
        while (offset-- > 0) {
            advance();
        }
    } else {
        m_current_iterator += offset;
    }
} // function -----------------------------------------------------------------

void
by_code_point<wchar_t>::const_iterator::retreat ()
{
    if constexpr (sizeof (wchar_t) == 2) {
        char16_t code_unit{static_cast<char16_t>(*(--m_current_iterator))};
        if (is_trailing_surrogate(code_unit)) {
            --m_current_iterator;
        }
    } else {
        --m_current_iterator;
    }
} // function -----------------------------------------------------------------

void
by_code_point<wchar_t>::const_iterator::retreat (
    difference_type offset
) {
    if constexpr (sizeof (wchar_t) == 2) {
        while (offset-- > 0) {
            advance();
        }
    } else {
        m_current_iterator -= offset;
    }
} // function -----------------------------------------------------------------

// ----------------------------------------------- nux::by_code_point<wchar_t>

// Constructors and Destructor ------------------------------------------------

by_code_point<wchar_t>::by_code_point (
    std::wstring_view string_to_iterate
)
noexcept
    : m_begin_iterator{string_to_iterate.cbegin()}
    , m_end_iterator{string_to_iterate.cend()}
{
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

by_code_point<wchar_t>::const_iterator
by_code_point<wchar_t>::begin ()
const noexcept
{
    return cbegin();
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator
by_code_point<wchar_t>::end ()
const noexcept
{
    return cend();
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator
by_code_point<wchar_t>::cbegin ()
const noexcept
{
    return const_iterator{m_begin_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator
by_code_point<wchar_t>::cend ()
const noexcept
{
    return const_iterator{m_end_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_reverse_iterator
by_code_point<wchar_t>::crbegin ()
const noexcept
{
    return const_reverse_iterator{cend()};
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_reverse_iterator
by_code_point<wchar_t>::crend ()
const noexcept
{
    return const_reverse_iterator{cbegin()};
} // function -----------------------------------------------------------------

// Free Functions -------------------------------------------------------------

std::size_t
string_size (
    const std::string& s
)
noexcept
{
    return std::size(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::u8string& s
)
noexcept
{
    return std::size(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::u16string& s
)
noexcept
{
    return std::size(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::u32string& s
)
noexcept
{
    return std::size(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::wstring& s
)
noexcept
{
    return std::size(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::string_view& s
)
noexcept
{
    return std::size(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::u8string_view& s
)
noexcept
{
    return std::size(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::u16string_view& s
)
noexcept
{
    return std::size(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::u32string_view& s
)
noexcept
{
    return std::size(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::wstring_view& s
)
noexcept
{
    return std::size(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const char* s
)
noexcept
{
    const char* current{s};
    while (*current != '\0') {
        ++current;
    }
    return current - s;
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const char8_t* s
)
noexcept
{
    const char8_t* current{s};
    while (*current != u8'\0') {
        ++current;
    }
    return current - s;
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const char16_t* s
)
noexcept
{
    const char16_t* current{s};
    while (*current != u'\0') {
        ++current;
    }
    return current - s;
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const char32_t* s
)
noexcept
{
    const char32_t* current{s};
    while (*current != U'\0') {
        ++current;
    }
    return current - s;
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const wchar_t* s
)
noexcept
{
    return std::wcslen(s);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

