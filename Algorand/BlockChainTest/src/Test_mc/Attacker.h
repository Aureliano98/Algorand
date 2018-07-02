//machuan 2018.6.2 create
//machuan 2018.6.12 add comments
#ifndef ATTACKER_H
#define ATTACKER_H
#include "User.h"
#include <vector>
class Attacker :public User
{
public:
  
  Attacker()
  {
    m_type = User::Type::Attack;
  }

  //Corrupt change the type and add it to a member vector
  void Corrupt(User* corrupted)
  {
    corrupted->m_type = Adverse;
    m_members.push_back(corrupted);
  }

  template <class T>
  void AssignDecision(int sender,int receiver,MSG<T> msg) 
  {
    for (int i = 0; i < m_members.size(); ++i)
    {
      if (m_members[i]->GetId() == sender)
        m_members[i]->m_software.SendMSG(msg, receiver);
    }
  };

private:
  Attacker & operator = (Attacker&) {};
  Attacker(Attacker&) {};
  //the member of corrupted users
  std::vector<User*> m_members;
};
#endif // !ATTACKER_H

