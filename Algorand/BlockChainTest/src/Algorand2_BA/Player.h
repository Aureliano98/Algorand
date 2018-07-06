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
int ID, n, t = 0, b;
bool aff, halt = false;
std::string message, v, ESIG0, ESIG1, ESIG2;
std::pair <std::string, int> VGPair;
std::vector<std::string> recieved;

public:
Player(int _ID, bool _aff = true):ID(_ID), aff(_aff)
{
    srand(time(NULL));
}
~Player(){}

void findV(std::vector<Player> &PList, int _t);
std::pair <std::string, int> getPair(){return VGPair;}
std::pair <int, int> count01();

bool isHonest(){return aff;}
std::string out() {return message;}

void msg(std::vector<Player> &PList, int var = 0);
void check();
void outDet();

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
    ESIG0 = "0"; //ESIG(j, 0)
    ESIG1 = "1"; //ESIG(j, 1)
    ESIG2 = "2"; //ESIG(j, 2)
    

    // int j = 0;
    // std::string minHash /*= sha256(PList[0].credentials)*/, curHash;
    // for (int i = 1; i < n; i ++)
    // {
    //     //curHash = sha256(PList[i].credentials);
    //     if (curHash > minHash)
    //     {
    //         minHash = curHash;
    //         j = i;
    //     }
    // }
    // if(PList[j].prevBlock != NULL && sha256(prevBlock) == sha(cert.Block))
    // {
    //     v = 
    // }
    // else
    // {
    //     v = "2"; //2 is the special character
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
            if(recieved[i].compare(ESIG0) == 0)cPair.first ++;
            if(recieved[i].compare(ESIG1) == 0)cPair.second ++;
        }
    }
    return cPair;
}

void Player::msg(std::vector<Player> &PList, int var)
{
<<<<<<< HEAD
    
    if (!halt)
    {
        //message = sign(j, v)
        message = v;
    }
    //std::cout << "preSend\n";
=======
    //std::cout << "send\n";
    // if (!halt)
    // {
    //     switch (var)
    //     {
    //         case 1:
    //             //doesn't change message
    //             break;
            
    //         default:
    //             //message = sign(j, v)
    //             message = v;
    //         break;
    //     }

    // }
    message = v;
    //std::cout << "b4 send\n";
>>>>>>> 92485937f9fa93f71da321fa0d5033345c08dc5f
    for(int i = 0; i < n; i ++)
    {
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
            if(recieved[i].compare(ESIG2) == 0)count2++;
        }
    }
    //std::cout << count.first << " " << count.second << " " << count2 << "\n";

    if(count.first > (2 * t) + 1)
    {
        VGPair.first = ESIG0;
        VGPair.second = 2;
    }
    else if(count.second > (2 * t) + 1)
    {
        VGPair.first = ESIG1;
        VGPair.second = 2;
    }
    else if(count2 > (2 * t) + 1)
    {
        VGPair.first = ESIG2;
        VGPair.second = 0;
    }
    else if(count.second > (2 * t) + 1)
    {
        VGPair.first = ESIG1;
        VGPair.second = 2;
    }
    else if(count.first > t + 1)
    {
        VGPair.first = ESIG0;
        VGPair.second = 1;
    }
    else if(count.second > t + 1)
    {
        VGPair.first = ESIG1;
        VGPair.second = 1;
    }
    else
    {
        VGPair.first = ESIG2;
        VGPair.second = 0;
    }
<<<<<<< HEAD
=======
    //std::cout << "end\n";
>>>>>>> 92485937f9fa93f71da321fa0d5033345c08dc5f
    b = 1;
    if (VGPair.second == 2)b = 0;
    //message = ESIG(i, b) + ESIG(i, v) + cred(i)
    return;
}
#endif