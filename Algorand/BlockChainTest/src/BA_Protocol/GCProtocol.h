/*
*   Graded Concensus Protocol
*   Kevin Chen - 29/6/18
*   Each player i outputs a pair (v,g)
*   Used via composition? or in 
*
*/
#ifndef GCP_H_
#define GCP_H_
#include <vector>
#include <iostream>
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Player.h"


class GCP
{
private:
int n, t = 0;
std::vector<Player*> &PList;

public:
GCP(std::vector<Player*> &_PList):PList(_PList), n(_PList.size())
{
    srand(time(NULL));
}
~GCP(){}

void playerCorrupt(int _t);
void update(std::vector<Player*> &_PList, int _t)
{
    PList = _PList;
    t = _t;
}

void calcInitV();


//void generatePlayers();
std::vector<Player*>& transferPlist(){return PList;}
void sendMsg();
void allCheck();
void calcVG();
void output();
void checkOutput(int c = 0);
};

void GCP::playerCorrupt(int _t)
{
    t = _t;
    int count = 0, target;
    while (count < t)
    {
        target = rand() % n;
        if(PList[target]->isHonest())
        {
            PList[target]->corrupt();
            count ++;
        }
    }
}

void GCP::calcInitV()
{
    for(int i = 0; i < n; i ++)
    {
        PList[i]->findV(PList, t);
    }
    return;
}
void GCP::sendMsg()
{
    //std::cout << "send\n";
    for(int i = 0; i < n; i ++)
    {
        PList[i]->clearMsg();
    }
    for(int i = 0; i < n; i ++)
    {
        PList[i]->msg(PList);
    }
}
void GCP::allCheck()
{
    for(int i = 0; i < n; i ++)
    {
        PList[i]->check();
    }
}
void GCP::output() //output determination
{
    for(int i = 0; i < n; i ++)
    {
        PList[i]->outDet();
    }
}
void GCP::checkOutput(int c) //output determination
{
    for(int i = 0; i < n; i ++)
    {
        PList[i]->print(c);
    }
}
void GCP::calcVG()
{
    calcInitV();
    //std::cout << "calcInit\n";
    sendMsg();
    //std::cout << "msg1\n";
    allCheck();
    //std::cout << "check\n";
    sendMsg();
    //std::cout << "msg2\n";
    output();
    checkOutput();
}
#endif