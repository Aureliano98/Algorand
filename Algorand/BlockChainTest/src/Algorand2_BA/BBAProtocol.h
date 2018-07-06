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
std::vector<Player> &PList;
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
void updatePList(std::vector<Player> &_PList, int _t)
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

void step1(std::vector<Player> _PList, int _t, int leader)
{
    updatePList(_PList, _t);
    blockPropose(leader);
    sendMsg();
}

void step2(std::vector<Player> _PList, int _t)
{
    updatePList(_PList, _t);
    gc.calcInitV();
    sendMsg();
}
void step3(std::vector<Player> _PList, int _t)
{
    updatePList(_PList, _t);
    //std::cout << "update\n";
    gc.allCheck();
    //std::cout << "check\n";
    sendMsg();
    //std::cout << "sent\n";
}
void step4(std::vector<Player> _PList, int _t)
{
    updatePList(_PList, _t);
    gc.output();
    sendMsg();
}
Block* stepS(int s, std::vector<Player> _PList, int _t)
{
    Block* newBlock = NULL;
    updatePList(_PList, _t);
    if((s - 2) % 3 == 0)
    {
        newBlock = mod0();
        if (newBlock != NULL) return newBlock;
    }
    else if((s - 2) % 3 == 1)
    {
        newBlock = mod1();
        if (newBlock != NULL) return newBlock;
    }
    else
    {
        newBlock = mod2();
        if (newBlock != NULL) return newBlock;
    }
    sendMsg();

}
void blockPropose(int leader);
void mod0();
void mod1();
void mod2();
void checkOutput()
{
    gc.checkOutput();
}
};

void BBAP::blockPropose(int leader)
{
    for (int i = 0; i < n; i ++)
    {
        PList[i].newRound();
        PList[i].propose(PList, leader);
    }
}

Block* BBAP::mod0()
{
    Block* newBlock = NULL;
    for (int i = 0; i < n; i ++)
    {
        newBlock = PList[i].coin0();
        if (newBlock != NULL) return newBlock;
    }
    return NULL;
}
Block* BBAP::mod1()
{
    Block* newBlock = NULL;
    for (int i = 0; i < n; i ++)
    {
        newBlock = PList[i].coin1();
        if (newBlock != NULL) return newBlock;
    }
    return NULL;
}
Block* BBAP::mod2()
{
    Block* newBlock = NULL;
    for (int i = 0; i < n; i ++)
    {
        newBlock = PList[i].coinFlip();
        if (newBlock != NULL) return newBlock;
    }
    return NULL;
}
#endif

