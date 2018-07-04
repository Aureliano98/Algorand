#include "sortition.h"

int Sortition::interval = 10000;

Sortition::Sortition() {
	N = Cloud::Instance().PK.size();
	tH = 0.69 * Cloud::Instance().PK.size();
	k = 1;
	p1 = 38.0 / N;
	p = 1000.0 / N; //Not defined yet
}

bool Sortition::verifyPotential(Software* sw, int round, int step)
{
	std::string credential = SIG(std::to_string(round) + std::to_string(1) +
		sw->m_blockchain.GetTail()->seed);
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

void Sortition::generateMasterKey(Software* sw)
{
	sw->m_userKey.GenerateKey(sw->m_userKey.PMK, sw->m_userKey.SMK);

	//a pice of informing information
	std::string publicInfo = SIG(sw->m_userKey.PMK + std::to_string(sw->m_blockchain.Length() + 1) +
		std::to_string(sw->m_blockchain.Length() + 10001));

	//use this payment to let other users know the change of PMK
	//sw->CreatPay(*sw, 0, publicInfo, "");

	updateEphemeralKey(sw);

}

void Sortition::updateEphemeralKey(Software* sw)
{
	//generate pk-r', s
	for (int round = 0; round < 10000; ++round)
	{
		for (int step = 0; step < 12; ++step)
		{
			sw->m_userKey.pk[round][step] = sw->m_userKey.pub_key +
				std::to_string(sw->m_blockchain.Length() + round) +
				std::to_string(step);
		}
	}

	//using SMK generate sk-r', s for every pk-r', s
	for (int round = 0; round < 10000; ++round)
	{
		for (int step = 0; step < 12; ++step)
		{
			//GenerateKey(sw->m_userKey[round][step], sw->m_userKey.SMK);
		}
	}

	//destroy SMK
	sw->m_userKey.SMK.assign("");

}