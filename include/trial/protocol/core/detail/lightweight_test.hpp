#ifndef TRIAL_PROTOCOL_CORE_DETAIL_LIGHTWEIGHT_TEST_HPP
#define TRIAL_PROTOCOL_CORE_DETAIL_LIGHTWEIGHT_TEST_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <algorithm>
#include <iterator>
#include <boost/detail/lightweight_test.hpp>

namespace trial
{
namespace protocol
{
namespace core
{
namespace detail
{

template<class FormattedOutputFunction, class InputIterator1, class InputIterator2>
void test_all_eq_impl(FormattedOutputFunction& output,
                      char const * file, int line, char const * function,
                      InputIterator1 first_begin, InputIterator1 first_end,
                      InputIterator2 second_begin, InputIterator2 second_end)
{
    InputIterator1 first_it = first_begin;
    InputIterator2 second_it = second_begin;
    typename std::iterator_traits<InputIterator1>::difference_type first_index = 0;
    typename std::iterator_traits<InputIterator2>::difference_type second_index = 0;
    std::size_t error_count = 0;
    const std::size_t max_count = 8;
    do
    {
        while ((first_it != first_end) && (second_it != second_end) && (*first_it == *second_it))
        {
            ++first_it;
            ++second_it;
            ++first_index;
            ++second_index;
        }
        if ((first_it == first_end) || (second_it == second_end))
        {
            break; // do-while
        }
        if (error_count == 0)
        {
            output << file << "(" << line << "): Container contents differ in function '" << function << "':";
        }
        else if (error_count >= max_count)
        {
            output << " ...";
            break;
        }
        output << " [" << first_index << "] '" << *first_it << "' != '" << *second_it << "'";
        ++first_it;
        ++second_it;
        ++first_index;
        ++second_index;
        ++error_count;
    } while (first_it != first_end);

    first_index += std::distance(first_it, first_end);
    second_index += std::distance(second_it, second_end);
    if (first_index != second_index)
    {
        if (error_count == 0)
        {
            output << file << "(" << line << "): Container sizes differ in function '" << function << "': size(" << first_index << ") != size(" << second_index << ")";
        }
        else
        {
            output << " [*] size(" << first_index << ") != size(" << second_index << ")";
        }
        ++error_count;
    }

    if (error_count == 0)
    {
        boost::detail::report_errors_remind();
    }
    else
    {
        output << std::endl;
        ++boost::detail::test_errors();
    }
}

template<class FormattedOutputFunction, class InputIterator1, class InputIterator2, typename Predicate>
void test_all_with_impl(FormattedOutputFunction& output,
                        char const * file, int line, char const * function,
                        InputIterator1 first_begin, InputIterator1 first_end,
                        InputIterator2 second_begin, InputIterator2 second_end,
                        Predicate predicate)
{
    InputIterator1 first_it = first_begin;
    InputIterator2 second_it = second_begin;
    typename std::iterator_traits<InputIterator1>::difference_type first_index = 0;
    typename std::iterator_traits<InputIterator2>::difference_type second_index = 0;
    std::size_t error_count = 0;
    const std::size_t max_count = 8;
    do
    {
        while ((first_it != first_end) && (second_it != second_end) && predicate(*first_it, *second_it))
        {
            ++first_it;
            ++second_it;
            ++first_index;
            ++second_index;
        }
        if ((first_it == first_end) || (second_it == second_end))
        {
            break; // do-while
        }
        if (error_count == 0)
        {
            output << file << "(" << line << "): Container contents differ in function '" << function << "':";
        }
        else if (error_count >= max_count)
        {
            output << " ...";
            break;
        }
        output << " [" << first_index << "]";
        ++first_it;
        ++second_it;
        ++first_index;
        ++second_index;
        ++error_count;
    } while (first_it != first_end);

    first_index += std::distance(first_it, first_end);
    second_index += std::distance(second_it, second_end);
    if (first_index != second_index)
    {
        if (error_count == 0)
        {
            output << file << "(" << line << "): Container sizes differ in function '" << function << "': size(" << first_index << ") != size(" << second_index << ")";
        }
        else
        {
            output << " [*] size(" << first_index << ") != size(" << second_index << ")";
        }
        ++error_count;
    }

    if (error_count == 0)
    {
        boost::detail::report_errors_remind();
    }
    else
    {
        output << std::endl;
        ++boost::detail::test_errors();
    }
}

} // namespace detail
} // namespace core
} // namespace protocol
} // namespace trial

#define TRIAL_PROTOCOL_TEST BOOST_TEST
#define TRIAL_PROTOCOL_TEST_EQUAL BOOST_TEST_EQ
#define TRIAL_PROTOCOL_TEST_THROWS BOOST_TEST_THROWS

#define TRIAL_PROTOCOL_TEST_THROW_EQUAL(EXPR, EXCEP, MSG)               \
    try {                                                               \
        EXPR;                                                           \
        ::boost::detail::throw_failed_impl                              \
              (#EXCEP, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION);     \
    }                                                                   \
    catch(EXCEP const& ex) {                                            \
        ::boost::detail::test_eq_impl                                   \
            (#EXPR, #EXPR, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, std::string(ex.what()), MSG); \
    }                                                                   \
    catch(...) {                                                        \
        ::boost::detail::throw_failed_impl                              \
            (#EXCEP, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION);       \
    }

#define TRIAL_PROTOCOL_TEST_NO_THROW(EXPR)                              \
    try {                                                               \
        EXPR;                                                           \
    }                                                                   \
    catch (...) {                                                       \
        const char *msg = "Unexpected exception from '" #EXPR "'";      \
        ::boost::detail::error_impl(msg, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION); \
    }

#define TRIAL_PROTOCOL_TEST_ALL_EQUAL(FIRST_BEGIN, FIRST_END, SECOND_BEGIN, SECOND_END) ::trial::protocol::core::detail::test_all_eq_impl(BOOST_LIGHTWEIGHT_TEST_OSTREAM, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, FIRST_BEGIN, FIRST_END, SECOND_BEGIN, SECOND_END)
#define TRIAL_PROTOCOL_TEST_ALL_WITH(FIRST_BEGIN, FIRST_END, SECOND_BEGIN, SECOND_END, PREDICATE) ::trial::protocol::core::detail::test_all_with_impl(BOOST_LIGHTWEIGHT_TEST_OSTREAM, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, FIRST_BEGIN, FIRST_END, SECOND_BEGIN, SECOND_END, PREDICATE)

#endif // TRIAL_PROTOCOL_CORE_DETAIL_LIGHTWEIGHT_TEST_HPP
