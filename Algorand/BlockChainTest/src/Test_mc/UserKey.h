/* This ask for a class to generate keys for users */

//machuan 2018.6.29 create
//machuan 2018.7.1 add class Class and several keys for ephemeral keys

#ifndef USERKEY_H
#define USERKEY_H

#include "MRandom.h"
#include <string>
#include <vector>

class UserKey
{
public:

  UserKey()
  {
    isCreated = false;
  }

  //You should determine what parameter do we need
  void CreateUserKey()
  {
    if (!isCreated)
    {
      Create(pub_key,scr_key);
      isCreated = true;
    }
    else
      return;
  }

  void GenerateKey(std::string& pKey,std::string& sKey)
  {
    Create(pKey, sKey);
  }

  //two kind of keys
  //Class is a class qdl create to store the big number of keys
  //It is not finished yet
  //Class pub_key, scr_key;
  std::string pub_key, scr_key;

  //You can change the name of these ephemeral keys
  //Class PMK, SMK;
  //std::vector <Class*> pk, sk;

  
  std::string PMK, SMK;

private:

  //apply the key creation process here
  void Create(...){};

  //Test only
  void Create(std::string& pKey, std::string& sKey)
  {
    int p, s;
    
    p = MRandom::RandInt(0, 1000000);
    s = MRandom::RandInt(0, 1000000);

    pKey = std::to_string(p);
    sKey = std::to_string(s);
  }



  bool isCreated;
};
#endif // !USERKEY_H

