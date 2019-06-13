
#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
USING_NS_CC;
class PlayingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(PlayingScene);
	void setViewPointCenter(cocos2d::Point position);
	void PlayingScene::onKeyReleased(EventKeyboard::KeyCode code, Event* unused_event);
	void setPlayerPosition(cocos2d::Point position);
	bool onTouchBegan(Touch* touch, Event* event);
	void attackCallback(Ref* pSender);
private:
	cocos2d::TMXTiledMap* tiled_map_1v1;
	cocos2d::TMXLayer* ground;
	Player* _hero;
	Player* _enemy;
	EventListenerTouchOneByOne* _listener_touch;
	Progress* _progress;

};
#endif // __PLAY_SCENE_H__
