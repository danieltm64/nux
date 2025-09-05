// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_UNICODE_BY_CODE_POINT_HPP_INCLUDED
#define NUX_UNICODE_BY_CODE_POINT_HPP_INCLUDED

#include <string>

#include <nux/core.hpp>

namespace nux {

namespace impl {

// Free Functions -------------------------------------------------------------

NUX_CONDITIONAL_EXPORT
int
initialize_utf8_sequence (
    char8_t leading_code_unit,
    char32_t& initial_code_point_value
);

NUX_CONDITIONAL_EXPORT
int
initialize_utf16_sequence (
    char16_t leading_code_unit,
    char32_t& initial_code_point_value
);

} // namespace ----------------------------------------------------------------

// Constants ------------------------------------------------------------------

constexpr char32_t bom{0xFEFF};

constexpr char16_t leading_surrogate_minimum_value{0xD800};

constexpr char16_t leading_surrogate_maximum_value{0xDBFF};

constexpr char16_t trailing_surrogate_minimum_value{0xDC00};

constexpr char16_t trailing_surrogate_maximum_value{0xDFFF};

constexpr char32_t maximum_code_point{0x10FFFF};

constexpr char32_t maximum_bmp_code_point{0xFFFF};

// Exceptions -----------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS invalid_code_point
    : public std::exception
{
public:
    // Constructors and Destructor --------------------------------------------

    invalid_code_point ()
    noexcept = default;

    ~invalid_code_point ()
    override = default;

    // Copy Operations --------------------------------------------------------

    invalid_code_point (
        const invalid_code_point& other
    )
    noexcept = default;

    invalid_code_point&
    operator = (
        const invalid_code_point& other
    ) &
    noexcept = default;

    // Move Operations --------------------------------------------------------

    invalid_code_point (
        invalid_code_point&& other
    )
    noexcept = default;

    invalid_code_point&
    operator = (
        invalid_code_point&& other
    ) &
    noexcept = default;

    // Core -------------------------------------------------------------------

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const char*
    what ()
    const noexcept override;
}; // class -------------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS invalid_unicode_encoding
    : public std::exception
{
public:
    // Constructors and Destructor --------------------------------------------

    invalid_unicode_encoding ()
    noexcept = default;

    ~invalid_unicode_encoding ()
    override = default;

    // Copy Operations --------------------------------------------------------

    invalid_unicode_encoding (
        const invalid_unicode_encoding& other
    )
    noexcept = default;

    invalid_unicode_encoding&
    operator = (
        const invalid_unicode_encoding& other
    ) &
    noexcept = default;

    // Move Operations --------------------------------------------------------

    invalid_unicode_encoding (
        invalid_unicode_encoding&& other
    )
    noexcept = default;

    invalid_unicode_encoding&
    operator = (
        invalid_unicode_encoding&& other
    ) &
    noexcept = default;

    // Core -------------------------------------------------------------------

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const char*
    what ()
    const noexcept override;
}; // class -------------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS iterated_past_end
    : public std::exception
{
public:
    // Constructors and Destructor --------------------------------------------

    iterated_past_end ()
    noexcept = default;

    ~iterated_past_end ()
    override = default;

    // Copy Operations --------------------------------------------------------

    iterated_past_end (
        const iterated_past_end& other
    )
    noexcept = default;

    iterated_past_end&
    operator = (
        const iterated_past_end& other
    ) &
    noexcept = default;

    // Move Operations --------------------------------------------------------

    iterated_past_end (
        iterated_past_end&& other
    )
    noexcept = default;

    iterated_past_end&
    operator = (
        iterated_past_end&& other
    ) &
    noexcept = default;

    // Core -------------------------------------------------------------------

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const char*
    what ()
    const noexcept override;
}; // class -------------------------------------------------------------------

// By Code Point --------------------------------------------------------------

template <
    typename CodeUnit
>
class by_code_point {
}; // class -------------------------------------------------------------------

template <>
class NUX_CONDITIONAL_EXPORT_CLASS by_code_point<char> {
public:
    // Types ------------------------------------------------------------------

    class NUX_CONDITIONAL_EXPORT_CLASS const_iterator {
    public:
        // Types --------------------------------------------------------------

        using difference_type = std::ptrdiff_t;

        using value_type = char;

        using reference = std::iterator_traits<
            std::string_view::const_iterator
        >::reference;

        using iterator_category = std::bidirectional_iterator_tag;

        using iterator_concept = std::bidirectional_iterator_tag;

        // Constructors and Destructor ----------------------------------------

        const_iterator ()
        noexcept = default;

        NUX_CONDITIONAL_EXPORT
        const_iterator (
            std::string_view::const_iterator initial_current_iterator,
            std::string_view::const_iterator initial_end_iterator
        )
        noexcept;

        ~const_iterator ()
        = default;

        // Copy Operations ----------------------------------------------------

        const_iterator (
            const const_iterator& other
        )
        = default;

        const_iterator&
        operator = (
            const const_iterator& other
        ) &
        = default;

        // Move Operations ----------------------------------------------------

        const_iterator (
            const_iterator&& other
        )
        noexcept = default;

        const_iterator&
        operator = (
            const_iterator&& other
        ) &
        noexcept = default;

        // Operator Overloads -------------------------------------------------

        NUX_CONDITIONAL_EXPORT
        reference
        operator * ()
        const;

        NUX_CONDITIONAL_EXPORT
        const_iterator&
        operator ++ ();

        NUX_CONDITIONAL_EXPORT
        const_iterator
        operator ++ (
            int
        );

        NUX_CONDITIONAL_EXPORT
        const const_iterator&
        operator += (
            difference_type offset
        );

        NUX_CONDITIONAL_EXPORT
        const_iterator&
        operator -- ()
        noexcept;

        NUX_CONDITIONAL_EXPORT
        const_iterator
        operator -- (
            int
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        const const_iterator&
        operator -= (
            difference_type offset
        )
        noexcept;

        // Friends ------------------------------------------------------------

        NUX_CONDITIONAL_EXPORT
        friend
        const_iterator
        operator + (
            const const_iterator& iterator,
            difference_type offset
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        const_iterator
        operator + (
            difference_type offset,
            const const_iterator& iterator
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        const_iterator
        operator - (
            const const_iterator& iterator,
            difference_type offset
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        const_iterator
        operator - (
            difference_type offset,
            const const_iterator& iterator
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        bool
        operator == (
            const const_iterator& iterator1,
            const const_iterator& iterator2
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        bool
        operator != (
            const const_iterator& iterator1,
            const const_iterator& iterator2
        )
        noexcept;

    private:
        // Private Data -------------------------------------------------------

        std::string_view::const_iterator m_current_iterator;
        std::string_view::const_iterator m_end_iterator;
    }; // class ---------------------------------------------------------------

    using iterator = const_iterator;

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using reverse_iterator = const_reverse_iterator;

    // Constructors and Destructor --------------------------------------------

    by_code_point ()
    noexcept = default;

    /**
        Description:
            Constructs a <#type>by_code_point</#type> from the given string.

        Parameters:
            string_to_iterate:
                The string to iterate over by code point.
    */
    NUX_CONDITIONAL_EXPORT
    explicit
    by_code_point (
        std::string_view string_to_iterate
    )
    noexcept;

    ~by_code_point ()
    = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>by_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>by_code_point</#type>
                to copy from.
    */
    by_code_point (
        const by_code_point& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>by_code_point</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>by_code_point</#type>
                to copy from.
    */
    by_code_point&
    operator = (
        const by_code_point& other
    ) &
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>by_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>by_code_point</#type>
                to move from.
    */
    by_code_point (
        by_code_point&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>by_code_point</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>by_code_point</#type>
                to move from.
    */
    by_code_point&
    operator = (
        by_code_point&& other
    ) &
    noexcept = default;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Returns a constant iterator to the beginning.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_iterator
    begin ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the end.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_iterator
    end ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the beginning.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_iterator
    cbegin ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the end.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_iterator
    cend ()
    const noexcept;

    /**
        Description:
            Returns a constant reverse iterator to the beginning.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_reverse_iterator
    crbegin ()
    const noexcept;

    /**
        Description:
            Returns a constant reverse iterator to the end.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_reverse_iterator
    crend ()
    const noexcept;

private:
    // Private Data -----------------------------------------------------------

    std::string_view::const_iterator m_begin_iterator;
    std::string_view::const_iterator m_end_iterator;
}; // class -------------------------------------------------------------------

template <>
class NUX_CONDITIONAL_EXPORT_CLASS by_code_point<char8_t> {
public:
    // Types ------------------------------------------------------------------

    class NUX_CONDITIONAL_EXPORT_CLASS const_iterator {
    public:
        // Types --------------------------------------------------------------

        using difference_type = std::ptrdiff_t;

        using value_type = char32_t;

        class NUX_CONDITIONAL_EXPORT_CLASS reference {
        public:
            // Constructors and Destructor ------------------------------------

            NUX_CONDITIONAL_EXPORT
            reference (
                std::u8string_view::const_iterator initial_current_iterator,
                std::u8string_view::const_iterator initial_end_iterator
            )
            noexcept;

            ~reference ()
            = default;

            // Operator Overloads ---------------------------------------------

            NUX_CONDITIONAL_EXPORT
            explicit(false)
            operator char32_t ()
            const;

        private:
            // Private Data ---------------------------------------------------

            std::u8string_view::const_iterator m_current_iterator;
            std::u8string_view::const_iterator m_end_iterator;

            // Private Functions ----------------------------------------------

            NUX_CONDITIONAL_EXPORT
            char32_t
            finish_sequence (
                int sequence_length,
                char32_t initial_code_point_value,
                std::u8string_view::const_iterator i
            )
            const;
        }; // class -----------------------------------------------------------

        using iterator_category = std::bidirectional_iterator_tag;

        using iterator_concept = std::bidirectional_iterator_tag;

        // Constructors and Destructor ----------------------------------------

        const_iterator ()
        noexcept = default;

        NUX_CONDITIONAL_EXPORT
        const_iterator (
            std::u8string_view::const_iterator initial_current_iterator,
            std::u8string_view::const_iterator initial_end_iterator
        )
        noexcept;

        ~const_iterator ()
        = default;

        // Copy Operations ----------------------------------------------------

        const_iterator (
            const const_iterator& other
        )
        = default;

        const_iterator&
        operator = (
            const const_iterator& other
        ) &
        = default;

        // Move Operations ----------------------------------------------------

        const_iterator (
            const_iterator&& other
        )
        noexcept = default;

        const_iterator&
        operator = (
            const_iterator&& other
        ) &
        noexcept = default;

        // Operator Overloads -------------------------------------------------

        NUX_CONDITIONAL_EXPORT
        reference
        operator * ()
        const;

        NUX_CONDITIONAL_EXPORT
        const_iterator&
        operator ++ ();

        NUX_CONDITIONAL_EXPORT
        const_iterator
        operator ++ (
            int
        );

        NUX_CONDITIONAL_EXPORT
        const const_iterator&
        operator += (
            difference_type offset
        );

        NUX_CONDITIONAL_EXPORT
        const_iterator&
        operator -- ()
        noexcept;

        NUX_CONDITIONAL_EXPORT
        const_iterator
        operator -- (
            int
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        const const_iterator&
        operator -= (
            difference_type offset
        )
        noexcept;

        // Friends ------------------------------------------------------------

        NUX_CONDITIONAL_EXPORT
        friend
        const_iterator
        operator + (
            const const_iterator& iterator,
            difference_type offset
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        const_iterator
        operator + (
            difference_type offset,
            const const_iterator& iterator
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        const_iterator
        operator - (
            const const_iterator& iterator,
            difference_type offset
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        const_iterator
        operator - (
            difference_type offset,
            const const_iterator& iterator
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        bool
        operator == (
            const const_iterator& iterator1,
            const const_iterator& iterator2
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        bool
        operator != (
            const const_iterator& iterator1,
            const const_iterator& iterator2
        )
        noexcept;

    private:
        // Private Data -------------------------------------------------------

        std::u8string_view::const_iterator m_current_iterator;
        std::u8string_view::const_iterator m_end_iterator;

        // Private Functions --------------------------------------------------

        NUX_CONDITIONAL_EXPORT
        char32_t
        finish_sequence (
            int sequence_length,
            char32_t initial_code_point_value,
            std::u8string_view::const_iterator i
        )
        const;

        NUX_CONDITIONAL_EXPORT
        char32_t
        finish_sequence (
            int sequence_length,
            char32_t initial_code_point_value,
            std::u8string_view::const_iterator& i
        );

        NUX_CONDITIONAL_EXPORT
        void
        advance ();

        NUX_CONDITIONAL_EXPORT
        void
        advance (
            difference_type offset
        );

        NUX_CONDITIONAL_EXPORT
        void
        retreat ();

        NUX_CONDITIONAL_EXPORT
        void
        retreat (
            difference_type offset
        );
    }; // class ---------------------------------------------------------------

    using iterator = const_iterator;

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using reverse_iterator = const_reverse_iterator;

    // Constructors and Destructor --------------------------------------------

    by_code_point ()
    noexcept = default;

    /**
        Description:
            Constructs a <#type>by_code_point</#type> from the given string.

        Parameters:
            string_to_iterate:
                The string to iterate over by code point.
    */
    NUX_CONDITIONAL_EXPORT
    explicit
    by_code_point (
        std::u8string_view string_to_iterate
    )
    noexcept;

    ~by_code_point ()
    = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>by_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>by_code_point</#type>
                to copy from.
    */
    by_code_point (
        const by_code_point& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>by_code_point</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>by_code_point</#type>
                to copy from.
    */
    by_code_point&
    operator = (
        const by_code_point& other
    ) &
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>by_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>by_code_point</#type>
                to move from.
    */
    by_code_point (
        by_code_point&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>by_code_point</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>by_code_point</#type>
                to move from.
    */
    by_code_point&
    operator = (
        by_code_point&& other
    ) &
    noexcept = default;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Returns a constant iterator to the beginning.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_iterator
    begin ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the end.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_iterator
    end ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the beginning.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_iterator
    cbegin ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the end.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_iterator
    cend ()
    const noexcept;

    /**
        Description:
            Returns a constant reverse iterator to the beginning.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_reverse_iterator
    crbegin ()
    const noexcept;

    /**
        Description:
            Returns a constant reverse iterator to the end.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_reverse_iterator
    crend ()
    const noexcept;

private:
    // Private Data -----------------------------------------------------------

    std::u8string_view::const_iterator m_begin_iterator;
    std::u8string_view::const_iterator m_end_iterator;
}; // class -------------------------------------------------------------------

template <>
class NUX_CONDITIONAL_EXPORT_CLASS by_code_point<char16_t> {
public:
    // Types ------------------------------------------------------------------

    class NUX_CONDITIONAL_EXPORT_CLASS const_iterator {
    public:
        // Types --------------------------------------------------------------

        using difference_type = std::ptrdiff_t;

        using value_type = char32_t;

        class NUX_CONDITIONAL_EXPORT_CLASS reference {
        public:
            // Constructors and Destructor ------------------------------------

            NUX_CONDITIONAL_EXPORT
            explicit
            reference (
                std::u16string_view::const_iterator initial_current_iterator,
                std::u16string_view::const_iterator initial_end_iterator
            )
            noexcept;

            ~reference ()
            = default;

            // Operator Overloads ---------------------------------------------

            NUX_CONDITIONAL_EXPORT
            explicit(false)
            operator char32_t ()
            const;

        private:
            // Private Data ---------------------------------------------------

            std::u16string_view::const_iterator m_current_iterator;
            std::u16string_view::const_iterator m_end_iterator;

            // Private Functions ----------------------------------------------

            NUX_CONDITIONAL_EXPORT
            char32_t
            finish_sequence (
                int sequence_length,
                char32_t initial_code_point_value,
                std::u16string_view::const_iterator i
            )
            const;
        }; // class -----------------------------------------------------------

        using iterator_category = std::bidirectional_iterator_tag;

        using iterator_concept = std::bidirectional_iterator_tag;

        // Constructors and Destructor ----------------------------------------

        const_iterator ()
        noexcept = default;

        NUX_CONDITIONAL_EXPORT
        const_iterator (
            std::u16string_view::const_iterator initial_current_iterator,
            std::u16string_view::const_iterator initial_end_iterator
        )
        noexcept;

        ~const_iterator ()
        = default;

        // Copy Operations ----------------------------------------------------

        const_iterator (
            const const_iterator& other
        )
        = default;

        const_iterator&
        operator = (
            const const_iterator& other
        ) &
        = default;

        // Move Operations ----------------------------------------------------

        const_iterator (
            const_iterator&& other
        )
        noexcept = default;

        const_iterator&
        operator = (
            const_iterator&& other
        ) &
        noexcept = default;

        // Operator Overloads -------------------------------------------------

        NUX_CONDITIONAL_EXPORT
        reference
        operator * ()
        const;

        NUX_CONDITIONAL_EXPORT
        const_iterator&
        operator ++ ();

        NUX_CONDITIONAL_EXPORT
        const_iterator
        operator ++ (
            int
        );

        NUX_CONDITIONAL_EXPORT
        const const_iterator&
        operator += (
            difference_type offset
        );

        NUX_CONDITIONAL_EXPORT
        const_iterator&
        operator -- ()
        noexcept;

        NUX_CONDITIONAL_EXPORT
        const_iterator
        operator -- (
            int
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        const const_iterator&
        operator -= (
            difference_type offset
        )
        noexcept;

        // Friends ------------------------------------------------------------

        NUX_CONDITIONAL_EXPORT
        friend
        const_iterator
        operator + (
            const const_iterator& iterator,
            difference_type offset
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        const_iterator
        operator + (
            difference_type offset,
            const const_iterator& iterator
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        const_iterator
        operator - (
            const const_iterator& iterator,
            difference_type offset
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        const_iterator
        operator - (
            difference_type offset,
            const const_iterator& iterator
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        bool
        operator == (
            const const_iterator& iterator1,
            const const_iterator& iterator2
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        bool
        operator != (
            const const_iterator& iterator1,
            const const_iterator& iterator2
        )
        noexcept;

    private:
        // Private Data -------------------------------------------------------

        std::u16string_view::const_iterator m_current_iterator;
        std::u16string_view::const_iterator m_end_iterator;

        // Private Functions --------------------------------------------------

        NUX_CONDITIONAL_EXPORT
        char32_t
        finish_sequence (
            int sequence_length,
            char32_t initial_code_point_value,
            std::u16string_view::const_iterator i
        )
        const;

        NUX_CONDITIONAL_EXPORT
        char32_t
        finish_sequence (
            int sequence_length,
            char32_t initial_code_point_value,
            std::u16string_view::const_iterator& i
        );

        NUX_CONDITIONAL_EXPORT
        void
        advance ();

        NUX_CONDITIONAL_EXPORT
        void
        advance (
            difference_type offset
        );

        NUX_CONDITIONAL_EXPORT
        void
        retreat ();

        NUX_CONDITIONAL_EXPORT
        void
        retreat (
            difference_type offset
        );
    }; // class ---------------------------------------------------------------

    using iterator = const_iterator;

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using reverse_iterator = const_reverse_iterator;

    // Constructors and Destructor --------------------------------------------

    by_code_point ()
    noexcept = default;

    /**
        Description:
            Constructs a <#type>by_code_point</#type> from the given string.

        Parameters:
            string_to_iterate:
                The string to iterate over by code point.
    */
    NUX_CONDITIONAL_EXPORT
    explicit
    by_code_point (
        std::u16string_view string_to_iterate
    )
    noexcept;

    ~by_code_point ()
    = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>by_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>by_code_point</#type>
                to copy from.
    */
    by_code_point (
        const by_code_point& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>by_code_point</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>by_code_point</#type>
                to copy from.
    */
    by_code_point&
    operator = (
        const by_code_point& other
    ) &
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>by_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>by_code_point</#type>
                to move from.
    */
    by_code_point (
        by_code_point&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>by_code_point</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>by_code_point</#type>
                to move from.
    */
    by_code_point&
    operator = (
        by_code_point&& other
    ) &
    noexcept = default;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Returns a constant iterator to the beginning.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_iterator
    begin ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the end.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_iterator
    end ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the beginning.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_iterator
    cbegin ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the end.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_iterator
    cend ()
    const noexcept;

    /**
        Description:
            Returns a constant reverse iterator to the beginning.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_reverse_iterator
    crbegin ()
    const noexcept;

    /**
        Description:
            Returns a constant reverse iterator to the end.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_reverse_iterator
    crend ()
    const noexcept;

private:
    // Private Data -----------------------------------------------------------

    std::u16string_view::const_iterator m_begin_iterator;
    std::u16string_view::const_iterator m_end_iterator;
}; // class -------------------------------------------------------------------

template <>
class NUX_CONDITIONAL_EXPORT_CLASS by_code_point<char32_t> {
public:
    // Types ------------------------------------------------------------------

    class NUX_CONDITIONAL_EXPORT_CLASS const_iterator {
    public:
        // Types --------------------------------------------------------------

        using difference_type = std::ptrdiff_t;

        using value_type = char32_t;

        using reference = std::iterator_traits<
            std::u32string_view::const_iterator
        >::reference;

        using iterator_category = std::bidirectional_iterator_tag;

        using iterator_concept = std::bidirectional_iterator_tag;

        // Constructors and Destructor ----------------------------------------

        const_iterator ()
        noexcept = default;

        NUX_CONDITIONAL_EXPORT
        const_iterator (
            std::u32string_view::const_iterator initial_current_iterator,
            std::u32string_view::const_iterator initial_end_iterator
        )
        noexcept;

        ~const_iterator ()
        = default;

        // Copy Operations ----------------------------------------------------

        const_iterator (
            const const_iterator& other
        )
        = default;

        const_iterator&
        operator = (
            const const_iterator& other
        ) &
        = default;

        // Move Operations ----------------------------------------------------

        const_iterator (
            const_iterator&& other
        )
        noexcept = default;

        const_iterator&
        operator = (
            const_iterator&& other
        ) &
        noexcept = default;

        // Operator Overloads -------------------------------------------------

        NUX_CONDITIONAL_EXPORT
        reference
        operator * ()
        const;

        NUX_CONDITIONAL_EXPORT
        const_iterator&
        operator ++ ();

        NUX_CONDITIONAL_EXPORT
        const_iterator
        operator ++ (
            int
        );

        NUX_CONDITIONAL_EXPORT
        const const_iterator&
        operator += (
            difference_type offset
        );

        NUX_CONDITIONAL_EXPORT
        const_iterator&
        operator -- ()
        noexcept;

        NUX_CONDITIONAL_EXPORT
        const_iterator
        operator -- (
            int
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        const const_iterator&
        operator -= (
            difference_type offset
        )
        noexcept;

        // Friends ------------------------------------------------------------

        NUX_CONDITIONAL_EXPORT
        friend
        const_iterator
        operator + (
            const const_iterator& iterator,
            difference_type offset
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        const_iterator
        operator + (
            difference_type offset,
            const const_iterator& iterator
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        const_iterator
        operator - (
            const const_iterator& iterator,
            difference_type offset
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        const_iterator
        operator - (
            difference_type offset,
            const const_iterator& iterator
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        bool
        operator == (
            const const_iterator& iterator1,
            const const_iterator& iterator2
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        bool
        operator != (
            const const_iterator& iterator1,
            const const_iterator& iterator2
        )
        noexcept;

    private:
        // Private Data -------------------------------------------------------

        std::u32string_view::const_iterator m_current_iterator;
        std::u32string_view::const_iterator m_end_iterator;
    }; // class ---------------------------------------------------------------

    using iterator = const_iterator;

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using reverse_iterator = const_reverse_iterator;

    // Constructors and Destructor --------------------------------------------

    by_code_point ()
    noexcept = default;

    /**
        Description:
            Constructs a <#type>by_code_point</#type> from the given string.

        Parameters:
            string_to_iterate:
                The string to iterate over by code point.
    */
    NUX_CONDITIONAL_EXPORT
    explicit
    by_code_point (
        std::u32string_view string_to_iterate
    )
    noexcept;

    ~by_code_point ()
    = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>by_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>by_code_point</#type>
                to copy from.
    */
    by_code_point (
        const by_code_point& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>by_code_point</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>by_code_point</#type>
                to copy from.
    */
    by_code_point&
    operator = (
        const by_code_point& other
    ) &
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>by_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>by_code_point</#type>
                to move from.
    */
    by_code_point (
        by_code_point&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>by_code_point</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>by_code_point</#type>
                to move from.
    */
    by_code_point&
    operator = (
        by_code_point&& other
    ) &
    noexcept = default;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Returns a constant iterator to the beginning.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_iterator
    begin ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the end.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_iterator
    end ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the beginning.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_iterator
    cbegin ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the end.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_iterator
    cend ()
    const noexcept;

    /**
        Description:
            Returns a constant reverse iterator to the beginning.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_reverse_iterator
    crbegin ()
    const noexcept;

    /**
        Description:
            Returns a constant reverse iterator to the end.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_reverse_iterator
    crend ()
    const noexcept;

private:
    // Private Data -----------------------------------------------------------

    std::u32string_view::const_iterator m_begin_iterator;
    std::u32string_view::const_iterator m_end_iterator;
}; // class -------------------------------------------------------------------

template <>
class NUX_CONDITIONAL_EXPORT_CLASS by_code_point<wchar_t> {
public:
    // Types ------------------------------------------------------------------

    class NUX_CONDITIONAL_EXPORT_CLASS const_iterator {
    public:
        // Types --------------------------------------------------------------

        using difference_type = std::ptrdiff_t;

        using value_type = char32_t;

        class NUX_CONDITIONAL_EXPORT_CLASS reference {
        public:
            // Constructors and Destructor ------------------------------------

            NUX_CONDITIONAL_EXPORT
            explicit
            reference (
                std::wstring_view::const_iterator initial_current_iterator,
                std::wstring_view::const_iterator initial_end_iterator
            )
            noexcept;

            ~reference ()
            = default;

            // Operator Overloads ---------------------------------------------

            NUX_CONDITIONAL_EXPORT
            explicit(false)
            operator char32_t ()
            const;

        private:
            // Private Data ---------------------------------------------------

            std::wstring_view::const_iterator m_current_iterator;
            std::wstring_view::const_iterator m_end_iterator;

            // Private Functions ----------------------------------------------

            NUX_CONDITIONAL_EXPORT
            char32_t
            finish_sequence (
                int sequence_length,
                char32_t initial_code_point_value,
                std::wstring_view::const_iterator i
            )
            const;
        }; // class -----------------------------------------------------------

        using iterator_category = std::bidirectional_iterator_tag;

        using iterator_concept = std::bidirectional_iterator_tag;

        // Constructors and Destructor ----------------------------------------

        const_iterator ()
        noexcept = default;

        NUX_CONDITIONAL_EXPORT
        const_iterator (
            std::wstring_view::const_iterator initial_current_iterator,
            std::wstring_view::const_iterator initial_end_iterator
        )
        noexcept;

        ~const_iterator ()
        = default;

        // Copy Operations ----------------------------------------------------

        const_iterator (
            const const_iterator& other
        )
        = default;

        const_iterator&
        operator = (
            const const_iterator& other
        ) &
        = default;

        // Move Operations ----------------------------------------------------

        const_iterator (
            const_iterator&& other
        )
        noexcept = default;

        const_iterator&
        operator = (
            const_iterator&& other
        ) &
        noexcept = default;

        // Operator Overloads -------------------------------------------------

        NUX_CONDITIONAL_EXPORT
        reference
        operator * ()
        const;

        NUX_CONDITIONAL_EXPORT
        const_iterator&
        operator ++ ();

        NUX_CONDITIONAL_EXPORT
        const_iterator
        operator ++ (
            int
        );

        NUX_CONDITIONAL_EXPORT
        const const_iterator&
        operator += (
            difference_type offset
        );

        NUX_CONDITIONAL_EXPORT
        const_iterator&
        operator -- ()
        noexcept;

        NUX_CONDITIONAL_EXPORT
        const_iterator
        operator -- (
            int
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        const const_iterator&
        operator -= (
            difference_type offset
        )
        noexcept;

        // Friends ------------------------------------------------------------

        NUX_CONDITIONAL_EXPORT
        friend
        const_iterator
        operator + (
            const const_iterator& iterator,
            difference_type offset
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        const_iterator
        operator + (
            difference_type offset,
            const const_iterator& iterator
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        const_iterator
        operator - (
            const const_iterator& iterator,
            difference_type offset
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        const_iterator
        operator - (
            difference_type offset,
            const const_iterator& iterator
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        bool
        operator == (
            const const_iterator& iterator1,
            const const_iterator& iterator2
        )
        noexcept;

        NUX_CONDITIONAL_EXPORT
        friend
        bool
        operator != (
            const const_iterator& iterator1,
            const const_iterator& iterator2
        )
        noexcept;

    private:
        // Private Data -------------------------------------------------------

        std::wstring_view::const_iterator m_current_iterator;
        std::wstring_view::const_iterator m_end_iterator;

        // Private Functions --------------------------------------------------

        NUX_CONDITIONAL_EXPORT
        char32_t
        finish_sequence (
            int sequence_length,
            char32_t initial_code_point_value,
            std::wstring_view::const_iterator i
        )
        const;

        NUX_CONDITIONAL_EXPORT
        char32_t
        finish_sequence (
            int sequence_length,
            char32_t initial_code_point_value,
            std::wstring_view::const_iterator& i
        );

        NUX_CONDITIONAL_EXPORT
        void
        advance ();

        NUX_CONDITIONAL_EXPORT
        void
        advance (
            difference_type offset
        );

        NUX_CONDITIONAL_EXPORT
        void
        retreat ();

        NUX_CONDITIONAL_EXPORT
        void
        retreat (
            difference_type offset
        );
    }; // class ---------------------------------------------------------------

    using iterator = const_iterator;

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using reverse_iterator = const_reverse_iterator;

    // Constructors and Destructor --------------------------------------------

    by_code_point ()
    noexcept = default;

    /**
        Description:
            Constructs a <#type>by_code_point</#type> from the given string.

        Parameters:
            string_to_iterate:
                The string to iterate over by code point.
    */
    NUX_CONDITIONAL_EXPORT
    explicit
    by_code_point (
        std::wstring_view string_to_iterate
    )
    noexcept;

    ~by_code_point ()
    = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>by_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>by_code_point</#type>
                to copy from.
    */
    by_code_point (
        const by_code_point& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>by_code_point</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>by_code_point</#type>
                to copy from.
    */
    by_code_point&
    operator = (
        const by_code_point& other
    ) &
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>by_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>by_code_point</#type>
                to move from.
    */
    by_code_point (
        by_code_point&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>by_code_point</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>by_code_point</#type>
                to move from.
    */
    by_code_point&
    operator = (
        by_code_point&& other
    ) &
    noexcept = default;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Returns a constant iterator to the beginning.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_iterator
    begin ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the end.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_iterator
    end ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the beginning.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_iterator
    cbegin ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the end.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_iterator
    cend ()
    const noexcept;

    /**
        Description:
            Returns a constant reverse iterator to the beginning.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_reverse_iterator
    crbegin ()
    const noexcept;

    /**
        Description:
            Returns a constant reverse iterator to the end.
    */
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const_reverse_iterator
    crend ()
    const noexcept;

private:
    // Private Data -----------------------------------------------------------

    std::wstring_view::const_iterator m_begin_iterator;
    std::wstring_view::const_iterator m_end_iterator;
}; // class -------------------------------------------------------------------

by_code_point(std::string_view) -> by_code_point<char>;
by_code_point(std::u8string_view) -> by_code_point<char8_t>;
by_code_point(std::u16string_view) -> by_code_point<char16_t>;
by_code_point(std::u32string_view) -> by_code_point<char32_t>;
by_code_point(std::wstring_view) -> by_code_point<wchar_t>;

// Free Functions -------------------------------------------------------------

constexpr
bool
fits_in_7_bits (
    char32_t code_point
)
noexcept
{
    return code_point <= 0b0111'1111;
} // function -----------------------------------------------------------------

constexpr
bool
is_standalone_byte (
    char8_t code_unit
)
noexcept
{
    return fits_in_7_bits(code_unit);
} // function -----------------------------------------------------------------

constexpr
bool
is_leading_byte (
    char8_t code_unit
)
noexcept
{
    return (code_unit >> 5) == 0b110
        || (code_unit >> 4) == 0b1110
        || (code_unit >> 3) == 0b11110;
} // function -----------------------------------------------------------------

constexpr
bool
is_trailing_byte (
    char8_t code_unit
)
noexcept
{
    return (code_unit >> 6) == 0b10;
} // function -----------------------------------------------------------------

constexpr
bool
is_leading_surrogate (
    char16_t code_unit
)
noexcept
{
    return code_unit >= leading_surrogate_minimum_value
        && code_unit <= leading_surrogate_maximum_value;
} // function -----------------------------------------------------------------

constexpr
bool
is_trailing_surrogate (
    char16_t code_unit
)
noexcept
{
    return code_unit >= trailing_surrogate_minimum_value
        && code_unit <= trailing_surrogate_maximum_value;
} // function -----------------------------------------------------------------

constexpr
bool
is_surrogate (
    char16_t code_unit
)
noexcept
{
    return code_unit >= leading_surrogate_minimum_value
        && code_unit <= trailing_surrogate_maximum_value;
} // function -----------------------------------------------------------------

constexpr
bool
is_in_surrogate_range (
    char32_t code_point
)
noexcept
{
    return code_point >= leading_surrogate_minimum_value
        && code_point <= trailing_surrogate_maximum_value;
} // function -----------------------------------------------------------------

constexpr
bool
is_code_point_valid (
    char32_t code_point
)
noexcept
{
    return code_point <= maximum_code_point
        && !is_in_surrogate_range(code_point);
} // function -----------------------------------------------------------------

constexpr
bool
is_whitespace (
    char32_t code_point
)
noexcept
{
    return code_point == 9
        || code_point == 10
        || code_point == 11
        || code_point == 12
        || code_point == 13
        || code_point == 32
        || code_point == 133
        || code_point == 160
        || code_point == 5760
        || code_point == 8192
        || code_point == 8193
        || code_point == 8194
        || code_point == 8195
        || code_point == 8196
        || code_point == 8197
        || code_point == 8198
        || code_point == 8199
        || code_point == 8200
        || code_point == 8201
        || code_point == 8202
        || code_point == 8232
        || code_point == 8233
        || code_point == 8239
        || code_point == 8287
        || code_point == 12288;
} // function -----------------------------------------------------------------

constexpr
bool
is_radix_digit (
    char32_t character,
    unsigned int radix
)
noexcept
{
    if (radix < 10) {
        return character >= '0' && character < ('0' + radix);
    } else {
        char32_t lowercase_character{
            static_cast<char32_t>(
                std::tolower(static_cast<int>(character))
            )
        };
        return (character >= '0' && character <= '9')
            || (
                lowercase_character >= 'a'
                    && lowercase_character < ('a' + radix - 10)
            );
    }
} // function -----------------------------------------------------------------

NUX_CONDITIONAL_EXPORT
std::size_t
string_size (
    const std::string& s
)
noexcept;

NUX_CONDITIONAL_EXPORT
std::size_t
string_size (
    const std::u8string& s
)
noexcept;

NUX_CONDITIONAL_EXPORT
std::size_t
string_size (
    const std::u16string& s
)
noexcept;

NUX_CONDITIONAL_EXPORT
std::size_t
string_size (
    const std::u32string& s
)
noexcept;

NUX_CONDITIONAL_EXPORT
std::size_t
string_size (
    const std::wstring& s
)
noexcept;

NUX_CONDITIONAL_EXPORT
std::size_t
string_size (
    const std::string_view& s
)
noexcept;

NUX_CONDITIONAL_EXPORT
std::size_t
string_size (
    const std::u8string_view& s
)
noexcept;

NUX_CONDITIONAL_EXPORT
std::size_t
string_size (
    const std::u16string_view& s
)
noexcept;

NUX_CONDITIONAL_EXPORT
std::size_t
string_size (
    const std::u32string_view& s
)
noexcept;

NUX_CONDITIONAL_EXPORT
std::size_t
string_size (
    const std::wstring_view& s
)
noexcept;

NUX_CONDITIONAL_EXPORT
std::size_t
string_size (
    const char* s
)
noexcept;

NUX_CONDITIONAL_EXPORT
std::size_t
string_size (
    const char8_t* s
)
noexcept;

NUX_CONDITIONAL_EXPORT
std::size_t
string_size (
    const char16_t* s
)
noexcept;

NUX_CONDITIONAL_EXPORT
std::size_t
string_size (
    const char32_t* s
)
noexcept;

NUX_CONDITIONAL_EXPORT
std::size_t
string_size (
    const wchar_t* s
)
noexcept;

template <
    typename TargetString
>
void
insert_code_point (
    TargetString& s,
    char32_t code_point,
    typename TargetString::size_type index
) {
    if constexpr (std::is_same_v<TargetString, std::string>) {
        s.insert(index, 1, static_cast<char>(code_point));
    } else if constexpr (std::is_same_v<TargetString, std::u8string>) {
        if (!is_code_point_valid(code_point)) {
            throw invalid_code_point{};
        }
        if (fits_in_7_bits(code_point)) {
            s.insert(index, 1, static_cast<char8_t>(code_point));
        } else if (code_point <= 0b0111'1111'1111) {
            s.insert(
                index++,
                1,
                static_cast<char8_t>(
                    (code_point >> 6) | 0b1100'0000
                )
            );
            s.insert(
                index,
                1,
                static_cast<char8_t>(
                    (code_point & 0b0011'1111) | 0b1000'0000
                )
            );
        } else if (code_point <= 0b1111'1111'1111'1111) {
            s.insert(
                index++,
                1,
                static_cast<char8_t>(
                    (code_point >> 12) | 0b1110'0000
                )
            );
            s.insert(
                index++,
                1,
                static_cast<char8_t>(
                    ((code_point >> 6) & 0b0011'1111) | 0b1000'0000
                )
            );
            s.insert(
                index,
                1,
                static_cast<char8_t>(
                    (code_point & 0b0011'1111) | 0b1000'0000
                )
            );
        } else {
            s.insert(
                index++,
                1,
                static_cast<char8_t>(
                    (code_point >> 18) | 0b1111'0000
                )
            );
            s.insert(
                index++,
                1,
                static_cast<char8_t>(
                    ((code_point >> 12) & 0b0011'1111) | 0b1000'0000
                )
            );
            s.insert(
                index++,
                1,
                static_cast<char8_t>(
                    ((code_point >> 6) & 0b0011'1111) | 0b1000'0000
                )
            );
            s.insert(
                index,
                1,
                static_cast<char8_t>(
                    (code_point & 0b0011'1111) | 0b1000'0000
                )
            );
        }
    } else if constexpr (
        std::is_same_v<TargetString, std::u16string>
            || (
                   std::is_same_v<TargetString, std::wstring>
                       && sizeof (wchar_t) == 2
               )
    ) {
        if (code_point > maximum_code_point) {
            throw invalid_code_point{};
        }
        if (
            !is_in_surrogate_range(code_point)
                && code_point <= maximum_bmp_code_point
        ) {
            s.insert(index, 1, static_cast<char16_t>(code_point));
        } else {
            code_point -= 0x10000;
            s.insert(
                index++,
                1,
                static_cast<char16_t>(
                    ((0b1111'1111'1100'0000'0000 & code_point) >> 10)
                        + leading_surrogate_minimum_value
                )
            );
            s.insert(
                index,
                1,
                static_cast<char16_t>(
                    (0b0000'0000'0011'1111'1111 & code_point)
                        + trailing_surrogate_minimum_value
                )
            );
        }
    } else if constexpr (
        std::is_same_v<TargetString, std::u32string>
            || (
                   std::is_same_v<TargetString, std::wstring>
                       && sizeof (wchar_t) == 4
               )
    ) {
        s.insert(index, 1, code_point);
    }
} // function -----------------------------------------------------------------

template <
    typename TargetString
>
void
append_code_point (
    TargetString& s,
    char32_t code_point
) {
    insert_code_point(s, code_point, s.size());
} // function -----------------------------------------------------------------

template <
    typename TargetString
>
void
prepend_code_point (
    TargetString& s,
    char32_t code_point
) {
    insert_code_point(s, code_point, 0);
} // function -----------------------------------------------------------------

template <
    typename OutputString,
    typename InputString
>
OutputString
convert_string (
    const InputString& s
) {
    OutputString result;
    result.reserve(string_size(s));
    for (char32_t current_code_point : by_code_point{s}) {
        append_code_point(result, current_code_point);
    }
    return result;
} // function -----------------------------------------------------------------

template <
    typename InputString
>
std::string
to_string (
    const InputString& s
) {
    return convert_string<std::string>(s);
} // function -----------------------------------------------------------------

template <
    typename InputString
>
std::u8string
to_u8string (
    const InputString& s
) {
    return convert_string<std::u8string>(s);
} // function -----------------------------------------------------------------

template <
    typename InputString
>
std::u16string
to_u16string (
    const InputString& s
) {
    return convert_string<std::u16string>(s);
} // function -----------------------------------------------------------------

template <
    typename InputString
>
std::u32string
to_u32string (
    const InputString& s
) {
    return convert_string<std::u32string>(s);
} // function -----------------------------------------------------------------

template <
    typename InputString
>
std::wstring
to_wstring (
    const InputString& s
) {
    return convert_string<std::wstring>(s);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

template <>
inline constexpr bool
std::ranges::enable_view<nux::by_code_point<char>>
    = true;

template <>
inline constexpr bool
std::ranges::enable_borrowed_range<nux::by_code_point<char>>
    = true;

template <>
inline constexpr bool
std::ranges::enable_view<nux::by_code_point<char8_t>>
    = true;

template <>
inline constexpr bool
std::ranges::enable_borrowed_range<nux::by_code_point<char8_t>>
    = true;

template <>
inline constexpr bool
std::ranges::enable_view<nux::by_code_point<char16_t>>
    = true;

template <>
inline constexpr bool
std::ranges::enable_borrowed_range<nux::by_code_point<char16_t>>
    = true;

template <>
inline constexpr bool
std::ranges::enable_view<nux::by_code_point<char32_t>>
    = true;

template <>
inline constexpr bool
std::ranges::enable_borrowed_range<nux::by_code_point<char32_t>>
    = true;

template <>
inline constexpr bool
std::ranges::enable_view<nux::by_code_point<wchar_t>>
    = true;

template <>
inline constexpr bool
std::ranges::enable_borrowed_range<nux::by_code_point<wchar_t>>
    = true;

#endif // NUX_UNICODE_BY_CODE_POINT_HPP_INCLUDED
