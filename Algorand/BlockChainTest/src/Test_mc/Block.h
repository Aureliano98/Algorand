//machuan 2018.6.2 create
//machuan 2018.6.12 add operator =,and copy constructor
//machuan 2018.6.29 edit the distructor to avoid bug
//cjw 2018.6.30 change the constructor and the hash method
//mc 2018.7.1 change the constructors

#ifndef BLOCK_H

#define BLOCK_H
#include <string>
#include <cstdio>
#include <time.h>
#include <cassert>
#include "../sha256_ckw/sha256.h"
class Block
{
public:
  //The first block
  Block()
  {
    pre = NULL;
    next = NULL;

    round = 0;

    m_savedata.clear();

    //This part need to be changed
    //I don't know how to set the first seed and hash
    srand(time(NULL));
    char buffer[10];
    sprintf_s(buffer, "%d", rand() % 10000000000);
    std::string str = buffer;
    c_hash.clear();
    c_hash.assign(hashToHexString(sha256(str)));
  }

  //A block is based on the last one
  Block(std::string msg,Block* Prev)
  {
    assert(Prev);
    pre = Prev;
	  next = NULL;
	  Prev->next = this;


	  round = Prev->round + 1;

	  m_savedata = msg;

    //wait for SIG function to update seed

	  std::string preString = std::to_string(Prev->round) + Prev->m_savedata + Prev->seed + Prev->c_hash;
      c_hash.clear();
	  c_hash.assign(hashToHexString(sha256(preString)));
  }
  
  //Test only
  Block(std::string msg)
  {
    pre = NULL;
    next = NULL;

    round = 0;

    m_savedata.clear();
    m_savedata = msg;

    srand(time(NULL));
    char buffer[10];
    sprintf_s(buffer, "%d", rand() % 10000000000);
    std::string str = buffer;
    c_hash.clear();
    c_hash.assign(hashToHexString(sha256(str)));
  }

  ~Block() {};

  //please only use this for initialization
  Block& operator = (const Block& right)
  {
    m_savedata = right.m_savedata;
    c_hash = right.c_hash;
  };


  Block(Block& copy)
  {
    pre = copy.pre;
    next = copy.next;
    c_hash = copy.c_hash;
    m_savedata = copy.m_savedata;
  };

  //Block.h is only one component of BlockChain
  //It shouldn't be anywhere else

  bool operator == (const Block& right)
  {
    if (right.m_savedata == m_savedata && right.pre == pre && right.next == next
      && right.round == round && right.seed == seed && right.c_hash == c_hash)
      return true;
    else
      return false;
  }
public:

  Block* pre;

  Block* next;

  int round;

  //The savedata contains all the payment
  std::string m_savedata;

  std::string seed;

  std::string c_hash;

  //Use this to create a blank block
  const static std::string VoidMsg;
};
const std::string Block::VoidMsg = "";
#endif // !BLOCK_H
