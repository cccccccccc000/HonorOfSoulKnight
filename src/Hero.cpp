#include"Hero.h"

bool Hero::InitWithSpecies(Species species)
{
	switch (species)
	{
	case ARTHUR:
	{
		this->attribute_ = attribute_arthur;
		//skill
		this->species_ = ARTHUR;
		break;
	}
	case HOUYI:
	{
		this->attribute_ = attribute_houyi;
		//skill
		this->species_ = HOUYI;
		break;
	}
	case DAJI:
	{
		this->attribute_ = attribute_daji;
		//skill
		this->species_ = DAJI;
		break;
	}
	default:
		return false;
	}
	this->state_.hp = this->attribute_.mhp;
	this->state_.mp = this->attribute_.mmp;
	this->debuff_.silent = 0;
	this->debuff_.stunned = 0;
	this->reborn_time_ = 0;
	this->money_ = 0;
	this->exp_ = 0;
	this->level_ = 1;
	this->dead_ = false;
	this->target_ = nullptr;
	this->experience = 300;
	this->bounty = 200;
	return true;
}

void Hero::ReceiveBuff(HeroBuff &buffA)
{
	if (buffA.GetDuration() > 0)
	{
		this->buffs_.insert(this->buffs_.end(), buffA);
		this->attribute_ = this->attribute_ + buffA.GetAttributeChange();
		this->state_ = this->state_ + buffA.GetStateChange();
		this->debuff_ = this->debuff_ + buffA.GetDebuffChange();
	}
}

void Hero::DecreaseBuffDuration(float delta)
{
	for (vector<HeroBuff>::iterator iter = this->buffs_.begin(); iter != this->buffs_.end(); ++iter)
	{
		iter->DecreaseDuration(1);
		if (iter->BuffEnd())
		{
			this->RemoveBuff(iter);
		}
	}
	if (this->dead_)
	{
		if (this->reborn_time_ = 0)
		{
			this->Reborn();
		}
		else if (this->reborn_time_ > 0)
		{
			--this->reborn_time_;
		}
	}
}

void Hero::RemoveBuff(vector<HeroBuff>::iterator iter)
{
	this->attribute_ = this->attribute_ - iter.GetAttributeChange();
	this->state_ = this->state_ - iter.GetStateChange();
	this->debuff_ = this->debuff_ - iter.GetDebuffChange();
	this->buffs_.erase(iter);
}

void Hero::PurchaseItem(Item& itemA,int price)
{
	if(this->money_>=price)
	{
		this->money_-=price;
		this->items_.insert(this->items_.end(), itemA);
		this->attribute_ = this->attribute_ + itemA;
	}
}

void Hero::SellItem(vector<Item>::iterator iter)
{
	//sorry you can't
}

void Hero::Die(int minute)
{
	this->dead_ = true;
	for (vector<HeroBuff>::iterator iter = this->buffs_.begin(); iter != this->buffs_.end(); ++iter)
	{
		this->RemoveBuff(iter);
	}
	this->state_.hp = 0;
	this->state_.mp = 0;
	this->reborn_time_ = this->level_*3+2;
	if (minute > 20 && minute < 35)
		this->reborn_time_ += minute - 20;
	if (this->reborn_time_ > 60)
		this->reborn_time_ = 60;
	this->money_ -= 0;
	this->target_ = nullptr;
}

void Hero::ReceiveExp(int exp)
{
	this->exp_+=exp;
	while(this->exp>=this->level_*200)
		this->HeroLevelUp();
}

void Hero::HeroLevelUp()
{
	this->level_++;
	switch (this->species_)
	{
		case ARTHUR:
		{
			this->attribute_=this->attribute_+levelup_arthur;
			break;
		}
		case HOUYI:
		{
			this->attribute_=this->attribute_+levelup_houyi;
			break;
		}
		case DAJI:
		{
			this->attribute_=this->attribute_+levelup_daji;
			break;
		}
	}
}

bool Hero::CanAttack()
{
	if (this->dead_ == true)
		return false;
	else
	{
		if (this->debuff_.stunned > 0)
			return false;
		else
			return true;
	}
}

bool Hero::Attack()
{
	if (this->CanAttack())
	{
		this->MoveTowards(this->target_->getPosition());
		if (this->target_->CanBeTarget())
		{
			if (this->camp_ != this->target_->GetCamp())
			{
				if(this->target_->GetHit(this->attribute_.atk))
				{
					this->ReceiveMoney(this->target_.bounty_);
					this->ReceiveExp(this->target_.experience_);
				}
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

bool Hero::RangedAttack()
{
	if (this->CanAttack())
	{
		if (this->target_->CanBeTarget())
		{
			if (this->camp_ != this->target_->GetCamp())
			{
                Bullet* bullet=Bullet::createWithType(this->bullet_name_);
                Point bullet_pos=this->getPosition();
                bullet->setPosition(bullet_pos);
                bullet->move(this->target_.getPosition);
				if(this->target_->GetHit(this->attribute_.atk))
				{
					this->ReceiveMoney(this->target_.bounty_);
					this->ReceiveExp(this->target_.experience_);
				}
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

bool Hero::CanBeTarget()
{
	if (this->dead_)
		return false;
	else
	{
		/*if (!this->state_.visible)
			return false;
		else*/
			return true;
	}
}

bool Hero::Reborn()
{
	this->dead_=false;
	this->state_.hp=this->attribute_.mhp;
	this->state_.mp=this->attribute_.mmp;
	Point pos;
	if(camp==RADIANT)
    {
        pos.x=112.0;
        pos.y=144.0;
    }
	else
    {
        pos.x=1488.0;
        pos.y=1456.0;
    }
	this->setPosition(pos);
	return true;
}