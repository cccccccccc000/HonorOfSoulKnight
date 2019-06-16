#ifndef __SPECIES_H__
#define __SPECIES_H__

#include"HeroBuff.h"

enum Species
{
	TOWERTIE1 = 0,
	TOWERTIE2,
	TOWERTIE3,
	ANCIENT,
	FOUNTAIN,
	MELEECREEP,
	RANGEDCREEP,
	SIEGECREEP,
	ARTHUR,
	HOUYI,
	DAJI,
};

//Attribute list
Attribute attribute_arthur = { MELEE,40.0,1622,3,0,0,164,14,0,7,1,0,120,0,40.0 };
Attribute attribute_houyi = { RANGED,40.0,1600,3,0,0,200,10,0,7,1,0,120,0,40.0 };
Attribute attribute_daji = { RANGED,40.0,1500,2,0,0,120,6,200,20,1,0,120,0,40.0 };
Attribute levelup_arthur = { MELEE,0.0,200,2,0,0,10,1,0,1,0,0,0,0,0.0 };
Attribute levelup_houyi = { RANGED,0.0,190,1,0,0,20,1,0,1,0,10,10,0,0.0 };
Attribute levelup_daji = { RANGED,0.0,120,1,0,0,9,1,20,1,0,0,0,0,0.0};

#endif
