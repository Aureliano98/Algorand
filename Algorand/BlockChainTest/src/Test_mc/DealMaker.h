/* The DealMaker should make a new deal and create a block according to that */

//machuan 2018.6.29 create

#ifndef DEALMAKER_H
#define DEALMAKER_H
#include "Block.h"
#include "sha256.h"
class DealMaker
{
public:

  //payment:(pk, pk', money, not sensitive information, sensitive information)
  std::string MakeADeal(Software from, Software to, int money, std::string publicInfo, std::string secretInfo) 
  {
  	return SIG(from.MyPubkey + to.MyPriKey + std::string(money) + publicInfo + hashToBinaryString(secretInfo));
  };
};
#endif // !DEALMAKER_H

