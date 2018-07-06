/* User class offers the basic user */

//machuan 2018.6.2 create
//machuan 2018.6.12 add comments and GetBlockChain
//machuan 2018.6.29 move almost all the storages into Software.h

#ifndef USER_H
#define USER_H

#include "Software.h"
#include "UserData.h"
#include <string>
#include <time.h>
#include <fstream>
class Test;
class Sortition;
class Player;
//class Attacker;
class User
{
  friend Sortition;
  friend Player;
public:
  //friend class Attacker;
  friend Test;
  User():m_data(),m_software(&m_data)
  {
  }

  //To create a deal message and then ask for a creation of blocks
  void CreatPay(int receiver, int payment, const std::string& pubInfo,const std::string& scrInfo)
  {
    if (!Cloud::Instance().active[m_data.m_identifier])
    {
      Cloud::Instance().activeN++;
      Cloud::Instance().active[m_data.m_identifier] = true;
    } 
    
    if (!Cloud::Instance().active[receiver])
    {
      Cloud::Instance().activeN++;
      Cloud::Instance().active[receiver] = true;
    }

    m_software.AddPay(receiver, payment, pubInfo, scrInfo);
  };

  UserData::Type GetType() const
  {
    return m_data.m_type;
  }

  int GetMoney() const
  {
    return m_software.GetMoney();
  }
  
  int GetId() const
  {
    return m_data.m_identifier;
  }
  
  void PrintBlockChain()
  {
    m_software.PrintBlockChain();
  }

  //All the users should be intialized by the first block
  void SetFirstBlock(Block* first)
  {
    m_software.SetFirstBlock(first);
  }

  void SaveBlockChain()
  {
    char buffer[25];
    sprintf_s(buffer, "data/%d", m_data.m_identifier);
    std::ofstream fout(buffer);
    m_software.SaveBlockChain(fout);
  }

private:
  // software holds all the datas and measures
  Software m_software;
  UserData m_data;
  User(User& a) :m_software(NULL){};
  User& operator = (const User& user) {};
};

#endif // !USER_H

