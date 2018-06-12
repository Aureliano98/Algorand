//machuan 2018.6.2 create
//machuan 2018.6.12 add operator =,and copy constructor
#ifndef BLOCK_H
#define BLOCK_H
#include "Block_GetHash.h"
#include <string>
#include <cstdio>
#include <time.h>
class Block
{
public:
  Block(const char* msg,unsigned long long timesteps)
  {
    pre = NULL;
    next = NULL;
    c_hash.clear();
    c_hash = GetHash();
    c_time.clear();
    AddTimeStamp(timesteps);
    m_savedata.assign(msg);
  }

  
  virtual ~Block()
  {
    delete pre;
    delete next;
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

  //the hash method
  Block_GetHash GetHash;

public:

  Block* pre;

  Block* next;

  std::string m_savedata;

  std::string c_hash;

  std::string c_time;
private:

  void AddTimeStamp(unsigned long long timesteps)
  {
    char* buffer;
    sprintf(buffer, "%d", timesteps);
    c_time.assign(buffer);
  }


};
#endif // !BLOCK_H
