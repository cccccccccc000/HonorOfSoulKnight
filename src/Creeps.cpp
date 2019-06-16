#include"Creeps.h"

Creeps* Creeps::create(Camp camp)
{
    Creeps* creeps=new Creeps();
    creeps->melee_creep_->create(camp,MELEECREEP);
    creeps->ranged_creep_->create(camp,RANGEDCREEP);
    creeps->siege_creep_->create(camp,SIEGECREEP);
    return creeps;
}