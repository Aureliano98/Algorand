#ifndef MRANDOM_H
#define MRANDOM_H
#include <boost/timer/timer.hpp>

class MRandom
{
public:
  MRandom()
  {
    m_runtime.start();
  }

  ~MRandom()
  {
    m_runtime.stop();
  }

  //Give a random int [minimum,maximum];
  static int RandInt(int minimum, int maximum) 
  {
    srand(m_runtime.elapsed().wall);
    return rand() % maximum + minimum;
  }

  //return random > micros ? false : true
  //random->[0,1000]
  static bool RandBool(int micros = 0) 
  {
    srand(m_runtime.elapsed().wall);
    unsigned int random = rand() % 1001;
    return random > micros ? false : true;
  }

private:
  static boost::timer::cpu_timer m_runtime;
};

#endif //MRANDOM_H
