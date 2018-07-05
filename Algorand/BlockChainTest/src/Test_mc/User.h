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
//class Attacker;
class User
{
public:
  //friend class Attacker;
  friend class Test;
  User(int* n1,int* t1):m_data(),m_software(n,t,&m_data)
  {
    n = n1;
    t = t1;
  }

  //To create a deal message and then ask for a creation of blocks
  void CreatPay(int receiver, int payment, const std::string& pubInfo,const std::string& scrInfo)
  {
    if (!Cloud::Instance().active[m_data.c_Id])
    {
      Cloud::Instance().activeN++;
      Cloud::Instance().active[m_data.c_Id] = true;
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

  void SaveBlockChain()
  {
    char buffer[25];
    sprintf_s(buffer, "data//%d", m_data.m_identifier);
    std::ofstream fout(buffer);
    m_software.SaveBlockChain(fout);
  }

protected:

  //All the users should be intialized by the first block
  void SetFirstBlock(Block* first)
  {
    m_software.SetFirstBlock(first);
  }

private:
  int *n, *t;
  // software holds all the datas and measures
  Software m_software;
  UserData m_data;
  User(User&) :m_software(NULL,NULL,NULL){};
  User& operator = (const User& user) {};
};

#endif // !USER_H

