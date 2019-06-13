#include"HeroBuff.h"

int HeroBuff::GetDuration()
{
	return this->duration_;
}

void HeroBuff::DecreaseDuration(int time)
{
	this->duration_ -= time;
}

bool HeroBuff::BuffEnd()
{
	if (this->duration_ <= 0)
		return true;
	else
		return false;
}

HeroAttribute HeroBuff::GetAttributeChange()
{
	return this->attribute_change_;
}

HeroState HeroBuff::GetStateChange()
{
	return this->state_change_;
}

HeroDebuff HeroBuff::GetDebuffChange()
{
	return this->debuff_change_;
}