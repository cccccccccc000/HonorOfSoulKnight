
#include "PlayingScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* PlayingScene::createScene()
{
	auto scene = PlayingScene::create();

	auto maplayer = MapLayer::create();
	scene->addChild(maplayer, -1);

	scene->hero_enemy_ = Hero::create(DIRE, ARTHUR);
	scene->addChild(scene->hero_enemy_);

	scene->r_tower_ = Attacker::create(RADIANT, TOWERTIE1);
	scene->addChild(scene->r_tower_);
	scene->r_ancient_ = Attacker::create(RADIANT, ANCIENT);
	scene->addChild(scene->r_ancient_);
	scene->r_fountain_ = Attacker::create(RADIANT, FOUNTAIN);
	scene->addChild(scene->r_fountain_);

	scene->d_tower_ = Attacker::create(DIRE, TOWERTIE1);
	scene->addChild(scene->r_tower_);
	scene->d_ancient_ = Attacker::create(DIRE, ANCIENT);
	scene->addChild(scene->r_ancient_);
	scene->d_fountain_ = Attacker::create(DIRE, FOUNTAIN);
	scene->addChild(scene->r_fountain_);

	auto equiplayer = EquipLayer::create();
	scene->addChild(equiplayer, 1);

	return scene;
}

static Scene* PlayingScene::createSceneWithHero(Species species)
{
	auto scene = PlayingScene::createScene();
	scene->hero_player_ = Hero::create(RADIANT, species);
	scene->addChild(scene->hero_player_);
	return scene;
}

bool PlayingScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	this->schedule(schedule_selector(this->IncreaseTime), 1.0f);
	//current time timer on
	this->schedule(schedule_selector(this->BuffTimerOn), 1.0f);

	this->schedule(schedule_selector(this->BulletTimerOn), 0.5f);

	this->schedule(schedule_selector(this->SelectTarget), 0.5f);

	this->schedule(schedule_selector(this->AiAttack), 1.0f);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// create the backgroud after win or lose
	{
		back_ground = Sprite::create("equipbackground.jpg");
		back_ground->setAnchorPoint(Point(0.5, 0.5));
		back_ground->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, visibleSize.height *0.5 + origin.y));
		back_ground->setVisible(false);
		addChild(back_ground, 2);

		auto black_system_label = [](std::string str) {
			auto label = Label::createWithSystemFont(str, "Arial", 50);
			label->setColor(Color3B(0, 0, 0));
			return label;
		};

		label_win = black_system_label("You Win");
		label_win->setAnchorPoint(Point(0.5, 0.5));
		label_win->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, visibleSize.height *0.5 + origin.y));
		label_win->setVisible(false);
		addChild(label_win, 3);

		label_lose = black_system_label("You Lose");
		label_lose->setAnchorPoint(Point(0.5, 0.5));
		label_lose->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, visibleSize.height *0.5 + origin.y));
		label_lose->setVisible(false);
		addChild(label_lose, 3);
	}

	return true;
}

void PlayingScene::IncreaseTime()
{
	if (!this->timer_pause_)
	{
		this->current_time_second_++;
		if (this->current_time_second_ % 30 == 0)
		{
			Creeps* r_creeps = Creeps::create(RADIANT);
			this->addChild(r_creeps);
			Creeps* d_creeps = Creeps::create(DIRE);
			this->addChild(d_creeps);
			this->r_creeps_.insert(this->creeps_.end(), r_creeps);
			this->d_creeps_.insert(this->creeps_.end(), d_creeps);
		}
		this->hero_player_->ReceiveMoney(5);
	}
}

void PlayingScene::BuffTimerOn()
{
	if (!this->timer_pause_)
	{
		this->hero_player_->DecreaseBuffDuration(1.0f);
		this->hero_enemy_->DecreaseBuffDuration(1.0f);
	}
}

void PlayingScene::BulletTimerOn()
{
	if (!this->timer_pause_)
	{
		for (std::map<Bullet*, MoveTo*>::iterator iter = this->bullet_seq.begin(); iter != this->bullet_seq.end(); ++iter)
		{
			if (iter->second->IsDone())
			{
				iter->first->Die();
				this->bullet_seq.erase(iter);
			}
		}
	}
}

void PlayingScene::SelectTargetForR(Attacker* theone)
{
	float x, y;
	Point onepos = theone->getPosition();

	Point pos = this->hero_enemy_->getPosition();
	if (this->hero_enemy_->CanBeTarget)
	{
		x = fabs(onepos.x - pos.x);
		y = fabs(onepos.x - pos.y);
		if (theone->GetRange() >= hypotf(x, y))
		{
			theone->SetTarget(this->hero_enemy_);
			return;
		}
	}
	pos = this->d_ancient_->getPosition();
	if (this->d_ancient_->CanBeTarget)
	{
		x = fabs(onepos.x - pos.x);
		y = fabs(onepos.x - pos.y);
		if (theone->GetRange() >= hypotf(x, y))
		{
			theone->SetTarget(this->d_ancient_);
			return;
		}
	}
	pos = this->d_tower_->getPosition();
	if (this->d_tower_->CanBeTarget)
	{
		x = fabs(onepos.x - pos.x);
		y = fabs(onepos.x - pos.y);
		if (theone->GetRange() >= hypotf(x, y))
		{
			theone->SetTarget(this->d_tower_);
			return;
		}
	}
	for (std::vector<Creeps*>::iterator iter = this->d_creeps_.begin(); iter != this->d_creeps_.end(); ++iter)
	{
		pos = iter->melee_creep_->getPosition();
		if (iter->melee_creep_->CanBeTarget)
		{
			x = fabs(onepos.x - pos.x);
			y = fabs(onepos.x - pos.y);
			if (theone->GetRange() >= hypotf(x, y))
			{
				theone->SetTarget(iter->melee_creep_);
				return;
			}
		}
		pos = iter->ranged_creep_->getPosition();
		if (iter->ranged_creep_->CanBeTarget)
		{
			x = fabs(onepos.x - pos.x);
			y = fabs(onepos.x - pos.y);
			if (theone->GetRange() >= hypotf(x, y))
			{
				theone->SetTarget(iter->ranged_creep_);
				return;
			}
		}
		pos = iter->siege_creep_->getPosition();
		if (iter->siege_creep_->CanBeTarget)
		{
			x = fabs(onepos.x - pos.x);
			y = fabs(onepos.x - pos.y);
			if (theone->GetRange() >= hypotf(x, y))
			{
				theone->SetTarget(iter->siege_creep_);
				return;
			}
		}
	}
	theone->SetTarget(nullptr);
}

void PlayingScene::SelectTargetForD(Attacker* theone)
{
	float x, y;
	Point onepos = theone->getPosition();

	Point pos = this->hero_player_->getPosition();
	if (this->hero_player_->CanBeTarget)
	{
		x = fabs(onepos.x - pos.x);
		y = fabs(onepos.x - pos.y);
		if (theone->GetRange() >= hypotf(x, y))
		{
			theone->SetTarget(this->hero_player_);
			return;
		}
	}
	pos = this->r_ancient_->getPosition();
	if (this->r_ancient_->CanBeTarget)
	{
		x = fabs(onepos.x - pos.x);
		y = fabs(onepos.x - pos.y);
		if (theone->GetRange() >= hypotf(x, y))
		{
			theone->SetTarget(this->r_ancient_);
			return;
		}
	}
	pos = this->r_tower_->getPosition();
	if (this->r_tower_->CanBeTarget)
	{
		x = fabs(onepos.x - pos.x);
		y = fabs(onepos.x - pos.y);
		if (theone->GetRange() >= hypotf(x, y))
		{
			theone->SetTarget(this->r_tower_);
			return;
		}
	}
	for (std::vector<Creeps*>::iterator iter = this->r_creeps_.begin(); iter != this->r_creeps_.end(); ++iter)
	{
		pos = iter->melee_creep_->getPosition();
		if (iter->melee_creep_->CanBeTarget)
		{
			x = fabs(onepos.x - pos.x);
			y = fabs(onepos.x - pos.y);
			if (theone->GetRange() >= hypotf(x, y))
			{
				theone->SetTarget(iter->melee_creep_);
				return;
			}
		}
		pos = iter->ranged_creep_->getPosition();
		if (iter->ranged_creep_->CanBeTarget)
		{
			x = fabs(onepos.x - pos.x);
			y = fabs(onepos.x - pos.y);
			if (theone->GetRange() >= hypotf(x, y))
			{
				theone->SetTarget(iter->ranged_creep_);
				return;
			}
		}
		pos = iter->siege_creep_->getPosition();
		if (iter->siege_creep_->CanBeTarget)
		{
			x = fabs(onepos.x - pos.x);
			y = fabs(onepos.x - pos.y);
			if (theone->GetRange() >= hypotf(x, y))
			{
				theone->SetTarget(iter->siege_creep_);
				return;
			}
		}
	}
	theone->SetTarget(nullptr);
}

void PlayingScene::SelectTarget()
{
	this->SelectTargetForR(this->hero_player_);
	this->SelectTargetForR(this->r_ancient_);
	this->SelectTargetForR(this->r_fountain_);
	this->SelectTargetForR(this->r_tower_);
	for (std::vector<Creeps*>::iterator iter = this->r_creeps_.begin(); iter != this->r_creeps_.end(); ++iter)
	{
		this->SelectTargetForR(iter->melee_creep_);
		this->SelectTargetForR(iter->ranged_creep_);
		this->SelectTargetForR(iter->siege_creep_);
	}
	this->SelectTargetForD(this->hero_enemy_);
	this->SelectTargetForD(this->d_ancient_);
	this->SelectTargetForD(this->d_fountain_);
	this->SelectTargetForD(this->d_tower_);
	for (std::vector<Creeps*>::iterator iter = this->d_creeps_.begin(); iter != this->d_creeps_.end(); ++iter)
	{
		this->SelectTargetForD(iter->melee_creep_);
		this->SelectTargetForD(iter->ranged_creep_);
		this->SelectTargetForD(iter->siege_creep_);
	}
}

void PlayingScene::AiAttack()
{
	if (this->hero_enemy_->GetTarget == nullptr)
		this->hero_enemy_->useAI();
	else
		this->hero_enemy_->Attack();
	/***********************************/
	if (this->r_ancient_->GetTarget == nullptr)
		;
	else
		this->r_ancient_->Attack();
	if (this->r_fountain_->GetTarget == nullptr)
		;
	else
		this->r_fountain_->Attack();
	if (this->r_tower_->GetTarget == nullptr)
		;
	else
		this->r_tower_->Attack();
	/***********************************/
	if (this->d_ancient_->GetTarget == nullptr)
		;
	else
		this->d_ancient_->Attack();
	if (this->d_fountain_->GetTarget == nullptr)
		;
	else
		this->d_fountain_->Attack();
	if (this->d_tower_->GetTarget == nullptr)
		;
	else
		this->d_tower_->Attack();
	/***********************************/
	for (std::vector<Creeps*>::iterator iter = this->r_creeps_.begin(); iter != this->r_creeps_.end(); ++iter)
	{
		if (iter->melee_creep_->GetTarget == nullptr)
			iter->melee_creep_->useAI();
		else
			iter->melee_creep_->Attack();
		if (iter->ranged_creep_->GetTarget == nullptr)
			iter->ranged_creep_->useAI();
		else
			iter->ranged_creep_->Attack();
		if (iter->siege_creep_->GetTarget == nullptr)
			iter->siege_creep_->useAI();
		else
			iter->siege_creep_->Attack();
	}
	/***********************************/
	for (std::vector<Creeps*>::iterator iter = this->d_creeps_.begin(); iter != this->d_creeps_.end(); ++iter)
	{
		if (iter->melee_creep_->GetTarget == nullptr)
			iter->melee_creep_->useAI();
		else
			iter->melee_creep_->Attack();
		if (iter->ranged_creep_->GetTarget == nullptr)
			iter->ranged_creep_->useAI();
		else
			iter->ranged_creep_->Attack();
		if (iter->siege_creep_->GetTarget == nullptr)
			iter->siege_creep_->useAI();
		else
			iter->siege_creep_->Attack();
	}
}

void PlayingScene::win() {
	this->label_win->setVisible(true);
	this->back_ground->setVisible(true);
}
void PlayingScene::lose() {
	this->label_lose->setVisible(true);
	this->back_ground->setVisible(true);
}
