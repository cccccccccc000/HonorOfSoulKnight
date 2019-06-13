
#ifndef __ATTACKER_H__
#define __ATTACKER_H__

#include "cocos2d.h"
#include "Species.h"

enum Camp
{
	RADIANT = 0,
	DIRE = 1,
};

class Attacker :public cocos2d::Sprite
{
public:
	virtual bool InitWithSpecies(Species species);

	Camp GetCamp();

	virtual bool CanAttack();

	virtual bool Attack();

	virtual bool CanBeTarget();

	bool stop();


protected:
	Camp camp_;

	Species species_;

	bool dead_;

	Attacker* target_;

	int experience;
		//exp which is received by killer
	int bounty;
		//gold which is received by killer
};

#endif