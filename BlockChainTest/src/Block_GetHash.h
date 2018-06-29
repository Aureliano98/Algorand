//Change the whole class to implement the hash algorithm in the block
//just for test
#pragma once
#include <time.h>
#include <cstdio>
#include <cstdlib>
class Block_GetHash
{
public:
  std::string operator() ()
  {
    srand(time(NULL));
    int tmp = rand();
    char buffer[257];
    sprintf_s(buffer, "%d", tmp);
    std::string hash = buffer;
    return hash;
  };
};