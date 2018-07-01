/* The cloud stores the common knowledge of users */
/* I don't know what exactly they are, so I leave */
/* this class for sure                            */
//machuan 2018.7.1 create

#ifndef CLOUD_H
#define CLOUD_H
#include <vector>
class Cloud
{
public:
  Cloud* Instance()
  {
    return cloud;
  }

  const std::vector<Class*>& GetPK() const
  {
    return PK;
  }
private:
  Cloud() {};
  Cloud(Cloud& copy) {};
  Cloud* cloud;

  //PK stores the public keys of the active users each turn
  //It should be updated each turn
  std::vector <Class*> PK;
};
#endif // !CLOUD_H
