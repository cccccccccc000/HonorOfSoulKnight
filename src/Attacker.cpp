#include"Attacker.h"

Camp Attacker::GetCamp()
{
	return this->camp_;
}

bool Attacker::CanAttack()
{
	return true;
}

bool Attacker::CanBeTarget()
{
	if (this->dead_)
		return false;
	else
		return true;
}