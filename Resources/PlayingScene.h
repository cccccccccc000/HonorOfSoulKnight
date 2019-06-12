
#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"

class PlayingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(PlayingScene);
	void setViewPointCenter(cocos2d::Point position);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void setPlayerPosition(cocos2d::Point position);

private:
	cocos2d::TMXTiledMap* tiled_map_1v1;
	cocos2d::TMXLayer* ground;
	cocos2d::Sprite* saber;

};
#endif // __PLAY_SCENE_H__
