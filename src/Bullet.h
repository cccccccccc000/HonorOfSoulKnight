#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Layer.h"

USING_NS_CC;

class MapLayer : public cocos2d::Layer
{
public:
	static cocos2d::Layer* createLayer();

	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(MapLayer);

	void setViewPointCenter(cocos2d::Point position);
	void MapLayer::onKeyReleased(EventKeyboard::KeyCode code, Event* unused_event);
	bool canMove(cocos2d::Point position);
	bool onTouchBegan(Touch* touch, Event* event);
	void MapLayer::menuPauseCallback(Ref* pSender);
	cocos2d::Point tileToWin(cocos2d::Point position);
	cocos2d::Point winToTile(cocos2d::Point position);

private:
	cocos2d::TMXTiledMap* tiled_map_1v1;
	cocos2d::TMXLayer* ground;
	cocos2d::TMXLayer* unblocked;
	EventListenerTouchOneByOne* _listener_touch;
	Progress* _progress;
	Sequence* _seq;

};

class Bullet :public cocos2d::Sprite
{
public:
	bool initBullet(std::string file_name);
	static Bullet* createWithType(std::string file_name);
	void Die();
	void move(cocos2d::Point position);
private:
	bool unusable;
	float bullet_speed;
	MapLayer* maplayer = nullptr;
};
#endif