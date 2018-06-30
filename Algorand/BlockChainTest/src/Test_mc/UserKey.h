/* This ask for a class to generate keys for users */

//machuan 2018.6.29 create

#ifndef USERKEY_H
#define USERKEY_H

#include <string>
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
  std::string pub_key, scr_key;

private:

  //apply the key creation process here
  void Create(...){};

  bool isCreated;
};
#endif // !USERKEY_H

