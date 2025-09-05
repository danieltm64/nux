// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_CHECK_GROUP_HPP_INCLUDED
#define NUX_CHECK_GROUP_HPP_INCLUDED

#include <nux/widget.hpp>

#include <type_traits>
#include <algorithm>

namespace nux {

template <
    typename T
>
class check_group
{
public:
    // Types ------------------------------------------------------------------

    using element_type = T;

    // Constructors and Destructor --------------------------------------------

    check_group ()
        : m_active_element{nullptr}
    {
    } // function -------------------------------------------------------------

    ~check_group()
    noexcept = default;

    // Copy Operations --------------------------------------------------------

    check_group (
        const check_group& other
    )
    = delete;

    check_group&
    operator = (
        const check_group& other
    )
    = delete;

    // Move Operations --------------------------------------------------------

    check_group (
        check_group&& other
    )
    = default;

    check_group&
    operator = (
        check_group&& other
    )
    = default;

    // Accessors --------------------------------------------------------------

    std::vector<element_type*>&
    grab_elements ()
    noexcept
    {
        return m_elements;
    } // function -------------------------------------------------------------

    const std::vector<element_type*>&
    grab_elements ()
    const noexcept
    {
        return m_elements;
    } // function -------------------------------------------------------------

    element_type*
    get_active_element ()
    noexcept
    {
        return m_active_element;
    } // function -------------------------------------------------------------

    const element_type*
    get_active_element ()
    const noexcept
    {
        return m_active_element;
    } // function -------------------------------------------------------------

    void
    set_active_element (
        element_type& element
    ) {
        auto entry{std::find(m_elements.begin(), m_elements.end(), &element)};
        if (entry != m_elements.end()) {
            if (&element != m_active_element) {
                if (m_active_element) {
                    m_active_element->set_checked(false);
                }
                m_active_element = &element;
                m_active_element->set_checked(true);
            }
        }
    } // function -------------------------------------------------------------

private:
    // Private Data -----------------------------------------------------------

    std::vector<element_type*> m_elements;
    element_type* m_active_element;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif
