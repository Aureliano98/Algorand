// message_base.h: base class of block message.
// Author: LYL
// Last update: 2018/5/29

#pragma once
#include "xalgorand.h"
#include <boost/multiprecision/cpp_int.hpp>

ALGORAND_BEGIN
// Concrete message classes should inherit this class.
// TODO: maybe there are other compulsory interfaces
class MessageBase {
public:
    ~MessageBase() = default;
    virtual uint256_t hash() const = 0;
};

inline uint256_t hash(const MessageBase &msg) {
    return msg.hash();
}
ALGORAND_END
