#include"Creature.h"
#include <math.h>

void Creature::MoveTowards(Point pos)
{
    Point destination=maplayer->tileToWin(pos);
    float x=fabs(destination.x-this->getPosition().x);
    float y=fabs(destination.y-this->getPosition().y);
    float distance=hypot(x,y);
    float time=distance/this->attribute_.spd;
    this->runAction(MoveTo::create(time, destination));
}

bool Creature::Attack()
{
	if (this->CanAttack())
	{
		this->MoveTowards(this->target_->getPosition());
		if (this->target_->CanBeTarget())
		{
			if (this->camp_ != this->target_->GetCamp())
			{
				this->target_->GetHit(this->attribute_.atk);
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

void Creature::useAI()
{
	float distance = this->attribute_.spd * 0.5;
	float dis = distance / 1.4;
	if (this->camp_ == 0) {
		auto moveBy = MoveBy::create(0.5,Vec2(dis,dis));
		this->runAction(moveBy);
	}
	else if (this -> camp_ == 1) {
		auto moveBy = MoveBy::create(0.5, Vec2(dis, dis));
		this->runAction(moveBy);
	}
}