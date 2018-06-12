//machuan 2018.6.2 create 
//machuan 2018.6.12 add comments and initialization of first block
#include <iostream>
#include <time.h>
#include "Test.h"
using namespace std;
int main()
{
  Test testmain;

  int users;
  cout << "Input the number of honest users:";
  cin >> users;
  testmain.AddUsers(users);
  for (int i = 0; i < users; ++i)
  {
    testmain.GetUser(i)->SetFistBlock(new Block("",0));
  }

  int attackers;
  cout << "Input the number of attackers:";
  cin >> attackers;
  testmain.AddAttackers(attackers);
  for (int i = 0; i < attackers; ++i)
  {
    testmain.GetAttacker(i)->SetFistBlock(new Block("", 0));
  }
  
  long long timestep = 0;
  
  while (timestep++)/*how to stop it?*/
  {
    testmain.AddDeal();
    //there should be much more things
  }
  //there should be a saving method
  testmain.SaveData();
  return 0;

}