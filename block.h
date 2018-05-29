// block.h: basic Block class
// Author: LYL
// Last update: 2018/5/29

#pragma once
#include "xalgorand.h"
#include "message_base.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>
#include <memory>
#include <vector>
#include <cassert>
#include <iostream>

ALGORAND_BEGIN
namespace detail {
    template<typename Integer>
    inline Integer reset_lowest_bit(Integer x) {
        return x & (x - 1);
    }

    // Computes what height to jump back to with the Block::skip pointer. 
    // The heuristic function is copied from bitcoin/src/chain.
    template<typename Integer>
    inline Integer get_skip_height(Integer height) {
        if (height < 2)
            return 0;
        return (height & 1) ? reset_lowest_bit(
            reset_lowest_bit(height - 1)) + 1 : reset_lowest_bit(height);
    }
}

// Resembles bitcoin/src/chain.
// Alloc is used as allocator of vector $(messages), which may boost
// performance. For development, just use std::allocator<void>.
template<typename Alloc>
class Block {
    using Self = Block;

public:
    // Dunno if clock precision suffices.
    using clock_type = typename std::chrono::steady_clock;
    using time_point = typename clock_type::time_point;
    using MessageAllocator = typename std::allocator_traits<Alloc>::
        template rebind_alloc<std::shared_ptr<MessageBase>>;
    // using allocator = Alloc;

    // Sets: prev, next, height, prev_hash (if prev != nullptr), skip (if prev != nullptr), 
    // timestamp.
    template<typename OtherAlloc = MessageAllocator>
    Block(Self *prev, Self *next, size_t height, OtherAlloc &&alloc = OtherAlloc()) : 
        prev(prev), next(next), skip(nullptr), height(height), hash(0), prev_hash(0), 
        version(0), merkle_root_hash(0), nonce(0), 
        messages(std::forward<OtherAlloc>(alloc)) {
        if (prev) {
            prev_hash = prev->hash;
            skip = prev->get_ancestor(detail::get_skip_height(height));
        }
        timestamp = clock_type::now();
    }

    const Self *get_ancestor(size_t height) const {
        if (height > this->height) 
            return nullptr;
        
        const Self *index_walk = this;
        int height_walk = this->height;
        while (height_walk > height) {
            int height_skip = detail::get_skip_height(height_walk);
            int height_skip_prev = detail::get_skip_height(height_walk - 1);
            if (index_walk->skip && (height_skip == height ||
                (height_skip > height && !(height_skip_prev < height_skip - 2 &&
                    height_skip_prev >= height)))) {
                // Only follow skip if prev->skip isn't better than skip->prev.
                index_walk = index_walk->skip;
                height_walk = height_skip;
                //height_walk = index_walk->height;
            } else {
                assert(index_walk->prev);
                index_walk = index_walk->prev;
                --height_walk;
            }
        }
        return index_walk;
    }

    Self *get_ancestor(size_t height) {
        return const_cast<Self *>(const_cast<const Self *>(this)->get_ancestor(height));
    }

    // May be helpful for debug.
    friend std::ostream &operator<<(std::ostream &out, const Self &self) {
        return out << "Block(prev=" << self.prev << ", height=" << self.height << 
            ", hash=" << self.hash << ", merkle_root_hash=" << self.merkle_root_hash << ")";
    }
   
    Self *prev, *next, *skip;   // skip: pointer to remote ancestor (skip list)
    size_t height;
    uint256_t hash, prev_hash;  // To compute hash, please refer to bitcoin/merkleblock
    uint32_t version;
    // I did some searching, it seems a block only keeps the hash of merkle root.
    uint256_t merkle_root_hash; 
    time_point timestamp;   // Set automatically
    uint32_t nonce;   
    std::vector<std::shared_ptr<MessageBase>, MessageAllocator> messages;
    // TODO: (not sure) verification status?
};

template<typename Alloc>
const Block<Alloc> *last_common_ancestor(const Block<Alloc> *x, const Block<Alloc> *y) {
    if (x->height > y->height)
        x = x->get_ancestor(y->height);
    else if (y->height > x->height)
        y = y->get_ancestor(x->height);
    while (x != y && x && y)
        x = x->prev, y = y->prev;
    assert(x == y);
    return x;
}
ALGORAND_END