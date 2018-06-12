//machuan 2018.6.2 create
//machuan 2018.6.12 add comments and GetBlockChain
#ifndef USER_H
#define USER_H
#include "UserKey.h"
#include "BlockChain.h"
#include <string>
#include <time.h>
class Attacker;
class User
{
public:
  friend class Attacker;

  User()
  {
    m_type = Honest;
    m_money = 100;  
  }

  enum Type
  {
    Honest,
    Adverse,
    Attack
  };
  
  //To create a deal message and then ask for a creation of blocks
  void MakeADeal(User* target,int bill) {};

  Type GetType() const
  {
    return m_type;
  }

  int GetMoney() const
  {
    return m_money;
  }
  
  //All the users should be intialized by the first block
  void SetFistBlock(Block* first)
  {
    m_blockchain.AddHead(first);
  }
  
  //Get the blockchain, it may be out of expectation
  BlockChain& GetBlockChain()  
  {
    return m_blockchain;
  };

protected:
  //Store a block that is being constructed
  Block *u_Block;
  //The class includes both the private and the public keys and the functions
  //to create them
  UserKey userkey;

  //use the number of users to give identifier
  //c_Id shows how many users have been created
  static int c_Id;

  int m_identifier;
  
  Type m_type;

  int m_money;
  
  BlockChain m_blockchain;
private:
  User(User&) {};
  User& operator = (const User& user) {};
};
#endif // !USER_H

