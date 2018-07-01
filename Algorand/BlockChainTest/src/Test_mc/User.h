/* User class offers the basic user */

//machuan 2018.6.2 create
//machuan 2018.6.12 add comments and GetBlockChain
//machuan 2018.6.29 move almost all the storages into Software.h

#ifndef USER_H
#define USER_H

#include "Software.h"
#include <string>
#include <time.h>

class Attacker;
class User
{
public:
  friend class Attacker;

  User()
  {
    m_identifier = c_Id++;
    m_type = Honest;
    m_software.BondUser(this);
  }

  enum Type
  {
    Honest,
    Adverse,
    Attack
  };
  
  //To create a deal message and then ask for a creation of blocks
  void MakeADeal(int identifier,int bill) 
  {
    m_software.MakeADeal(m_identifier,identifier, bill);
  };

  Type GetType() const
  {
    return m_type;
  }

  int GetMoney() const
  {
    return m_software.GetMoney();
  }
  
  int GetId() const
  {
    return m_identifier;
  }

  //All the users should be intialized by the first block
  void SetFirstBlock(Block* first)
  {
    m_software.SetFirstBlock(first);
  }
  
  void PrintBlockChain()
  {
    m_software.PrintBlockChain();
  }

protected:

  //use the number of users to give identifier
  //c_Id shows how many users have been created
  static int c_Id;

  //to identify the users
  int m_identifier;
  
  Type m_type;
 
private:

  // software holds all the datas and measures
  Software m_software;
 
  User(User&) {};
  User& operator = (const User& user) {};
};
#endif // !USER_H

