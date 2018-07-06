/* This ask for a class to generate keys for users */

//machuan 2018.6.29 create
//machuan 2018.7.1 add class Class and several keys for ephemeral keys

#ifndef USERKEY_H
#define USERKEY_H
#include "Cloud.h"
#include "MRandom.h"
#include "../Signiture_qdl/SignatureBasedOnRSA.h"
#include <string>
#include <vector>
#include <fstream>
class UserKey : protected SignatureBasedOnRSA
{
public:
  static const enum Pos
  {
    pub = 0,
    scr = 1,
    mod = 2
  };
  using SignatureBasedOnRSA::Sign;
  using SignatureBasedOnRSA::SignatureBasedOnRSA;
 

  UserKey():SignatureBasedOnRSA(fin)
  {

    Cloud::Instance().PK.push_back(rsa.E);
    Cloud::Instance().PK.push_back(rsa.N);
  }

  ~UserKey()
  {
    fin.close();
  }

  void GenerateMasterKey() {};

  BigInteger& key(int pos)
  {
    switch(pos)
    {
    case pub:
      return rsa.E;
      break;
    
    case scr:
      return rsa.D;
      break;
    
    case mod:
      return rsa.N;
      break;
    }
  }
  /*
  void GenerateKey(BigInteger& pKey, BigInteger& sKey,BigInteger& Mod)
  {
    Create(pKey, sKey);
  }
  */
  //two kind of keys
  //Class is a class qdl create to store the big number of keys
  //It is not finished yet
  //BigInteger key[3];
  //std::string pub_key, scr_key;

  //You can change the name of these ephemeral keys
  //Class PMK, SMK;
  //std::vector <Class*> pk, sk;

  BigInteger MK[3];
  //std::string PMK, SMK;

private:

  static std::ifstream fin;

private:

  /*
  //Test only
  void Create(std::string& pKey, std::string& sKey)
  {
    int p, s;
    
    p = MRandom::RandInt(0, 1000000);
    s = MRandom::RandInt(0, 1000000);

    pKey = std::to_string(p);
    sKey = std::to_string(s);
  }
*/
  //bool isCreated;
};

std::ifstream UserKey::fin("../key/PrimeSet");
#endif // !USERKEY_H

