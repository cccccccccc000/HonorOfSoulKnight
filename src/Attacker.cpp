#include"Attacker.h"
#include "PlayingScene.h"
Attacker* Attacker::create(Camp camp,Species species)
{
    //set file name, bullet and inital position:

    std::string file_name;
    std::string bullet_file;
    Point pos;
    switch (species)
    {
        case TOWERTIE1:
        {
            bullet_file="bullet1.png";
            if(camp==RADIANT)
            {
                pos.x=560.0;
                pos.y=592.0;
            }
            else
            {
                pos.x=1040.0;
                pos.y=1008.0;
            }
            break;
        }
        case ANCIENT:
        {
            bullet_file="bullet1.png";
            if(camp==RADIANT)
            {
                pos.x=320.0;
                pos.y=352.0;
            }
            else
            {
                pos.x=1280.0;
                pos.y=1248.0;
            }
            break;
        }
        case FOUNTAIN:
        {
            bullet_file="bullet1.png";
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
            break;
        }
        case MELEECREEP:
        {
            file_name="meleecreep.png";
            if(camp==RADIANT)
            {
                pos.x=464.0;
                pos.y=496.0;
            }
            else
            {
                pos.x=1136.0;
                pos.y=1136.0;
            }
            break;
        }
        case RANGEDCREEP:
        {
            file_name="rangedcreep.png";
            bullet_file="bullet1.png";
            if(camp==RADIANT)
            {
                pos.x=432.0;
                pos.y=464.0;
            }
            else
            {
                pos.x=1168.0;
                pos.y=1168.0;
            }
            break;
        }
        case SIEGECREEP:
        {
            file_name="siegecreep.png";
            bullet_file="arrow1.png";
            if(camp==RADIANT)
            {
                pos.x=400.0;
                pos.y=432.0;
            }
            else
            {
                pos.x=1200.0;
                pos.y=1200.0;
            }
            break;
        }
        case ARTHUR:
        {
            file_name="saber.png";
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
            break;
        }
        case HOUYI:
        {
            file_name="archer.png";
            bullet_file="arrow1.png";
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
            break;
        }
        case DAJI:
        {
            file_name="caster.png";
            bullet_file="bullet1.png";
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
            break;
        }
    }
    
    //create a object:
	Attacker* attacker=new Attacker;
    if(!file_name.empty())
    {
        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(file_name);
        attacker->setTexture(texture);
    }
	if (attacker && attacker->InitWithSpecies(species))
    {
        attacker->autorelease();
        attacker->setAnchorPoint(Vec2(0.5, 0));
        attacker->setPosition(pos);
        attacker->SetCamp(camp);
        attacker->bullet_name_=bullet_file;
        //create hpbar:
        auto size = attacker->getContentSize();
        if(camp==RADIANT)
            attacker->hp_bar_ = Progress::create("small-enemy-progress-bg.png","small-player-progress-fill.png");
        else
			attacker->hp_bar_ = Progress::create("small-enemy-progress-bg.png","small-enemy-progress-fill.png");
		attacker->hp_bar_->autorelease();
		attacker->hp_bar_->setPosition( size.width/2, size.height + attacker->hp_bar_->getContentSize().height/2);
        attacker->addChild(attacker->hp_bar_);
        return attacker;
    }
    else
    {
        delete attacker;
        attacker = nullptr;
        return nullptr;
    }
}

bool Attacker::CanAttack()
{
	if (this->dead_ == true)
		return false;
	else
    	return true;
}

bool Attacker::RangedAttack()
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
                bullet->move(this->target_->getPosition());
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

bool Attacker::GetHit(int enemy_attack)
{
    this->state_.hp-=static_cast<int>(enemy_attack*(1-this->attribute_.def));
    if(this->state_.hp<=0)
    {
		CCScene* sence = CCDirector::sharedDirector()->getRunningScene();
		int minute = sence->getMinute();
        this->Die(minute);
        return true;
    }
    return false;
}

void Attacker::Die(int minute)
{
    this->dead_ = true;
	this->state_.hp = 0;
	this->state_.mp = 0;
    this->setVisible(false);
    this->hp_bar_->setVisible(false);
    if(this->species_==ANCIENT)
    {
        if(this->camp_==RADIANT)
            PlayingScene::lose();
        else
            PlayingScene::win();
    }
}

bool Attacker::CanBeTarget()
{
	if (this->dead_)
		return false;
	else
        if(this->species_==FOUNTAIN)
            return false;
        else
		    return true;
}