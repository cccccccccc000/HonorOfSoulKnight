
#ifndef __HERO_H__
#define __HERO_H__

#include<vector>
#include<iterator>

#include"Creeps.h"
#include"Skill.h"

class Hero :public Creature
{
public:
	bool InitWithSpecies(Species species)override;

	void ReceiveBuff(HeroBuff &buffA);

	void DecreaseBuffDuration(float delta);

	void RemoveBuff(std::vector<HeroBuff>::iterator iter);

	void PurchaseItem(Attribute& itemA,int price);

	void SellItem(std::vector<Attribute>::iterator iter);

	void Die(int minute)override;

	void ReceiveMoney(int money) {this->money_+=money;}

	void ReceiveExp(int exp);

	int GetLevel() {return this->level_;}

	void HeroLevelUp();

	bool CanAttack()override;

	bool Attack()override;

	bool RangedAttack()override;

	bool CanBeTarget()override;
	
	bool Reborn();

private:
	HeroDebuff debuff_;

	std::vector<HeroBuff> buffs_;

	std::vector<Skill> skills_;

	std::vector<Item> items_;

	int reborn_time_;

	int money_;

	int exp_;

	int level_;
};

#endif
