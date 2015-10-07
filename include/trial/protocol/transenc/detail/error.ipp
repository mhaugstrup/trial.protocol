#ifndef TRIAL_PROTOCOL_TRANSENC_ERROR_IPP
#define TRIAL_PROTOCOL_TRANSENC_ERROR_IPP

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

namespace trial
{
namespace protocol
{
namespace transenc
{

namespace detail
{

class error_category : public boost::system::error_category
{
public:
    const char *name() const BOOST_SYSTEM_NOEXCEPT
    {
        return "trial.protocol.transenc";
    }

    std::string message(int value) const
    {
        switch (value)
        {
        case unknown_token:
            return "unknown token";

        case unexpected_token:
            return "unexpected token";

        case negative_length:
            return "negative length";

        case overflow:
            return "overflow";

        case invalid_value:
            return "invalid value";

        case incompatible_type:
            return "incompatible type";

        case expected_end_record:
            return "expected end record bracket";

        case expected_end_array:
            return "expected end array bracket";

        case expected_end_assoc_array:
            return "expected end assoc array bracket";
        }
        return "trial.protocol.json error";
    }
};

} // namespace detail

inline const boost::system::error_category& error_category()
{
    static detail::error_category instance;
    return instance;
}
} // namespace transenc
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_TRANSENC_ERROR_IPP
