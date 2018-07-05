// xalgorand.h: basics for Algorand project.
// Author: LYL
// Last edit: 2018/7/6

#pragma once
#include <boost/multiprecision/cpp_int.hpp>

// Note: it is recommended to use the following macros to access the namespace
//      in case we need to change the namespace's name.
#define IS_ALGORAND_INLINE false 
#define ALGORAND algorand::
#if IS_ALGORAND_INLINE
#define ALGORAND_BEGIN inline namespace algorand {
#else
#define ALGORAND_BEGIN namespace algorand {
#endif
#define ALGORAND_END }
#define ALGORAND_USING using namespace algorand

ALGORAND_BEGIN
// Alias for hashing
using uint256_t = typename boost::multiprecision::uint256_t;

// Converts binary .xxx to double in [0, 1)
template<typename InIt>
inline double to_double(InIt first, InIt last) {
    double ans = 0, weight = 0.5;
    for (auto i = first; i != last; ++i) {
        ans += boost::lexical_cast<int>(*i) * weight;
        weight /= 2;
    }
    return ans;
}

// Converts binary .xxx to double in [0, 1)
inline double to_double(const uint256_t &n) {
    auto str = n.str();
    return to_double(cbegin(str), cend(str));
}
ALGORAND_END
