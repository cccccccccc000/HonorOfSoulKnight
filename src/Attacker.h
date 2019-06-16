
#ifndef __ATTACKER_H__
#define __ATTACKER_H__

#include "cocos2d.h"
#include "Species.h"
#include "Progress.h"
#include "Bullet.h"

enum Camp
{
	RADIANT = 0,
	DIRE = 1,
};

class Attacker :public cocos2d::Sprite
{
public:
	virtual bool InitWithSpecies(Species species);

	static Attacker* create(Camp camp,Species species);

	inline void SetCamp(Camp camp) {this->camp_=camp;}

	Camp GetCamp() {return this->camp_;}

	virtual bool CanAttack();

	virtual bool Attack();

	virtual bool RangedAttack();

	bool GetHit(int enemy_attack);
		//physical damaged
	virtual void Die(int minute);

	virtual bool CanBeTarget();

	void ergodicAllNode(CCNode *rootNode);

	inline void SetTarget(Attacker* target) {this->target_=target;}

	bool stop();

	inline int GetExperience() {return experience_;}

	inline int GetBounty() {return bounty_;}

protected:
	Camp camp_;

	Species species_;

	Attribute attribute_;

	HeroState state_;

	bool dead_;

	Attacker* target_;

	std::string bullet_name_;

	int experience_;
		//exp which is received by killer
	int bounty_;
		//gold which is received by killer
	Progress* hp_bar_;
};

#endif