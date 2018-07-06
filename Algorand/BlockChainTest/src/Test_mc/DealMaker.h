/* The DealMaker should make a new deal and create a block according to that */

//machuan 2018.6.29 create
/* This class should do all the works about how to make a deal */
/* Including */
#ifndef DEALMAKER_H
#define DEALMAKER_H
#include "Block.h"
#include "sortition.h"
#include "Cloud.h"
#include "UserData.h"
#include "boost/timer/timer.hpp"
#include "../sha256_ckw/sha256.h"
#include "../BA_Protocol/Player.h"
#include "../BA_Protocol/GCProtocol.h"
#include "../BA_Protocol/BBAProtocol.h"
#include "../Signiture_qdl/SignatureBasedOnRSA.h"
#include <string>
using namespace Signature;
class DealMaker
{
public:
  DealMaker(int *n1,int *t1,BlockChain* chain,UserKey* key,UserData* data)
  {
    n = n1;
    t = t1;
    m_blockchain = chain;
    m_userKey = key;
  }
  //Test only
  Block* MakeADeal(...) 
  {
    boost::timer::cpu_timer timer;
    std::string result = "";
    Block* newBlock = new Block(result);
    return newBlock;
  }

  //payment:(pk, pk', money, not sensitive information, sensitive information)
  std::string Payment(const int from, const int to, int money,
							const std::string& publicInfo,const std::string& secretInfo)
	{
		return m_userKey->Sign(hashToBinaryString(sha256(Cloud::Instance().PK[from].IntoBinaryS() + Cloud::Instance().PK[to].IntoBinaryS() + std::to_string(money) +
					publicInfo + hashToBinaryString(sha256(secretInfo))))).IntoBinaryS();
	};

  static void Agreement() {};
  void Verify(int round)
  {
    r = round;
    if (m_sortition.verifyPotential(m_userKey, m_blockchain, r, s))
      PList.push_back(new Player(m_data->m_identifier, *n, *t, m_data->m_type == m_data->Honest ? true : false));
  }

  //Storing all the payment the user make
  std::vector<std::string> m_payments;

private:
  //round and step
  int r, s;
  int *n, *t;
  std::vector<Player*> PList;
  Sortition m_sortition;
  UserData* m_data;
  BlockChain* m_blockchain;
  UserKey* m_userKey;
};

#endif // !DEALMAKER_H

