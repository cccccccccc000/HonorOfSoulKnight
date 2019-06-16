#ifndef __CREEP_H__
#define __CREEP_H__

#include"Creature.h"

class Creeps
{
public:
	static Creeps* create(Camp camp);

	// members:
	Creature* melee_creep_;
	Creature* ranged_creep_;
	Creature* siege_creep_;
};
#endif