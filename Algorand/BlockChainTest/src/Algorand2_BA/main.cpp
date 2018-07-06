#include <iostream>
#include "BBAProtocol.h"
int main(int argc, char *argv[])
{
    std::vector<Player> PList;
    for ( int i = 0; i < 20; i ++)
    {
        Player newPlayer(i);
        PList.push_back(newPlayer);
    }
    PList[1].corrupt();
    PList[3].corrupt();
    PList[4].corrupt();
    PList[7].corrupt();
    PList[10].corrupt();

    BBAP a(PList);
    a.step2(PList, 5);
    //std::cout << "step2\n";
    a.step3(PList, 5);
    //std::cout << "step3\n";
    a.step4(PList, 5);
    //std::cout << "step4\n";

    a.checkOutput();
    return 0;
}