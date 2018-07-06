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

    BBAP a(PList);
    a.corruptPlayers(5);
    a.calcBBAP();
    return 0;
}