/* The cloud stores the common knowledge of users */
/* I don't know what exactly they are, so I leave */
/* this class for sure                            */
//machuan 2018.7.1 create

#ifndef CLOUD_H
#define CLOUD_H
#include <vector>
#include <string>
class Cloud
{
public:
  static Cloud Instance()
  {
    return cloud;
  }

  //PK stores the public keys of the active users each turn
  //It should be updated each turn
  //std::vector <Class*> PK;
  std::vector <std::string> PK;

  std::vector <int> active;
  
  int activeN;

private:
  Cloud() 
  {
    activeN = 0;
    active.clear();
    PK.clear();
  };
  Cloud(Cloud& copy) {};
  static Cloud cloud;


};
Cloud Cloud::cloud;

#endif // !CLOUD_H
