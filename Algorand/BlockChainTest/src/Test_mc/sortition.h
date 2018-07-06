#ifndef SORTITION_H
#define SORTITION_H
#include "Cloud.h"
#include "../Signiture_qdl/SignatureBasedOnRSA.h"
#include "../sha256_ckw/sha256.h"
#include "../BA_Protocol/Player.h"
using namespace Signature;
class Sortition{
public:
	Sortition()
	{
		N = Cloud::Instance().activeN;
		tH = 0.69 * N;
		k = 1;
		p1 = 38.0 / N;
		p = 1000.0 / N;
	}

	//Verify whether a user is a potential leader in step 1
	//when put in the last user, let last = true
	int verifyLeader(Player* user, int round, bool last = false)
	{
		static double MIN = 1.0;
		static int Id = 0;
		std::string hashCr = hashToBinaryString(sha256(getCredential(user, round, 1)));
		double number = 0.0;
		for (int i = 255; i >= 0; i--)
		{
			number = number * 0.5 + hashCr[i] - '0';
		}
		number *= 0.5;

		if (number < MIN)
		{
			MIN = number;
			Id = user->GetId();
		}

		if (last)
		{
			return Id;
		}
	}

	//Verify whether a user is a verifier in step > 1 
	void verifyVerifier(Player* user, std::vector <Player*>& list, int round, int step)
	{
		std::string hashCr = hashToBinaryString(sha256(getCredential(user, round, 1)));
		double number = 0.0;
		for (int i = 255; i >= 0; i--)
		{
			number = number * 0.5 + hashCr[i] - '0';
		}
		number *= 0.5;

		if (number < p)
		{
			list.push_back(user);
		}
	}

	std::string getCredential(Player* user, int round, int step)
	{
		std::string info = std::to_string(round) + std::to_string(step) +
			user->m_software.m_blockchain.GetTail()->seed;
		std::string hashInfo = hashToBinaryString(sha256(info));
    
    user->m_software.m_userKey.GenerateMasterKey();
    
		std::string credential = EncryptWith(hashInfo, user->m_software.m_userKey.MK[UserKey::N], user->m_software.m_userKey.MK[UserKey::E]).IntoBinaryS();
    return credential;
	}

private:

	//All the active user in round r
	int N;

	//Lower-bound of honest users in step >1 of round r
	int tH;

	//Look-back parameter
	int k;

	//Possibility of a user being a potential leader in step 1
	double p1;

	//Possibility of a user being a verifier in step >1
	double p;

	//PMK and SMK updates per interval rounds
	static int interval;
};

int Sortition::interval = 10000;

#endif // SORTITION_H