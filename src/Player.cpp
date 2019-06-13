#include "Player.h"
#include <iostream>

bool Player::initWithPlayerType(PlayerType type)
{
    std::string sfName = "";
    std::string animationNames[5] = {"attack", "dead", "hit", "stay", "walk"};
    _animationNames.assign(animationNames,animationNames+5);
    switch (type)
    {
    case PlayerType::HERO:
        {
        _name = "hero";
        sfName = "hero-stay0000.png";
        _isShowBar = false;
        int animationFrameNums[5] = {10, 12, 15, 30, 24};
        _animationFrameNums.assign(animationFrameNums, animationFrameNums+5);
        _speed = 100;
        break;
        }
    case PlayerType::ENEMY:
        {
        _name = "enemy";
        sfName = "enemy-stay0000.png";
        _isShowBar = true;
        int animationFrameNums[5] = {21, 21, 24, 30, 24};
        _animationFrameNums.assign(animationFrameNums, animationFrameNums+5);
        _speed = 150;
        break;
        }
    }
    this->initWithSpriteFrameName(sfName);
    this->addAnimation();

    auto size = this->getContentSize();
    _progress = Progress::create("small-enemy-progress-bg.png","small-enemy-progress-fill.png");
    _progress->setPosition( size.width/2, size.height + _progress->getContentSize().height/2);
    this->addChild(_progress);
    if(!_isShowBar)
    {
        _progress->setVisible(false);
    }

    return true;
}
Player* Player::create(PlayerType type)
{
    Player* player = new Player();
    if (player && player->initWithPlayerType(type))
    {
        player->autorelease();
        player->setAnchorPoint(Vec2(0.5, 0));
        return player;
    }
    else
    {
        delete player;
        player = NULL;
        return NULL;
    }
}
void Player::addAnimation()
{
    auto animation = AnimationCache::getInstance()->getAnimation(String::createWithFormat("%s-%s", _name.c_str(),
                                                            _animationNames[0].c_str())->getCString());
    if (animation)
        return;
    for (int i = 0; i < _animationNum; i ++)
    {
        auto animation = Animation::create();
        animation->setDelayPerUnit(0.05);
        for (int j = 0; j < _animationFrameNums[i]; j ++)
        {
            auto sfName = String::createWithFormat("%s-%s%04d.png", _name.c_str(), _animationNames[i].c_str(), j)->getCString();
            animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName));
            if (!animation)
            log("hello ha ha");
        }
        AnimationCache::getInstance()->addAnimation(animation, String::createWithFormat("%s-%s", _name.c_str(),
                                                            _animationNames[i].c_str())->getCString());
    }
}
void Player::playAnimationForever(std::string animationName)
{
    auto str = String::createWithFormat("%s-%s", _name.c_str(), animationName.c_str())->getCString();
    bool exist = false;
    for (int i = 0; i < _animationNum; i ++) {
        if (animationName == _animationNames[i])
        {
            exist = true;
            break;
        }
    }
    if (exist == false)
        return;
    auto animation = AnimationCache::getInstance()->getAnimation(str);
	auto animate = RepeatForever::create(Animate::create(animation));
	this->runAction(animate);
}

void Player::playAnimation(std::string animationName)
{
    auto str = String::createWithFormat("%s-%s", _name.c_str(), animationName.c_str())->getCString();
    bool exist = false;
    for (int i = 0; i < _animationNum; i ++) {
        if (animationName == _animationNames[i])
        {
            exist = true;
            break;
        }
    }
    if (exist == false)
        return;
    auto animation = AnimationCache::getInstance()->getAnimation(str);
    auto func = [&]()
	{
		this->stopAllActions();
		this->playAnimationForever("stay");
		_seq = nullptr;
	};
	auto callback = CallFunc::create(func);
	auto animate = Sequence::create(Animate::create(animation), callback,NULL);
	this->runAction(animate);
}

void Player::walkTo(Vec2 dest)
{
    if (_seq)
        this->stopAction(_seq);
    auto curPos = this->getPosition();
    if (curPos.x > dest.x)
        this->setFlippedX(true);
    else
        this->setFlippedX(false);
    auto diff = dest - curPos;
    auto time = diff.getLength() / _speed;
    auto moveTo = MoveTo::create(time, dest);
    auto func = [&]()
	{
		this->stopAllActions();
		this->playAnimationForever("stay");
		_seq = nullptr;
	};
	auto callback = CallFunc::create(func);
	this->stopAllActions();
	this->playAnimationForever("walk");
	_seq = Sequence::create(moveTo, callback, nullptr);

    this->runAction(_seq);
}

void Player::getHit()
{
    float blood = _progress->getProgress();
    if (_name == "hero")
        blood -= 3;
    else
        blood -= 5;
    _progress->setProgress(blood);
    log(String::createWithFormat("hit now blood is %f", blood)->getCString());
    if (blood <= 0)
    {
        log(String::createWithFormat("%s is dead.", _name.c_str())->getCString());
        auto func = [&]()
        {
            this->stopAllActions();
            this->playAnimation("dead");
        };
        auto callback = CallFunc::create(func);
        _seq = Sequence::create(callback, nullptr);
        this->runAction(_seq);
        this->_progress->setVisible(false);
        this->setVisible(false);
        return;
    }
}

void Player::autoDoAction(Player* hero) // just for _enemy
{
    Vec2 dest = hero->getPosition();
    if (_seq)
        this->stopAction(_seq);
    auto curPos = this->getPosition();
    if (curPos.x > dest.x)
        this->setFlippedX(true);
    else
        this->setFlippedX(false);
    auto diff = dest - curPos;
    if (diff.x > 0) diff.x -= 90;
    else diff.x += 90;
    if (diff.y > 0) diff.y -= 20;
    else diff.y += 20;
    auto time = diff.getLength() / _speed;
    auto moveTo = MoveTo::create(time, dest);
    auto func = [&]()
	{
		this->stopAllActions();
		this->playAnimationForever("stay");
		_seq = nullptr;
	};
	auto callback = CallFunc::create(func);
	this->stopAllActions();
	this->playAnimationForever("walk");
	_seq = Sequence::create(moveTo, callback, nullptr);

    this->runAction(_seq);
}

void Player::autoAttack(Player* hero) // just for _enemy
{
    float blood = _progress->getProgress();
    if (blood <= 0)
        return;
    Vec2 del = this->getPosition() - hero->getPosition();
    if (del.length() <= 100)
    {
        this->playAnimation("attack");
        hero->getHit();
    }
}
