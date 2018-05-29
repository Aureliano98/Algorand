// test_block.cpp: unit test for class Block.
// Author: LYL
// Last update: 2018/5/29

#include "block.h"
#include <random>
using namespace std;
ALGORAND_USING;

namespace {
    class MyMessage : public MessageBase {
    public:
        explicit MyMessage(const uint256_t &num) : _num(num) {}
        virtual uint256_t hash() const override {
            return _num;
        }
    protected:
        uint256_t _num;
    };
}

int main() {
    using DefaultBlock = Block<allocator<void>>;
    constexpr size_t test_size = 16;

    cout << "Testing algorand::detail::get_skip_height:" << endl;
    for (size_t i = 0; i != test_size; ++i)
        cout << "algorand::detail::get_skip_height(" << i << ") == " <<
        ALGORAND detail::get_skip_height(i) << endl;

    cout << endl << "Building chain:" << endl;
    vector<shared_ptr<DefaultBlock>> blocks;
    blocks.push_back(make_shared<DefaultBlock>(nullptr, nullptr, 0));
    blocks.back()->messages.push_back(make_shared<MyMessage>(0));
    //cout << "prev=" << blocks.back()->prev << ", skip=" << blocks.back()->skip << endl;

    for (size_t i = 1; i != test_size; ++i) {
        blocks.push_back(make_shared<DefaultBlock>(addressof(*blocks.back()), 
            nullptr, blocks.back()->height + 1));
        blocks.back()->messages.push_back(make_shared<MyMessage>(i));
        blocks.rbegin()[1]->next = addressof(*blocks.back());
        //cout << "prev=" << blocks.back()->prev << ", skip=" << blocks.back()->skip << endl;
    }
    for (auto &&b : blocks) {
        cout << *b << ", ";
        if (b->skip)
            cout << "skip->height=" << b->skip->height << endl;
        else
            cout << "skip=nullptr" << endl;
    }

    cout << endl << "Testing last_common_ancestor:" << endl;
    mt19937 eng(random_device{}());
    uniform_int_distribution<size_t> rand_int(0, blocks.size() - 1);
    for (size_t i = 0; i != 16; ++i) {
        auto x = blocks[rand_int(eng)];
        auto y = blocks[rand_int(eng)];
        cout << "last_common_ancestor(" << x->height << ", " << y->height << ") == " << 
            last_common_ancestor(addressof(*x), addressof(*y))->height << endl;
    }
    
    system("pause");
    return 0;
}