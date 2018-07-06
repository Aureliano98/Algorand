#include "Cloud.h"
#include "Signiture.h"
#include "sortition.h"
#include "DealMaker.h"

#include <fstream>

int Sortition::interval = 10000;

Sortition::Sortition()
{
	N = Cloud::Instance().activeN;
	tH = 0.69 * N;
	k = 1;
	p1 = 38.0 / N;
	p = 1000.0 / N; //Not defined yet
}

bool Sortition::verifyPotential(UserKey* uk,BlockChain* bc, int round, int step)
{
  std::string info = std::to_string(round) + std::to_string(step) + bc->GetTail()->seed;
  std::string hashInfo = hashToBinaryString(sha256(info));
	std::string credential = uk->Sign(hashInfo).IntoBinaryS();
	std::string hashCr = hashToBinaryString(sha256(credential));

	double number = 0.0;
	for (int i = 255; i >= 0; i--)
	{
		number = number * 0.5 + hashCr[i] - '0';
	}
	number *= 0.5;

	if (step == 1 && number < p1)
	{
		return true;
	}

	if (step > 1 && number < p)
	{
		return true;
	}

	return false;
}

/*
void Sortition::generateMasterKey(UserKey* uk, BlockChain* bc, int userNumber)
{
	uk->GenerateMasterKey();

	//a piece of informing information
	std::string publicInfo = uk->Sign(std::to_string(userNumber) + std::to_string(bc->Length() + 1) +
		std::to_string(bc->Length() + 10001)).IntoBinaryS();

	//use this payment to let other users know the change of PMK
	//use MakeADeal(uk->pub_key, uk->pub_key, 0, publicInfo, "") in DealMaker;
  
	//updateEphemeralKey(uk, bc, userNumber);
}

void Sortition::updateEphemeralKey(UserKey* uk, BlockChain* bc, int userNumber)
{
	std::ofstream pkout("../key/pk/" + std::to_string(userNumber), std::ios::binary);
	std::ofstream skout("../key/sk/" + std::to_string(userNumber), std::ios::binary);

	//generate pk-r', s
	for (int round = 0; round < 10000; ++round)
	{
		for (int step = 0; step < 12; ++step)
		{
			 pkout << uk->pub_key + std::to_string(bc->Length() + round) +
						std::to_string(step);
		}
	}

	//using SMK generate sk-r', s for every pk-r', s
	for (int round = 0; round < 10000; ++round)
	{
		for (int step = 0; step < 12; ++step)
		{
			//GenerateKey(sw->m_userKey[round][step], sw->m_userKey.SMK);
			//skout << sk;
		}
	}

	//destroy SMK
	uk->SMK.assign("");

	pkout.close();
	skout.close();

}
*/