/* The cloud stores the common knowledge of users */
/* I don't know what exactly they are, so I leave */
/* this class for sure                            */
//machuan 2018.7.1 create

#ifndef CLOUD_H
#define CLOUD_H
#include <vector>
#include <string>
#include <cassert>
#include "../Signiture_qdl/BigInteger.h"
class Cloud
{
public:
  static Cloud& Instance()
  {
    return cloud;
  }

  BigInteger& Pk(int index)
  {
    if (active[index])
      return PK[index];
    else
      assert(0);
  }

  BigInteger& PkMod(int index)
  {
    if (active[index])
      return PKMOD[index];
    else
      assert(0);
  }

  void AddPlayer(int num)
  {
    for (int i = 0; i < num; ++i)
      active.push_back(false);
  }

  //PK stores the public keys of the active users each turn
  //It should be updated each turn
  std::vector <BigInteger&> PK, PKMOD;

  std::vector <int> active;

  int activeN;
private:
  Cloud() 
  {
    activeN = 0;
    active.clear();
    PK.clear();
    PKMOD.clear();
  };
 
  Cloud(Cloud& copy) {};
  static Cloud cloud;


};

#endif // !CLOUD_H
