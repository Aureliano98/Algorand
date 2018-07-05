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
using namespace SignatureBasedOnRSA;
class UserKey
{
public:

  UserKey()
  {
    InitKey(fin);
    GetKey(key[mod], key[pub], key[scr]);
    Cloud::Instance().PK.push_back(key[pub]);
    Cloud::Instance().PK.push_back(key[mod]);
  }

  ~UserKey()
  {
    fin.close();
  }

  void GenerateMasterKey()
  {
    InitKey(fin);
    GetKey(MK[mod], MK[pub], MK[scr]);
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
  BigInteger key[3];
  //std::string pub_key, scr_key;

  //You can change the name of these ephemeral keys
  //Class PMK, SMK;
  //std::vector <Class*> pk, sk;

  BigInteger MK[3];
  //std::string PMK, SMK;
public:
  
  static int pub, scr, mod;

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

int UserKey::pub = 0;
int UserKey::scr = 1;
int UserKey::mod = 2;
std::ifstream UserKey::fin("../key/primekey");
#endif // !USERKEY_H

