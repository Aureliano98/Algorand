/* The DealMaker should make a new deal and create a block according to that */

//machuan 2018.6.29 create
/* This class should do all the works about how to make a deal */
/* Including */
#ifndef DEALMAKER_H
#define DEALMAKER_H
#include "Block.h"
#include "McTimer.h"
#include <string>
class DealMaker
{
public:
  Block* MakeADeal(...) 
  {
    McTimer timer;
    char buffer[10];
    sprintf_s(buffer, "%lf", timer.GetSeconds());
    std::string result = buffer;
    Block* newBlock = new Block(result);
    return newBlock;
  };

};
#endif // !DEALMAKER_H

