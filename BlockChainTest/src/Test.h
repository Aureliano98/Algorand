//machuan 2018.6.2 create
//machuan 2018.6.12 add comments, GetUsers, GetAttackers
//machuan 2018.6.28 change the AddDeal() to adapt the new AddDeal in Software.h

#include "User.h"
#include "Attacker.h"
#ifndef TEST_H
#define TEST_H
#include <vector>
#include <time.h>
class Test
{
public:
  Test() {};

  virtual ~Test()
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
 }
  
  //Add a specific user
  void AddUsers(User* user)
  {
    c_Users.push_back(user);
  }

  //Add a bunch of users
  void AddUsers(int number)
  {
    for (int i = 0; i < number; ++i)
      c_Users.push_back(new User());
  }

  //Add a specific Attacker
  void AddAttackers(Attacker* attacker)
  {
    c_Attackers.push_back(attacker);
  }

  //Add a bunch of Attackers
  void AddAttackers(int number)
  {
    for (int i = 0; i < number; ++i)
      c_Attackers.push_back(new Attacker());
  }

  //This should save all the datas into the harddrive
  //But how? and save what ?
  virtual void SaveData() {};

  //This will cause a formation of a random deal
  //with random users and random money
  void AddDeal()
  {
    int userA = 0, userB = 0;
    userA = RandUser();
    userB = RandUser();
    while (userA == userB)
    {
      userB = RandUser();
    }
    c_Users[userA]->MakeADeal(c_Users[userB]->GetId(), RandMoney(c_Users[userA]->GetMoney()));
  }

  //How to attack?
  virtual void Attack() {};

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

protected:
  //Give a random User index [0,c_Users.size())
  int RandUser() const
  {
    srand(time(NULL));
    return rand() % c_Users.size();
  }
  //Give the random money [1,maximum];
  int RandMoney(int maximum) const
  {
    srand(time(NULL));
    return rand() % maximum + 1;
  }

  //Maybe a mistake will occur
  //Return 0 means correct, 1 means mistake
  bool Mistake(int percents = 0) const
  {
    srand(time(NULL));
    int random = rand() % 101;
    return random > percents ? false : true;
  }
  
private:
  void operator = (Test&) {};
  Test(Test&) {};

  //current Users
  std::vector<User*> c_Users;
  //current Attackers
  std::vector<Attacker*> c_Attackers;
};
#endif //!TEST_H