/* The DealMaker should make a new deal and create a block according to that */

//machuan 2018.6.29 create
/* This class should do all the works about how to make a deal */
/* Including */
#ifndef DEALMAKER_H
#define DEALMAKER_H
#include "Block.h"
#include "McTimer.h"
#include "sha256.h"
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
  }

  //payment:(pk, pk', money, not sensitive information, sensitive information)
  std::string MakeADeal(const Software &from, const Software &to, int money,
							const std::string& publicInfo, const std::string& secretInfo)
	{
		return SIG(from.MyPubKey() + to.MyPubKey() + std::to_string(money) +
					publicInfo + hashToBinaryString(sha256(secretInfo)));
	};

};
#endif // !DEALMAKER_H

