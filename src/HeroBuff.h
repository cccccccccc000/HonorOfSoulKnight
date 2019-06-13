#ifndef __HEROBUFF_H__
#define __HEROBUFF_H__

enum Range
{
	MELEE = 0,
	RANGED = 1,
};
struct Attribute
{
	Range aran;
		//melee or ranged
	int mhp;
		//max health point
	int hpr;
		//hp recovery
	int mmp;
		//max mana point
	int mpr;
		//mp recovery
	int atk;
		//attack
	int def;
		//defense
	int mat;
		//magic attack
	int mdf;
		//magic defense
	int bat;
		//base attack time
	int crt;
		//critical rate(%)
	int cdg;
		//critical damage(%)
	int evd;
		//evasion rate(%)
	int spd;
		//movement speed
	Attribute operator+(const Attribute& change)noexcept
	{
		Attribute A;
		A.atk = this->atk + change.atk;
		A.bat = this->bat + change.bat;
		A.cdg = this->cdg + change.cdg;
		A.crt = this->crt + change.crt;
		A.def = this->def + change.def;
		A.evd = this->evd + change.evd;
		A.hpr = this->hpr + change.hpr;
		A.mat = this->mat + change.mat;
		A.mdf = this->mdf + change.mdf;
		A.mhp = this->mhp + change.mhp;
		A.mmp = this->mmp + change.mmp;
		A.mpr = this->mpr + change.mpr;
		A.spd = this->spd + change.spd;
		return A;
	}
	Attribute operator-(const Attribute& change)noexcept
	{
		Attribute A;
		A.atk = this->atk - change.atk;
		A.bat = this->bat - change.bat;
		A.cdg = this->cdg - change.cdg;
		A.crt = this->crt - change.crt;
		A.def = this->def - change.def;
		A.evd = this->evd - change.evd;
		A.hpr = this->hpr - change.hpr;
		A.mat = this->mat - change.mat;
		A.mdf = this->mdf - change.mdf;
		A.mhp = this->mhp - change.mhp;
		A.mmp = this->mmp - change.mmp;
		A.mpr = this->mpr - change.mpr;
		A.spd = this->spd - change.spd;
		return A;
	}
	Attribute operator=(const Attribute& change)noexcept
	{
		Attribute A;
		A.atk = change.atk;
		A.bat = change.bat;
		A.cdg = change.cdg;
		A.crt = change.crt;
		A.def = change.def;
		A.evd = change.evd;
		A.hpr = change.hpr;
		A.mat = change.mat;
		A.mdf = change.mdf;
		A.mhp = change.mhp;
		A.mmp = change.mmp;
		A.mpr = change.mpr;
		A.spd = change.spd;
		return A;
	}
};
struct HeroState
{
	int hp;
		//health point
	int mp;
		//mana point
	HeroState operator+(const HeroState& change)noexcept
	{
		HeroState A;
		A.hp = this->hp + change.hp;
		A.mp = this->mp + change.mp;
		return A;
	}
	HeroState operator-(const HeroState& change)noexcept
	{
		HeroState A;
		A.hp = this->hp - change.hp;
		A.mp = this->mp - change.mp;
		return A;
	}
};
struct HeroDebuff
{
	int silent;
		//number of silent debuffs
	int stunned;
		//number of stunned debuffs
	HeroDebuff operator+(const HeroDebuff& change)
	{
		HeroDebuff A;
		A.silent = this->silent + change.silent;
		A.stunned = this->stunned + change.stunned;
		return A;
	}
	HeroDebuff operator-(const HeroDebuff& change)
	{
		HeroDebuff A;
		A.silent = this->silent - change.silent;
		A.stunned = this->stunned - change.stunned;
		return A;
	}
};

class HeroBuff
{
public:
	int GetDuration();
		//return duration of the buff
	void DecreaseDuration(int time);
		//decrease duration of the buff by "time"
	bool BuffEnd();

	Attribute GetAttributeChange();

	HeroState GetStateChange();

	HeroDebuff GetDebuffChange();

private:
	int duration_;

	Attribute attribute_change_;

	HeroState state_change_;

	HeroDebuff debuff_change_;
};

#endif // __HEROBUFF_H__
