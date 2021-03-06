/* A software is where we hold all the datas */
/* A software is bond to a certain user */

//machuan 2018.6.29 create
//mc 2018.7.1 remove bug from SetFirstBlock class

#ifndef SOFTWARE_H
#define SOFTWARE_H

#include "UserKey.h"
#include "BlockChain.h"
#include "Signiture.h"
#include "UserData.h"
//#include "DealMaker.h"
#include "Cloud.h"
#include <string>
#include <vector>
#include <fstream>

/*
//MSG is a structure which stores a kind of msg and count the times you get it
template<class T>
struct MSG
{
  MSG() :msg_msg() 
  {
    msg_count = 0;
  }
  MSG(T msg) : msg_msg(msg)
  {
    msg_count = 0;
  }
  T msg_msg;
  int msg_count;
  bool operator == (const MSG<T>& right)
  {
    return (*this == right);
  }
};
*/

class Sortition;
class Test;
class Player;

class Software
{

public:

  friend Test;
  friend Sortition;
  friend Player;
  //friend DealMaker;

  Software(UserData* data) :m_data(data),m_blockchain(),m_userKey()
  {
    m_money = 100;
    m_round = 0;
    s_softwarelist.push_back(this);
  }
  
  ~Software()
  {
  }
  
  //Use for initialize
  void SetFirstBlock(Block* first)
  {
    Block* copy = new Block(*first);
    m_blockchain.AddHead(copy);
  }

  //cjw AddPay
  void AddPay(int receiver, int payment, const std::string& publicInfo,const std::string& secretInfo)
  {
    if (m_money < payment)
      return;
    
    m_payments.push_back(Payment(m_data->m_identifier,receiver,payment,publicInfo,secretInfo));
  }
  
  int GetMoney() const
  {
    return m_money;
  }

  void PrintBlockChain()
  {
    m_blockchain.ViewBlockChain();
  }
  
  void SaveBlockChain(std::ofstream& fout)
  {
    m_blockchain.PrintBlockChain(fout);
    m_round++;
  }
  
  /*
  template<class T>
  void SendMSG(MSG<T>& msg, int identifier) const
  {
    s_softwarelist[identifier]->GetMSG(msg);
  }
  //???
  void GetMSG(MSG<Block*>& msg) const
  {
    //???
  }

  //???
  void GetMSG(MSG<std::string>& msg)const
  {
    //???
  }
  */
private:

  std::string Payment(const int from, const int to, int money,
    const std::string& publicInfo, const std::string& secretInfo)
  {
    return m_userKey.Sign(hashToBinaryString(sha256(Cloud::Instance().PK[from]->IntoBinaryS() + Cloud::Instance().PK[to]->IntoBinaryS() + std::to_string(money) +
      publicInfo + hashToBinaryString(sha256(secretInfo))))).IntoBinaryS();
  }

  //software should communicate freely with each other, so I create a list
  //the original method is to create an observer
  //this should do the same thing
  static std::vector<Software*> s_softwarelist;
  
  std::vector<std::string> m_payments;

  UserData* m_data;

  BlockChain m_blockchain;

  //the Dealmaker should try to make deal and create a new block
  //DealMaker m_dealmaker;

  // The class includes both the private and the public keys and the functions
  //to create them
  UserKey m_userKey;

  int m_money;

  //count each round
  int m_round;
  
};
std::vector <Software*> Software::s_softwarelist;
#endif // !SOFTWARE_H

