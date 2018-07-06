#ifndef USERDATA_H
#define USERDATA_H
class Software;
class DealMaker;
class User;
class Player;
class UserData
{
public:
  enum Type
  {
    Honest,
    Adverse,
    Attack
  };

  UserData()
  {
    m_identifier = c_Id++;
    m_type = Honest;
  }
  friend Software;
  friend DealMaker;
  friend User;
  friend Player;
private:
  //use the number of users to give identifier
  //c_Id shows how many users have been created
  static int c_Id;

  //to identify the users
  int m_identifier;

  Type m_type;

};
int UserData::c_Id = 0;
#endif // !USERDATA_H
