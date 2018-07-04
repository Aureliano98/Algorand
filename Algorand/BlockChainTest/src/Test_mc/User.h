/* User class offers the basic user */

//machuan 2018.6.2 create
//machuan 2018.6.12 add comments and GetBlockChain
//machuan 2018.6.29 move almost all the storages into Software.h

#ifndef USER_H
#define USER_H

#include "Software.h"
#include <string>
#include <time.h>
#include <fstream>
class Test;
class Attacker;
class User
{
public:
  friend class Attacker;
  friend class Test;
  User()
  {
    m_identifier = c_Id++;
    m_type = Honest;
    m_software.BondUser(m_identifier);
  }

  enum Type
  {
    Honest,
    Adverse,
    Attack
  };
  
  //To create a deal message and then ask for a creation of blocks
  void CreatPay(int receiver, int payment, const std::string& pubInfo,const std::string& scrInfo)
  {
    m_software.CreatPay(receiver, payment, pubInfo, scrInfo);
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
  
  void PrintBlockChain()
  {
    m_software.PrintBlockChain();
  }

  void SaveBlockChain()
  {
    char buffer[25];
    sprintf_s(buffer, "data//AUser%d.txt", m_identifier);
    std::ofstream fout(buffer);
    m_software.SaveBlockChain(fout);
  }

protected:

  //All the users should be intialized by the first block
  void SetFirstBlock(Block* first)
  {
    m_software.SetFirstBlock(first);
  }
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
int User::c_Id = 0;
#endif // !USER_H

