/* The DealMaker should make a new deal and create a block according to that */

//machuan 2018.6.29 create

#ifndef DEALMAKER_H
#define DEALMAKER_H
#include "Block.h"
class DealMaker
{
public:
  Block * MakeADeal(...) 
  {
    return new Block("",0);
  };

};
#endif // !DEALMAKER_H

