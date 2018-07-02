/* This ask for a class to generate keys for users */

//machuan 2018.6.29 create
//machuan 2018.7.1 add class Class and several keys for ephemeral keys

#ifndef USERKEY_H
#define USERKEY_H

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
  void CreateKey(...)
  {
    if (!isCreated)
    {
      Create();
      isCreated = true;
    }
    else
      return;
  }

  //two kind of keys
  //Class is a class qdl create to store the big number of keys
  //It is not finished yet
  //Class pub_key, scr_key;
  
  //You can change the name of these ephemeral keys
  //Class PMK, SMK;
  //std::vector <Class*> pk, sk;

private:

  //apply the key creation process here
  void Create(...){};

  bool isCreated;
};
#endif // !USERKEY_H

