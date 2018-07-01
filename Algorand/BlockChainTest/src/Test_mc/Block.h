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

    srand(time(NULL));
    char buffer[10];
    sprintf_s(buffer, "%d", rand() % 10000000000);
    std::string str = buffer;
    c_hash.clear();
    c_hash.assign(hashToBinaryString(sha256(str)));
  }

  //The rest block is based the last one
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
	  c_hash.assign(hashToBinaryString(sha256(preString)));
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
    c_hash.assign(hashToBinaryString(sha256(str)));
  }

  virtual ~Block()
  {
  }

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
public:

  Block* pre;

  Block* next;

  int round;

  std::string m_savedata;

  std::string seed;

  std::string c_hash;
};
#endif // !BLOCK_H
