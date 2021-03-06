#ifndef TRIAL_DYNAMIC_ALGORITHM_VISIT_HPP
#define TRIAL_DYNAMIC_ALGORITHM_VISIT_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/dynamic/variable.hpp>

namespace trial
{
namespace dynamic
{

// Mutable visitation

template <typename Visitor, template <typename> class Allocator>
auto visit(Visitor&& visitor, basic_variable<Allocator>& variable)
    -> decltype(std::forward<Visitor>(visitor).operator()(variable.template unsafe_get<nullable>()))
{
    using variable_type = basic_variable<Allocator>;

    switch (variable.code())
    {
    case token::code::null:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<nullable>());
    case token::code::boolean:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<bool>());
    case token::code::signed_char:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<signed char>());
    case token::code::unsigned_char:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<unsigned char>());
    case token::code::signed_short_integer:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<signed short int>());
    case token::code::unsigned_short_integer:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<unsigned short int>());
    case token::code::signed_integer:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<signed int>());
    case token::code::unsigned_integer:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<unsigned int>());
    case token::code::signed_long_integer:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<signed long int>());
    case token::code::unsigned_long_integer:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<unsigned long int>());
    case token::code::signed_long_long_integer:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<signed long long int>());
    case token::code::unsigned_long_long_integer:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<unsigned long long int>());
    case token::code::real:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<float>());
    case token::code::long_real:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<double>());
    case token::code::long_long_real:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<long double>());
    case token::code::string:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<typename variable_type::string_type>());
    case token::code::wstring:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<typename variable_type::wstring_type>());
    case token::code::u16string:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<typename variable_type::u16string_type>());
    case token::code::u32string:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<typename variable_type::u32string_type>());
    case token::code::array:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<typename variable_type::array_type>());
    case token::code::map:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<typename variable_type::map_type>());
    }
    TRIAL_DYNAMIC_UNREACHABLE();
}

// Const visitation

template <typename Visitor, template <typename> class Allocator>
auto visit(Visitor&& visitor, const basic_variable<Allocator>& variable)
    -> decltype(std::forward<Visitor>(visitor).operator()(variable.template unsafe_get<nullable>()))
{
    using variable_type = basic_variable<Allocator>;

    switch (variable.code())
    {
    case token::code::null:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<nullable>());
    case token::code::boolean:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<bool>());
    case token::code::signed_char:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<signed char>());
    case token::code::unsigned_char:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<unsigned char>());
    case token::code::signed_short_integer:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<signed short int>());
    case token::code::unsigned_short_integer:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<unsigned short int>());
    case token::code::signed_integer:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<signed int>());
    case token::code::unsigned_integer:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<unsigned int>());
    case token::code::signed_long_integer:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<signed long int>());
    case token::code::unsigned_long_integer:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<unsigned long int>());
    case token::code::signed_long_long_integer:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<signed long long int>());
    case token::code::unsigned_long_long_integer:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<unsigned long long int>());
    case token::code::real:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<float>());
    case token::code::long_real:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<double>());
    case token::code::long_long_real:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<long double>());
    case token::code::string:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<typename variable_type::string_type>());
    case token::code::wstring:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<typename variable_type::wstring_type>());
    case token::code::u16string:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<typename variable_type::u16string_type>());
    case token::code::u32string:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<typename variable_type::u32string_type>());
    case token::code::array:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<typename variable_type::array_type>());
    case token::code::map:
        return std::forward<Visitor>(visitor)(variable.template unsafe_get<typename variable_type::map_type>());
    }
    TRIAL_DYNAMIC_UNREACHABLE();
}

} // namespace dynamic
} // namespace trial

#endif // TRIAL_DYNAMIC_ALGORITHM_VISIT_HPP
