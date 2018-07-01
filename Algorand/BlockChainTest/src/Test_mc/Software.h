/* A software is where we hold all the datas */
/* A software is bond to a certain user */

//machuan 2018.6.29 create
//mc 2018.7.1 remove bug from SetFirstBlock class

#ifndef SOFTWARE_H
#define SOFTWARE_H

#include "UserKey.h"
#include "BlockChain.h"
#include "DealMaker.h"
#include <string>
#include <vector>
#include <fstream>

class User;
class Sortition;
class Software
{

public:

  friend Sortition;

  Software() 
  {
    isBond = false;
    m_user = NULL;
    m_money = 100;
    s_softwarelist.push_back(this);
  };
  
  ~Software()
  {
  }
  //A software need to have a single user
  void BondUser(User* user) 
  {
    if (!isBond)
    {
      m_user = user;
      isBond = true;
    }
    else
      return;
  };

  //move from user class
  void SetFirstBlock(Block* first)
  {
    Block* copy = new Block(*first);
    m_blockchain.AddHead(copy);
  }

  //Test only
  void MakeADeal(int payer, int receiver, int payment) 
  {
    m_blockchain.AddBlock(m_dealmaker.MakeADeal(payer, receiver, payment));
  }

  /*
  //cjw MakeADeal
  void MakeADeal(Software receiver, int payment, std::string publicInfo, std::string publicInfo, std::string secretInfo) 
  {
    if(m_money < payment)
    {
      std::cout << "No enough money!" << std::endl;
      return;
    }

    m_blockchain.AddBlock(m_dealmaker.MakeADeal(*this, receiver, payment, publicInfo, secretInfo));
  }
  */
  int GetMoney() const
  {
    return m_money;
  }

  //this should be read only but I don't know how to do it.
  // LYL: I think this suffices.
  const Class& MyScrKey() const noexcept
  {
    return m_userKey.scr_key;
  }

  //this should be read only but I don't know how to do it.
  // LYL: I think this suffices.
  const Class& MyPubKey() const noexcept
  {
    return m_userKey.pub_key;
  }
  
  void PrintBlockChain()
  {
    m_blockchain.ViewBlockChain();
  }
  
  void SaveBlockChain(std::ofstream& fout)
  {
    m_blockchain.PrintBlockChain(fout);
  }
  
  

private:

  //bond a single user
  bool isBond;
  User* m_user;
  
  //software should communicate freely with each other, so I create a list
  //the original method is to create an observer
  //this should do the same thing
  static std::vector<Software*> s_softwarelist;

  //Because the one user can build a lot of blocks
  //So the unproven blocks are stored here
  //This can be useless 
  std::vector<Block*> m_WaitingBlocks;

  BlockChain m_blockchain;

  //the Dealmaker should try to make deal and create a new block
  DealMaker m_dealmaker;

  // The class includes both the private and the public keys and the functions
  //to create them
  UserKey m_userKey;

  int m_money;
  
};
#endif // !SOFTWARE_H

