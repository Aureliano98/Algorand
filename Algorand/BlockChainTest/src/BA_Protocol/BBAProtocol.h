/*
*   Binary Byzantine agreement Protocol
*   Kevin Chen - 29/6/18
*   outi = either 0 or 1 for all honest players
*
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
std::vector<Player*> &PList;
GCP gc;

public:
BBAP(std::vector<Player*> &_PList):PList(_PList), n(_PList.size()), gc(_PList)
{
}
~BBAP(){}
void corruptPlayers(int _t)
{
    t = _t;
    gc.playerCorrupt(_t);
}
void updatePList(std::vector<Player*> &_PList, int _t)
{
    PList = _PList;
    t = _t;
    gc.update(_PList, _t);
}
void sendMsg()
{
    gc.sendMsg();
}
void calcBBAP();

void step2(std::vector<Player*> _PList, int _t)
{
    updatePList(_PList, _t);
    gc.calcInitV();
    sendMsg();
}
void step3(std::vector<Player*> _PList, int _t)
{
    updatePList(_PList, _t);
    //std::cout << "update\n";
    gc.allCheck();
    //std::cout << "check\n";
    sendMsg();
    //std::cout << "sent\n";
}
void step4(std::vector<Player*> _PList, int _t)
{
    updatePList(_PList, _t);
    gc.output();
    sendMsg();
}
void stepS(int s, std::vector<Player*> _PList, int _t)
{
    updatePList(_PList, _t);
    if((s - 2) % 3 == 0)
    {

    }
    else if((s - 2) % 3 == 1)
    {

    }
    else
    {

    }
    sendMsg();
}
void mod0();
void mod1();
void mod2();
void checkOutput()
{
    gc.checkOutput();
}
};

void BBAP::mod0()
{
    for (int i = 0; i < n; i ++)
    {
        PList[i]->coin0();
    }
}
void BBAP::mod1()
{
    for (int i = 0; i < n; i ++)
    {
        PList[i]->coin1();
    }
}
void BBAP::mod2()
{
    for (int i = 0; i < n; i ++)
    {
        PList[i]->coinFlip();
    }
}
#endif

