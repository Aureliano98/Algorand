#ifndef SORTITION_H
#define SORTITION_H
#include "Software.h"
#include "../sha256_ckw/sha256.h"
#include "UserKey.h"
#include "DealMaker.h"
#include "Signiture.h"
#include "Cloud.h"

class Sortition{
public:
	Sortition();

	//Verify whether a user is a potential leader in step 1 / verifier in step > 1 
	bool verifyPotential(Software* sw, int round, int step = 1);

	void generateMasterKey(Software* sw);

private:

	void updateEphemeralKey(Software* sw);

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

#endif // SORTITION_H