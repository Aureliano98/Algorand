/*
*   Players using BBA
*   Kevin Chen - 29/6/18
*   outi = either 0 or i for all honest players
*
*/
#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <cstring>

class Player
{
private:
int ID, skip, n, t = 0, y; //
bool aff, halt = false, majHonest = true; //affiliation
std::string message, v, ESIG0, ESIG1, ESIG2;
std::pair <int,int> VGPair;//v can be 0, 1 or a special character that we will represent with 2, G is 0,1, or 2
std::vector<std::string> recieved;

public:
Player(int _ID, bool _aff = true):ID(_ID), aff(_aff)
{
    srand(time(NULL));
}
~Player(){}

void setV(int _v){v = _v;}
void findV(std::vector<Player> &PList, int _t);
std::pair <int, int> getPair(){return VGPair;}
std::pair <int, int> count01();
bool isHonest(){return aff;}
bool checkHonesty(){return majHonest;}
std::string out() {return message;}

void msg(std::vector<Player> &PList, int var = 0);//variation
void check();
void outDet(); //output determination

void print(int i = 0)
{
    switch(i)
    {   
        case 1:
            std::cout << "ID: " << ID << " ";
            break;
        case 2:
            std::cout << "Aff: " << aff << " ";
            break;
        case 3:
            std::cout << "Msg: " << message << " ";
            break;
        case 4:
            std::cout << "pair: " << VGPair.first << " " << VGPair.second << " ";
            break;
        default:
            std::cout << "ID: " << ID << " ";
            std::cout << "Aff: " << aff << " ";
            std::cout << "Msg: " << message << " ";
            std::cout << "pair: " << VGPair.first << " " << VGPair.second << " ";
            break;
    }

    std::cout << "\n";
}
void clearMsg(){recieved.clear();}
void newRound(){halt = false;}
void corrupt()
{
    aff = false;
}

};

void Player::findV(std::vector<Player> &PList, int _t)
{
    n = PList.size();
    t = _t;
    ESIG0 = "0";
    ESIG1 = "1";
    ESIG2 = "2";
    // int min = 0;
    // std::string minHash /*= sha256(PList[0].credentials)*/, curHash;
    // for (int i = 1; i < n; i ++)
    // {
    //     //curHash = sha256(PList[i].credentials);
    //     if (curHash > minHash)
    //     {
    //         minHash = curHash;
    //         min = i;
    //     }
    // }
    // if(PList[min].prevBlock != NULL && sha256(prevBlock) == sha(cert.Block))
    // {
    //     v = 
    // }
    // else
    // {
    //     v = 2;
    // }
    v = "1";

    return;
}

std::pair <int, int> Player::count01()
{
    std::pair <int, int> cPair;
    cPair.first = 0;
    cPair.second = 0;
    for (int i = 0; i < recieved.size(); i ++)
    {
        if(i != ID)
        {
            if(recieved[i].compare(ESIG0))cPair.first ++;
            if(recieved[i].compare(ESIG1))cPair.second ++;
        }
    }
    return cPair;
}

void Player::msg(std::vector<Player> &PList, int var) //which round is it
{
    //std::cout << "InMsg\n";
    if (!halt)
    {
        //std::cout << "!halt\n";
        message = v;
        //message = ESIG(j, v);
        // std::pair <int, int> count;
        // if (var != 0)
        // {
        //     count = count01();
        // }
        // if (var == 1)
        // {
        //     if (count.first > (2 * t) + 1)
        //     {
        //         message = 0;
        //         halt = true;
        //     }
        //     else if (count.second > (2 * t) + 1)
        //     {
        //         message = 1;
        //     }
        //     else message = 0;
        // }
        // else if (var == 2)
        // {
        //     if (count.second > (2 * t) + 1)
        //     {
        //         message = 1;
        //         halt = true;
        //     }
        //     else if (count.first > (2 * t) + 1)
        //     {
        //         message = 0;
        //     }
        //     else message = 1;
        // }
        // else if (var == 3)
        // {
        //     majHonest = true;
        //     if(count.first == 0) message = 0;
        //     else if(count.second == 1) message = 1;
        //     else
        //     {
        //         message = rand() % 2;
        //         majHonest = false;
        //         y ++;
        //     }
        // }
    }
    //std::cout << "preSend\n";
    for(int i = 0; i < n; i ++)
    {
        //std::cout << i << "\n";
        //skip = rand() % numPlayers; //acts as a pseudo way to implement time since we're only running on one OS
        if(i != ID /*&& !(skip < t)*/) //typical amount recieved is n-t, this gives a t/n chance to skip
        {
            // if (aff) //honest
            // {
                PList[i].recieved.push_back(message);
            //}
            // else
            // {
            //     PList[i].recieved.push_back(rand() % 2);//simulating adversary
            // }
        }
    }
    return;
}

void Player::check()
{
    std::pair <int, int> count = count01(); 
    if(count.first > (2 * t) + 1)
    {
        v = "0";
    }
    else if(count.second > (2 * t) + 1)
    {
        v = "1";
    }
    else v = "2";
    //std::cout << "count0 " << count.first << "\ncount0 " << count.second << "\n";
    return;
}

void Player::outDet()
{
    std::pair <int, int> count = count01();
    int count2 = 0;
    for (int i = 0; i < n; i ++)
    {
        if(i != ID)
        {
            if(recieved[i].compare(ESIG2))count2++;
        }
    }
    if(count.first > (2 * t) + 1)
    {
        VGPair.first = 0;
        VGPair.second = 2;
    }
    else if(count.second > (2 * t) + 1)
    {
        VGPair.first = 1;
        VGPair.second = 2;
    }
    else if(count2 > (2 * t) + 1)
    {
        VGPair.first = 2;
        VGPair.second = 0;
    }
    else if(count.second > (2 * t) + 1)
    {
        VGPair.first = 1;
        VGPair.second = 2;
    }
    else if(count.first > t + 1)
    {
        VGPair.first = 0;
        VGPair.second = 1;
    }
    else if(count.second > t + 1)
    {
        VGPair.first = 1;
        VGPair.second = 1;
    }
    else
    {
        VGPair.first = 2;
        VGPair.second = 0;
    }
    //std::cout << "n " << n << "t " << t << "\n";
    return;
}
#endif