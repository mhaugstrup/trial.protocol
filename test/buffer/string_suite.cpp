///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/buffer/string.hpp>
#include <trial/protocol/core/detail/lightweight_test.hpp>

using namespace trial::protocol;

//-----------------------------------------------------------------------------
// Helper
//-----------------------------------------------------------------------------

template <typename CharT,
          typename Super = buffer::basic_string<CharT> >
class string_buffer : Super
{
public:
    using value_type = typename Super::value_type;
    using size_type = typename Super::size_type;
    using view_type = typename Super::view_type;

    string_buffer(std::basic_string<CharT>& data)
        : Super(data)
    {
    }

    virtual bool grow(size_type size)
    {
        return Super::grow(size);
    }

    virtual void write(value_type value)
    {
        return Super::write(value);
    }

    virtual void write(const view_type& view)
    {
        return Super::write(view);
    }
};

//-----------------------------------------------------------------------------
// std::string
//-----------------------------------------------------------------------------

namespace string_suite
{

void test_empty()
{
    std::string output;
    string_buffer<char> container(output);
    TRIAL_PROTOCOL_TEST_EQUAL(output, "");
}

void test_single()
{
    std::string output;
    string_buffer<char> container(output);
    TRIAL_PROTOCOL_TEST_EQUAL(container.grow(1), true);
    TRIAL_PROTOCOL_TEST_NO_THROW(container.write('A'));
    TRIAL_PROTOCOL_TEST_EQUAL(output, "A");
}

void test_view()
{
    std::string output;
    string_buffer<char> container(output);
    std::string input = "alpha";
    TRIAL_PROTOCOL_TEST_EQUAL(container.grow(input.size()), true);
    TRIAL_PROTOCOL_TEST_NO_THROW(container.write(input));
    TRIAL_PROTOCOL_TEST_EQUAL(output, input);
}

void test()
{
    test_empty();
    test_single();
    test_view();
}

} // namespace string_suite

//-----------------------------------------------------------------------------
// std::wstring
//-----------------------------------------------------------------------------

namespace wstring_suite
{

void test_empty()
{
    std::wstring output;
    string_buffer<std::wstring::value_type> container(output);
    TRIAL_PROTOCOL_TEST(output == L"");
}

void test_single()
{
    std::wstring output;
    string_buffer<std::wstring::value_type> container(output);
    TRIAL_PROTOCOL_TEST_EQUAL(container.grow(1), true);
    TRIAL_PROTOCOL_TEST_NO_THROW(container.write(L'A'));
    TRIAL_PROTOCOL_TEST(output == L"A");
}

void test_view()
{
    std::wstring output;
    string_buffer<std::wstring::value_type> container(output);
    std::wstring input = L"alpha";
    TRIAL_PROTOCOL_TEST_EQUAL(container.grow(input.size()), true);
    TRIAL_PROTOCOL_TEST_NO_THROW(container.write(input));
    TRIAL_PROTOCOL_TEST(output == input);
}

void test()
{
    test_empty();
    test_single();
    test_view();
}

} // namespace wstring_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    string_suite::test();
    wstring_suite::test();

    return boost::report_errors();
}
