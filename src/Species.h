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
Attribute attribute_arthur = { MELEE,1622,3,0,0,164,14,0,7,1,0,120,0,40 };
Attribute attribute_houyi = { RANGED,1622,3,0,0,164,14,0,7,1,0,120,0,40 };
Attribute attribute_daji = { RANGED,1622,3,0,0,164,14,0,7,1,0,120,0,40 };

#endif
