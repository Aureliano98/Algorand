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
int ID, v, skip, message, n, t = 0, y; //
bool aff, halt = false, majHonest = true; //affiliation
std::pair <int,int> VGPair;//v can be 0, 1 or a special character that we will represent with 2, G is 0,1, or 2
std::vector<int> recieved;

public:
Player(int num, int v1, int _n, int _t, bool honest = true):ID(num), v(v1), aff(honest), n(_n), t(_t)
{
    srand(time(NULL));
}
~Player(){}
void setV(int _v){v = _v;}
std::pair <int, int> getPair(){return VGPair;}
std::pair <int, int> count01();
bool checkHonesty(){return majHonest;}

void msg(std::vector<Player> &PList, char value = 'v');
void check();
void outDet(); //output determination

void printVG(){std::cout << VGPair.first << " " << VGPair.second << " " << aff <<"\n";}
void printMsg(){std::cout << message <<"\n";}
void clearMsg(){recieved.clear();}
void newRound(){halt = false;}
void corrupt(int _v, std::pair <int, int> _pair)
{
    aff = false;
    v = _v;
    VGPair = _pair;
}
};

std::pair <int, int> Player::count01()
{
    std::pair <int, int> cPair;
    cPair.first = 0;
    cPair.second = 0;
    for (int i = 0; i < recieved.size(); i ++)
    {
        if(i != ID)
        {
            if(recieved[i] == 0)cPair.first ++;
            if(recieved[i] == 1)cPair.second ++;
        }
    }
    return cPair;
}
void Player::msg(std::vector<Player> &PList, char value) //which round is it
{
    if (!halt)
    {
        message = v;
        std::pair <int, int> count;
        if (value != 'v')
        {
            count = count01();
        }
        if (value == '1')
        {
            if (count.first > (2 * t) + 1)
            {
                message = 0;
                halt = true;
            }
            else if (count.second > (2 * t) + 1)
            {
                message = 1;
            }
            else message = 0;
        }
        else if (value == '2')
        {
            if (count.second > (2 * t) + 1)
            {
                message = 1;
                halt = true;
            }
            else if (count.first > (2 * t) + 1)
            {
                message = 0;
            }
            else message = 1;
        }
        else if (value == '3')
        {
            majHonest = true;
            if(count.first == 0) message = 0;
            else if(count.second == 1) message = 1;
            else
            {
                message = rand() % 2;
                majHonest = false;
                y ++;
            }
        }
    }
    //std::cout<<"PlayerMsg " << PList.size() << " " << v << "\n";
    for(int i = 0; i < PList.size(); i ++)
    {
        //std::cout<<i;
        //skip = rand() % numPlayers; //acts as a pseudo way to implement time since we're only running on one OS
        if(i != ID /*&& !(skip < t)*/) //typical amount recieved is n-t, this gives a t/n chance to skip
        {
            //PList[i].recieved.push_back(v);
            if (aff) //honest
            {
                PList[i].recieved.push_back(message);
            }
            else
            {
                PList[i].recieved.push_back(rand() % 2);//simulating adversary
            }
        }
    }
    //std::cout<<"\n";
    return;
}

void Player::check()
{
    std::pair <int, int> count = count01(); 
    //int count0 = 0, count1 = 0;
    //std::cout<<"inCheck\n";
    // for (int i = 0; i < recieved.size(); i ++)
    // {
    //     //std::cout << i;
    //     if(i != ID)
    //     {
    //         if(recieved[i] == 0)count0++;
    //         if(recieved[i] == 1)count1++;
    //     }
    // }
    // std::cout<<"Check count0 " << count0 << "\n";
    // std::cout<<"Check count1 " << count1 << "\n";
    if(count.first > (2 * t) + 1)
    {
        //std::cout << "count0>\n";
        v = 0;
    }
    else if(count.second > (2 * t) + 1)
    {
        //std::cout << "count1>\n";
        v = 1;
    }
    else v = 2;
    return;
}
void Player::outDet()
{
    std::pair <int, int> count = count01(); 
    //std::cout<<"inOutDet\n";
    // int count0 = 0, count1 = 0;
    // for (int i = 0; i < recieved.size(); i ++)
    // {
    //     if(i != ID)
    //     {
    //         if(recieved[i] == 0)count0++;
    //         if(recieved[i] == 1)count1++;
    //     }
    // }
    if(count.first > (2 * t) + 1)
    {
        //std::cout << "count0>";
        VGPair.first = 0;
        VGPair.second = 2;
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
    return;
}
#endif