/* This class is an adaptor for the boost timer.hpp */
//machuan  2018.6.30
#ifndef MCTIMER_H
#define MCTIMER_H
#include <boost/timer.hpp>
#include <iostream>
using boost::timer;
using std::cout;
class McTimer
{

public:
  McTimer()
  {
    t.restart();
  }

  void Reset()
  {
    t.restart();
  }

  double GetSeconds() const
  {
    return t.elapsed();
  }

private:
  timer t;
};
#endif // !MCTIMER_H
