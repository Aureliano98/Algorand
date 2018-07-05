// main.cpp: the code snippets for verifier / leader selection
// Author: LYL
// Last edit: 2018/7/6

#include "xalgorand.h"
#include <iostream>
#include <random>
#include <boost/container_hash/hash.hpp>

using namespace std;
ALGORAND_USING;

using boost::multiprecision::hash_value;
using boost::hash_value;

ALGORAND_BEGIN
using key_type = void *;    // for exposition; TODO: change this
using binary_string = vector<bool>;
using big_sig_type = tuple<size_t, binary_string, binary_string>;

namespace detail {
    template<typename InIt>
    binary_string to_binary_string(InIt first, InIt last) {
        binary_string str;
        for (; first != last; ++first)
            str.push_back(static_cast<bool>(*first));
        return str;
    }
}

template<typename Ty>
decltype(auto) get_big_sig_type_index(Ty &&x) {
    return (get<0>(forward<Ty>(x)));
}

template<typename Ty>
decltype(auto) get_big_sig_type_message(Ty &&x) {
    return (get<1>(forward<Ty>(x)));
}

template<typename Ty>
decltype(auto) get_big_sig_type_hash_value(Ty &&x) {
    return (get<2>(forward<Ty>(x)));
}

binary_string to_binary_string(const std::string &s) {
    return detail::to_binary_string(s.begin(), s.end());
}

binary_string to_binary_string(const ALGORAND uint256_t &x) {
    return to_binary_string(x.str());
}

binary_string to_binary_string(const big_sig_type &x) {
    binary_string str = to_binary_string(
        boost::lexical_cast<string>(get_big_sig_type_index(x)));
    copy(get_big_sig_type_message(x).cbegin(),
        get_big_sig_type_message(x).cend(),
        back_inserter(str));
    copy(get_big_sig_type_hash_value(x).cbegin(),
        get_big_sig_type_hash_value(x).cend(),
        back_inserter(str));
    return str;
}

// i.e. the S function (p.8)
// TODO: change this with actual signing algorithm.
binary_string sign(const ALGORAND uint256_t &hm, const key_type &priv_key) {
    return binary_string();
}

binary_string small_sig(const binary_string &m, const key_type &priv_key) {
    return sign(boost::hash_value(m), priv_key);
}

// SIG of this form is the same as p.9
big_sig_type big_sig(size_t i, const binary_string &m, const key_type &priv_key) {
    return big_sig_type(i, m, small_sig(m, priv_key));
}

// May not be correct. In the essay this is denoted as
// SIG_{l^r}(Q^{r-1})
big_sig_type big_sig(size_t i, const ALGORAND uint256_t &x) {
    return big_sig_type(i, to_binary_string(x), binary_string());
}

ALGORAND uint256_t get_credential(size_t i, const binary_string &m, const key_type &priv_key) {
    return hash_value(big_sig(i, m, priv_key));
}
ALGORAND_END

// Shows the parts that are relevant to verifier and leader selection in 
// MC's Test project.
int main() {
    //constexpr ptrdiff_t traceback_k = 1; // Set k as needed

    size_t num_users, max_rounds;
    cin >> num_users >> max_rounds;

    default_random_engine eng(random_device{}());
    uniform_real_distribution<> random(0, 1);

    // User info, may be encapsulated in some user class
    // TODO: replace these
    vector<key_type> priv_keys(num_users);
    vector<key_type> public_keys(num_users);
    vector<binary_string> messages(num_users);

    // The seed Q^(r-1) = hash_value(active_public_keys^(r-1))
    // Dunno what should the init value should be
    uint256_t seed = 0;
    //vector<uint256_t> active_public_keys;
    vector<uint256_t> credentials;
    vector<size_t> verifiers;

    for (size_t r = 0; r != max_rounds; ++r) {
        //active_public_keys.clear();
        verifiers.clear();
        
        // Each user gets his SIG_i
        for (size_t i = 0; i != num_users; ++i) {
            credentials[i] = get_credential(i, messages[i], priv_keys[i]);
        }
        
        // Select $(leader)
        size_t leader = min_element(credentials.cbegin(), credentials.cend()) - credentials.cbegin();
        
        // Select $(verifiers)
        for (size_t i = 0; i = credentials.size(); ++i) {
            binary_string str = to_binary_string(credentials[i]);
            auto value = to_double(cbegin(str), cend(str));
            auto x = random(eng);
            if (value <= x)
                verifiers.push_back(i);
        }

        bool is_new_block_empty = false;
        // The leader constructs a new block, then runs BA
        // is_new_block_empty should be set finally


        // Update seed
        if (!is_new_block_empty) {
            // Note: the pseudocode on https://www.jianshu.com/p/900374cd7eab
            // is not consistent with the paper (p.30). Below complies with
            // the paper.
            auto bin_str = to_binary_string(big_sig(leader, seed));
            auto str = to_binary_string(to_string(r));
            copy(begin(str), end(str), back_inserter(bin_str));
            seed = hash_value(bin_str);
        } else {
            seed = hash_value(seed.str() + to_string(r));
        }
    }

    system("pause");
    return 0;

}
