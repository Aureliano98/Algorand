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
int v, n, t;
std::vector<Player> PList;

public:
GCP(int _n, int _t):n(_n), t(_t)
{
    srand(time(NULL));
    v = rand() % 2;
}
~GCP(){}
void generatePlayers();
std::vector<Player>& transferPlist(){return PList;}
void sendMsg();
void allCheck();
void calcVG();
void output();
void checkOutput();
};

void GCP::generatePlayers()
{
    for (int i = 0; i < n - t; i ++)
    {
        Player newPlayer(i, v, n, t);
        PList.push_back(newPlayer);
    }
    for (int i = 0; i < t; i ++)
    {
        Player newPlayer(i, !v/*rand() % 2*/, n, t, false);
        PList.push_back(newPlayer);
    }
    
}
void GCP::sendMsg()
{
    if(PList.empty())
    {
        std::cout << "Error: No player list\n";
        return;
    }
    for(int i = 0; i < PList.size(); i ++)
    {
        PList[i].clearMsg();
    }
    for(int i = 0; i < PList.size(); i ++)
    {
        PList[i].msg(PList);
    }
}
void GCP::allCheck()
{
    for(int i = 0; i < PList.size(); i ++)
    {
        PList[i].check();
    }
}
void GCP::output() //output determination
{
    for(int i = 0; i < PList.size(); i ++)
    {
        PList[i].outDet();
    }
}
void GCP::checkOutput() //output determination
{
    for(int i = 0; i < PList.size(); i ++)
    {
        PList[i].printVG();
    }
}
void GCP::calcVG()
{
    // for (int i = 0; i < 5; i ++) std::cout << rand() % 2;
    // std::cout << "\n";
    generatePlayers();
    //std::cout << "Generated\n";
    sendMsg();
    //std::cout << "Sent round1\n";
    allCheck();
    //std::cout << "Checked\n";
    sendMsg();
    //std::cout << "Sent round2\n";
    output();
    //std::cout << "Output\n";
    //checkOutput();
}
#endif