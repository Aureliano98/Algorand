//machuan 2018.6.2 create
//machuan 2018.6.12 add comments, GetUsers, GetAttackers
//machuan 2018.6.28 change the AddDeal() to adapt the new AddDeal in Software.h

#ifndef TEST_H
#define TEST_H
#include "../BA_Protocol/Player.h"
//#include "Attacker.h"
#include "sortition.h"
#include "MRandom.h"
#include "Cloud.h"
#include "../BA_Protocol/BBAProtocol.h"
#include <boost/timer/timer.hpp>
#include <vector>
#include <time.h>
class Test
{
public:
  Test():m_BBAP(PList)
  {
    PList.clear();
    c_Users.clear();
    //c_Attackers.clear();

    firstblock = new Block();

    m_runtime.start();
    
    n = 0; t = 0;
    m = 180;
  };

  ~Test()
 {
   while (c_Users.size() != 0)
   {
     if(c_Users.back() != NULL)
      delete c_Users.back();
     c_Users.pop_back();
   }
   /*
   while (c_Attackers.size() != 0)
   {
     if(c_Attackers.back() != NULL)
      delete c_Attackers.back();
     c_Attackers.pop_back();
   }
    */
   m_runtime.stop();

   delete firstblock;
 }
  
  //Add a specific user
  void AddUser(Player* user)
  {
    n++;
    c_Users.push_back(user);
    user->SetFirstBlock(firstblock);

    Cloud::Instance().AddPlayer(1);
  }

  //Add a bunch of users
  void AddUsers(int number)
  {
    n += number;
    int first = c_Users.size();

    for (int i = 0; i < number; ++i)
    {
      c_Users.push_back(new Player());
    }
    
    Cloud::Instance().AddPlayer(number);
    
    for (int i = first; i < c_Users.size(); ++i)
    {
      c_Users[i]->m_software.SetFirstBlock(firstblock);
    }
    
  }

  /*
  //Add a specific Attacker
  void AddAttacker(Attacker* attacker)
  {
    t += 1;
    
    c_Attackers.push_back(attacker);
    
    attacker->SetFirstBlock(firstblock);
    
    Cloud::Instance().AddPlayer(1);
  }

  //Add a bunch of Attackers
  void AddAttackers(int number)
  {
    t += number;
    int first = c_Attackers.size();

    for (int i = 0; i < number; ++i)
      c_Attackers.push_back(new Attacker());

    Cloud::Instance().AddPlayer(number);

    for (int i = first; i < c_Attackers.size(); ++i)
    {
      c_Attackers[i]->SetFirstBlock(firstblock);
    }
  }
  */

  Player* GetUser(int index)
  {
    if (index >= c_Users.size() || index < 0)
      return NULL;
    else
      return c_Users[index];
  }
/*
  Attacker* GetAttacker(int index)
  {
    if (index >= c_Attackers.size() || index < 0)
      return NULL;
    else
      return c_Attackers[index];
  }
*/
  //Test only
  void PrintAllBlocks()
  {
    for (int i = 0; i < c_Users.size(); ++i)
    {
      printf("User%d:\n", i);
      c_Users[i]->PrintBlockChain();
      std::cout << "====================================" << std::endl;
    }
  }
  
  void Step()
  {
    timestep++;//round

    //Add new users with possibility 1%
    //if (MRandom::RandBool(10))
    //{
    //  AddUsers(1);
    //}
      
    //Then deals will occur
    int num = MRandom::RandInt(0, c_Users.size()/2);
    AddAPay();
    
    Main();
    
    //Save the blocks into .txt files to imitate the saving progress
    SaveData();
  }

protected:
  //This should save all the datas into the harddrive
  //But how? and save what ?
  void SaveData() 
  {
    for (int i = 0; i < c_Users.size(); ++i)
      c_Users[i]->SaveBlockChain();
  };

  //This will cause a formation of a random deal
  //with random users and random money
  void AddAPay()
  {
    //randomly choose two people to make a deal
    int userA = 0, userB = 0;
    userA = MRandom::RandInt(0, c_Users.size());
    userB = MRandom::RandInt(0, c_Users.size());
    while (userA == userB)
    {
      userB = MRandom::RandInt(0, c_Users.size());
    }
    int payment = MRandom::RandInt(1, c_Users[userA]->GetMoney());
    //userA wants to make a deal with userB
    c_Users[userA]->CreatPay(c_Users[userB]->GetId(),-payment, std::to_string(userA), std::to_string(m_runtime.elapsed().wall));
    c_Users[userB]->CreatPay(c_Users[userA]->GetId(),+payment, std::to_string(userA), std::to_string(m_runtime.elapsed().wall));
  }

  //Add several deals
  //with random users and random money
  void AddPays(int num)
  {
    for (int i = 0; i < num; ++i)
    {
      //randomly two people to make a deal
      int userA = 0, userB = 0;
      userA = MRandom::RandInt(0, c_Users.size());
      userB = MRandom::RandInt(0, c_Users.size());
      while (userA == userB)
      {
        userB = MRandom::RandInt(0, c_Users.size());
      }
      int payment = MRandom::RandInt(1, c_Users[userA]->GetMoney());
      //userA wants to make a deal with userB
      c_Users[userA]->CreatPay(c_Users[userB]->GetId(), -payment, std::to_string(userA), std::to_string(m_runtime.elapsed().wall));
      c_Users[userB]->CreatPay(c_Users[userA]->GetId(), +payment, std::to_string(userA), std::to_string(m_runtime.elapsed().wall));
    }
  }

  void Main()
  {
    Block* newBlock = NULL;
    for (int s = 0; s <= m + 2; ++s) {
      //verifiers.clear();
      PList.clear();
      
      int leader;
      // Each user gets his SIG_i
      for (int i = 0; i < n; ++i) {
        //verify players
        m_sortition.verifyVerifier(c_Users[i], PList, timestep, s);

        // Select $(leader)
        leader = m_sortition.verifyLeader(c_Users[i], timestep, i == n - 1 ? true : false);
      }

      //update credentials
      for(int i = 0; i < PList.size(); ++i)
        PList[i]->credentials = m_sortition.getCredential(c_Users[i], timestep, s);

      //BBA*
      switch (s)
      {
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      default:
        break;
      }
      
    }
    if (newBlock == NULL)
    {

    }

    for (int i = 0; i < c_Users.size(); ++i)
    {
      c_Users[i]->m_software.m_blockchain.AddBlock();
    }
  }
 
private:
  void operator = (Test&) {};
  Test(Test& a):m_BBAP(a.PList){};

  static int timestep;

  static boost::timer::cpu_timer m_runtime;

  //current Users
  std::vector<Player*> c_Users;
  //current Attackers
  //std::vector<Attacker*> c_Attackers;

  std::vector<Player*> PList;
  std::vector<std::string> credentials;
  
  Sortition m_sortition;

  BBAP m_BBAP;

  int n, t;

  int m;

  Block* firstblock;
};
int Test::timestep = 0;
boost::timer::cpu_timer Test::m_runtime; 
#endif //!TEST_H