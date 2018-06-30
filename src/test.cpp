#include "sha256.h"
#include <string>
#include <iostream>
using namespace std;
int main()
{
  for (int i = 0; i < 2; ++i)
  {
    string input;
    cin >> input;
    string output = hashToBinaryString(sha256(input));
    cout << output << endl;
    cout << output.size() << endl;
  }
  system("pause");
  return 0;
}