//machuan 2018.6.2 create
//machuan 2018.6.12 add comments, GetUsers, GetAttackers
//machuan 2018.6.28 change the AddDeal() to adapt the new AddDeal in Software.h

#ifndef TEST_H
#define TEST_H
#include "User.h"
#include "Attacker.h"
#include <boost/timer/timer.hpp>
#include <vector>
#include <time.h>
class Test
{
public:
  Test() 
  {
    c_Users.clear();
    c_Attackers.clear();

    firstblock = new Block();

    m_runtime.start();
    
  };

  ~Test()
 {
   while (c_Users.size() != 0)
   {
     if(c_Users.back() != NULL)
      delete c_Users.back();
     c_Users.pop_back();
   }

   while (c_Attackers.size() != 0)
   {
     if(c_Attackers.back() != NULL)
      delete c_Attackers.back();
     c_Attackers.pop_back();
   }

   m_runtime.stop();

   delete firstblock;
 }
  
  //Add a specific user
  void AddUser(User* user)
  {
    c_Users.push_back(user);
    user->SetFirstBlock(firstblock);
  }

  //Add a bunch of users
  void AddUsers(int number)
  {
    int first = c_Users.size();

    for (int i = 0; i < number; ++i)
      c_Users.push_back(new User());

    for (int i = first; i < c_Users.size(); ++i)
    {
      c_Users[i]->SetFirstBlock(firstblock);
    }

  }

  /*
  //Add a specific Attacker
  void AddAttacker(Attacker* attacker)
  {
    c_Attackers.push_back(attacker);
    attacker->SetFirstBlock(firstblock);
  }

  //Add a bunch of Attackers
  void AddAttackers(int number)
  {
    int first = c_Attackers.size();

    for (int i = 0; i < number; ++i)
      c_Attackers.push_back(new Attacker());

    for (int i = first; i < c_Attackers.size(); ++i)
    {
      c_Attackers[i]->SetFirstBlock(firstblock);
    }
  }
  */

  User* GetUser(int index)
  {
    if (index >= c_Users.size() || index < 0)
      return NULL;
    else
      return c_Users[index];
  }

  Attacker* GetAttacker(int index)
  {
    if (index >= c_Attackers.size() || index < 0)
      return NULL;
    else
      return c_Attackers[index];
  }

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
    timestep++;

    //Add new users with possibility 1%
    if (RandBool(10))
    {
      AddUsers(1);
    }
      

    //Then deals will occur
    int num = RandInt(0, c_Users.size());
    AddDeals(num);
    
    //Then we get to an agreement
    //Agreement();
    //A new block should have been added into chain here
    //???();
    //

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
  void AddADeal()
  {
    //randomly choose two people to make a deal
    int userA = 0, userB = 0;
    userA = RandInt(0, c_Users.size());
    userB = RandInt(0, c_Users.size());
    while (userA == userB)
    {
      userB = RandInt(0, c_Users.size());
    }

    //userA wants to make a deal with userB
    c_Users[userA]->MakeADeal(c_Users[userB]->GetId(), RandInt(1,c_Users[userA]->GetMoney()));
  }

  //Add several deals
  //with random users and random money
  void AddDeals(int num)
  {
    for (int i = 0; i < num; ++i)
    {
      //randomly two people to make a deal
      int userA = 0, userB = 0;
      userA = RandInt(0, c_Users.size());
      userB = RandInt(0, c_Users.size());
      while (userA == userB)
      {
        userB = RandInt(0, c_Users.size());
      }
      c_Users[userA]->MakeADeal(c_Users[userB]->GetId(), RandInt(1, c_Users[userA]->GetMoney()));
    }
  }

  //Give a random int [minimum,maximum];
  int RandInt(int minimum,int maximum) const
  {
    srand(m_runtime.elapsed().wall);
    return rand() % maximum + minimum;
  }

  //return random > micros ? false : true
  //random->[0,1000]
  bool RandBool(int micros = 0) const
  {
    srand(m_runtime.elapsed().wall);
    unsigned int random = rand() % 1001;
    return random > micros ? false : true;
  }
  
private:

  void operator = (Test&) {};
  Test(Test&) {};

  static int timestep;

  boost::timer::cpu_timer m_runtime;

  //current Users
  std::vector<User*> c_Users;
  //current Attackers
  std::vector<Attacker*> c_Attackers;

  Block* firstblock;
};
int Test::timestep = 0;
#endif //!TEST_H