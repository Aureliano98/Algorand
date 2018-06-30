//machuan 2018.6.2 create
//machuan 2018.6.12 add operator =,and copy constructor
//machuan 2018.6.29 edit the distructor to avoid bug

#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include <cstdio>
#include <time.h>
#include "sha256.h"

class Block
{
public:
  Block(std::string msg,time_t timesteps,Block* Prev)
  {
    pre = Prev;
	next = NULL;
	Prev->next = this;

	round = Prev->round + 1;

	m_savedata = msg;

    //wait for SIG function to update seed

	std::string preString = std::to_string(Prev->round) + Prev->m_savedata + Prev->seed + Prev->c_hash;
    c_hash.clear();
	c_hash.assign(hashToBinaryString(sha256(preString)));

    c_time = &timesteps;
  }


  virtual ~Block()
  {
  }

  //please only use this for initialization
  Block& operator = (const Block& right)
  {
    m_savedata = right.m_savedata;
    c_hash = right.c_hash;
    c_time = right.c_time;
  };

  Block(Block& copy)
  {
    pre = NULL;
    next = NULL;
    c_hash = copy.c_hash;
    c_time = copy.c_time;
    m_savedata = copy.m_savedata;
  };

protected:

public:

  Block* pre;

  Block* next;

  int round;

  std::string m_savedata;

  std::string seed;

  std::string c_hash;

  time_t* c_time;
};
#endif // !BLOCK_H
