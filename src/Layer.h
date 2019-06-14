
#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H__

#include "cocos2d.h"

#include "Player.h"
USING_NS_CC;

class MapLayer : public cocos2d::Layer
{
public:
    static cocos2d::Layer* createLayer();

    virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC (MapLayer);
    
	void setViewPointCenter(cocos2d::Point position);
	void MapLayer::onKeyReleased(EventKeyboard::KeyCode code, Event* unused_event);
	void setPlayerPosition(cocos2d::Point position);
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void attackCallback(Ref* pSender);
	cocos2d::Point tileCoordForPosition(cocos2d::Point position);
private:
	cocos2d::TMXTiledMap* tiled_map_1v1;
	cocos2d::TMXLayer* ground;
	cocos2d::TMXLayer* block;
	Player* _hero;
	Player* _enemy;
	EventListenerTouchOneByOne* _listener_touch;
	Progress* _progress;

};
#endif // __MAP_LAYER_H__


#ifndef __EQUIP_LAYER_H__
#define __EQUIP_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class EquipLayer : public cocos2d::Layer
{
public:
    static cocos2d::Layer* createLayer();

    virtual bool init();
    
	CREATE_FUNC (EquipLayer);
	
	void botton_callback(Ref* sender);

private:
	

};
#endif // __EQUIP_LAYER_H__