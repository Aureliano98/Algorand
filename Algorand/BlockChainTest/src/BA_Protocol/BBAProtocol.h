/*
*   Binary Byzantine agreement Protocol
*   Kevin Chen - 29/6/18
*   outi = either 0 or 1 for all honest players
*/
#ifndef BBAP_H_
#define BBAP_H_
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "GCProtocol.h"
#include "Player.h"

class BBAP
{
private:
int n, t = 0;
std::vector<Player> PList;
GCP gc;

public:
BBAP(std::vector<Player> &_PList):PList(_PList), n(_PList.size()), gc(_PList)
{
}
~BBAP(){}
void corruptPlayers(int _t)
{
    t = _t;
    gc.playerCorrupt(_t);
}

void calcBBAP();
/*
void getInitVal();
void step1();
void step2();
void step3();
int outVal();
void checkOutput();
*/
};

void BBAP::calcBBAP()
{
    gc.calcVG();
    // getInitVal();
    // do
    // {   
    //     minHonest = false;
    //     step1();
    //     //std::cout << "step1 fin\n";
    //     step2();
    //     //std::cout << "step2 fin\n";
    //     step3();
    //     //std::cout << "step3 fin\n";
    //     for (int i = 0; i < PList.size(); i ++)
    //     {
    //         if(!PList[i].checkHonesty())
    //         {
    //             minHonest = true;
    //             break;
    //         }
    //     } 
    //     //std::cout << minHonest << "\n";

    //     gamma ++;
    // }while(minHonest && gamma <= 10);
    // //std::cout << "Iterated " << gamma << " times\n";
    // //checkOutput();
    // //std::cout << "out = " << outVal() << "\n";
    return;
}
// void BBAP::getInitVal()
// {
//     for (int i = 0; i <  PList.size(); i ++)
//     {
//         if(PList[i].getPair().second == 2)
//         {
//             PList[i].setV(0);
//         }
//         else
//         {
//             PList[i].setV(1);
//         }

//     }
// }
// void BBAP::step1()
// {
//     for (int i = 0; i < PList.size(); i ++)
//     {
//         PList[i].msg(PList, '1');
//     }
// }
// void BBAP::step2()
// {
//     for (int i = 0; i < PList.size(); i ++)
//     {
//         PList[i].msg(PList, '2');
//     }
// }

// void BBAP::step3()
// {
//     for (int i = 0; i < PList.size(); i ++)
//     {
//         PList[i].msg(PList, '3');
//     }
// }
// int BBAP::outVal()
// {
//     return PList[0].out();
// }

// void BBAP::checkOutput() //output determination
// {
//     for(int i = 0; i < PList.size(); i ++)
//     {
//         PList[i].printMsg();
//     }
// }
#endif

