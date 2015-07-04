#ifndef TRIAL_PROTOCOL_JSON_SERIALIZATION_OARCHIVE_HPP
#define TRIAL_PROTOCOL_JSON_SERIALIZATION_OARCHIVE_HPP

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
#include <boost/archive/detail/common_oarchive.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <trial/protocol/json/writer.hpp>

namespace trial
{
namespace protocol
{
namespace json
{

template <typename CharT>
class basic_oarchive
    : public boost::archive::detail::common_oarchive< basic_oarchive<CharT> >
{
    friend class boost::archive::save_access;

public:
    typedef typename json::basic_writer<CharT>::buffer_type buffer_type;

    basic_oarchive(buffer_type&);

    template <typename T>
    void save(const T& data);

    template<typename T>
    void save_override(const T& data);

    // String literal
    void save_override(const char *data);

    // Ignore these
    void save_override(const boost::archive::version_type) {}
    void save_override(const boost::archive::object_id_type) {}
    void save_override(const boost::archive::object_reference_type) {}
    void save_override(const boost::archive::class_id_type) {}
    void save_override(const boost::archive::class_id_optional_type) {}
    void save_override(const boost::archive::class_id_reference_type) {}
    void save_override(const boost::archive::tracking_type) {}
    void save_override(const boost::archive::class_name_type&) {}

protected:
    json::basic_writer<CharT> writer;
};

typedef basic_oarchive<char> oarchive;

} // namespace json
} // namespace protocol
} // namespace trial

BOOST_SERIALIZATION_REGISTER_ARCHIVE(trial::protocol::json::oarchive);

#include <trial/protocol/json/serialization/detail/oarchive.ipp>

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_OARCHIVE_HPP