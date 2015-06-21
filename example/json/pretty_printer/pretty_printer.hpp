#ifndef TRIAL_PROTOCOL_JSON_EXAMPLE_PRETTY_PRINTER_HPP
#define TRIAL_PROTOCOL_JSON_EXAMPLE_PRETTY_PRINTER_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/json/reader.hpp>
#include <trial/protocol/json/writer.hpp>

namespace trial
{
namespace protocol
{
namespace json
{
namespace example
{

class pretty_printer
{
public:
    pretty_printer(json::reader reader, json::writer writer)
        : reader(reader),
          writer(writer),
          indent_width(4)
    {
    }

    void print()
    {
        // Print outer scope
        switch (type())
        {
        case json::token::begin_array:
            print_array(false);
            break;

        case json::token::end_array:
            throw json::error(make_error_code(json::unbalanced_end_array));

        case json::token::begin_object:
            print_object(false);
            break;

        case json::token::end_object:
            throw json::error(make_error_code(json::unbalanced_end_object));

        default:
            print_value();
            break;
        }
        newline();
    }

private:
    void print_array(bool do_indent)
    {
        assert(reader.type() == json::token::begin_array);

        if (do_indent)
            indent(reader.level());
        writer.literal("[");
        newline();

        int count = 0;
        while (reader.next())
        {
            if (reader.type() == json::token::end_array)
                break;
            print_array_element(count);
            ++count;
        }

        if (reader.type() != json::token::end_array)
            throw json::error(make_error_code(json::expected_end_array));
        newline();
        indent(reader.level() - 1);
        writer.literal("]");
    }

    void print_array_element(int count)
    {
        switch (type())
        {
        case json::token::begin_array:
            if (count > 0)
            {
                writer.literal(",");
                newline();
            }
            print_array(true);
            break;

        case json::token::end_array:
            break;

        case json::token::begin_object:
            if (count > 0)
            {
                writer.literal(",");
                newline();
            }
            print_object(true);
            break;

        case json::token::end_object:
            throw json::error(make_error_code(json::unbalanced_end_object));

        default:
            if (count > 0)
            {
                writer.literal(",");
                newline();
            }
            indent(reader.level());
            print_value();
            break;
        }
    }

    void print_object(bool do_indent)
    {
        assert(reader.type() == json::token::begin_object);

        if (do_indent)
            indent(reader.level());
        writer.literal("{");
        newline();

        int count = 0;
        while (reader.next())
        {
            if (reader.type() == json::token::end_object)
                break;
            print_object_element(count);
            ++count;
        }

        if (reader.type() != json::token::end_object)
            throw json::error(make_error_code(json::expected_end_object));
        newline();
        indent(reader.level() - 1);
        writer.literal("}");
    }

    void print_object_element(int count)
    {
        if (reader.type() != json::token::string)
            throw json::error(make_error_code(json::invalid_key));

        // Print value separator
        if (count > 0)
        {
            writer.literal(",");
            newline();
        }

        json::reader::view_type key = reader.literal();
        if (!reader.next())
            throw json::error(make_error_code(json::invalid_value));

        // Print key
        indent(reader.level());
        writer.literal(key);

        // Print key separator
        writer.literal(" : ");

        // Print value
        switch (reader.type())
        {
        case json::token::begin_array:
            print_array(false);
            break;

        case json::token::begin_object:
            print_object(false);
            break;

        default:
            print_value();
            break;
        }
    }

    void print_value()
    {
        switch (reader.type())
        {
        case json::token::begin_array:
        case json::token::end_array:
        case json::token::begin_object:
        case json::token::end_object:
            assert(false);
            break;

        default:
            writer.literal(reader.literal());
            break;
        }
    }

    json::token::value type()
    {
        json::token::value token = reader.type();
        if (token == json::token::end)
            throw json::error(reader.error());
        return token;
    }

    void indent(int level)
    {
        writer.literal(std::string(indent_width * level, ' '));
    }

    void newline()
    {
        writer.literal("\n");
    }

private:
    json::reader reader;
    json::writer writer;
    int indent_width;
};

} // namespace example
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_EXAMPLE_PRETTY_PRINTER_HPP
