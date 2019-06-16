#include "Bullet.h"

bool Bullet::initBullet(std::string file_name)
{
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(file_name);
	this->setTexture(texture);
}

 Bullet* Bullet::createWithType(std::string file_name)
{
	Bullet* bullet = new Bullet();
	if (bullet && bullet->initBullet(file_name))
	{
		bullet->autorelease();
		return bullet;
	}
	else
	{
		delete bullet;
		bullet = NULL;
		return NULL;
	}
}


 void Bullet::Die()
{
	this->unusable = true;
	this->setVisible(false);
}

void Bullet::move(cocos2d::Point position)
{
	Point destination = this->maplayer->tileToWin(position);
	float x = fabs(destination.x - this->getPosition().x);
	float y = fabs(destination.y - this->getPosition().y);
	float distance = hypot(x, y);
	float time = distance / this->bullet_speed;
	MoveTo* moveto = MoveTo::create(time, destination);
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	scene->bullet_seq.insert(std::pair<Bullet*, MoveTo*>(this, moveto));
	this->runAction(moveto);
}


