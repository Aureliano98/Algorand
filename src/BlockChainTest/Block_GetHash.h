//Change the whole class to implement the hash algorithm in the block
#pragma once
#include <time.h>
#include <cstdio>
#include <cstdlib>
class Block_GetHash
{
public:
  const char* operator() ()
  {
    srand(time(NULL));
    int tmp = rand();
    char* buffer;
    sprintf(buffer, "%d", tmp);
    return buffer;
  };
};