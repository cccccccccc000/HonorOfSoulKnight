
#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H__

#include "cocos2d.h"
#include <map>
#include "Player.h"
#include "Hero.h"
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
	bool canMove(cocos2d::Point position);
	bool onTouchBegan(Touch* touch, Event* event);
	void MapLayer::menuPauseCallback(Ref* pSender);
	cocos2d::Point tileToWin(cocos2d::Point position);
	cocos2d::Point winToTile(cocos2d::Point position);
	Hero* hero_player;
	Hero* hero_enemy;
	std::vector<Creeps*> creeps;
	std::map<Bullet*, MoveTo*> bullet_seq;
private:
	cocos2d::TMXTiledMap* tiled_map_1v1;
	cocos2d::TMXLayer* ground;
	cocos2d::TMXLayer* unblocked;
	EventListenerTouchOneByOne* _listener_touch;
	Progress* _progress;
	Sequence* _seq;

};




#include "cocos2d.h"
#include "SkillButton.h"
USING_NS_CC;

class EquipLayer : public cocos2d::Layer
{
public:
	static cocos2d::Layer* createLayer();

	virtual bool init();

	CREATE_FUNC(EquipLayer);

	void death_number_my_hero_add_one(); //invoke this functoin, the death number of my hero add 1
	void death_number_enemy_hero_add_one(); //invoke this functoin, the death number of enemy hero add 1 

private:

	int int_death_number_my_hero = 0;
	int int_death_number_enemy_hero = 0;
	std::string string_death_number_my_hero = "0";
	std::string string_death_number_enemy_hero = "0";
	cocos2d::Sprite* equip_display;
	cocos2d::Menu* equip_display_Menu;
	cocos2d::Menu* equip_display_label;

};
#endif