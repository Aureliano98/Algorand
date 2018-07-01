//machuan 2018.6.2 create 
//machuan 2018.6.12 add comments and initialization of first block
//machuan 2018.6.29 change the test to the simplest form with no other functions
#include <iostream>
#include <time.h>
#include "Test.h"
using namespace std;
int main()
{
  Test testmain;
  
  cout << "Input the number of honest users: ";
  int users;
  cin >> users;
  testmain.AddUsers(users);

  //The first test program has only honest users
  /*
  int attackers;
  cout << "Input the number of attackers:";
  cin >> attackers;
  testmain.AddAttackers(attackers);
  */
  
  cout << "Input the looping times: ";
  int maxtime = 0;
  cin >> maxtime;

  int timestep = 0;
  while (++timestep <= maxtime)
  {
    testmain.Step();
  }


  testmain.PrintAllBlocks();
  //In the first edition it has no saving function
  /*
  //there should be a saving method
  testmain.SaveData();
  */
  
  system("pause");
  return 0;

}