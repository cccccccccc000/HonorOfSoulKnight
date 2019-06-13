#ifndef __PLAYING_SCENE_H__
#define __PLAYING_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class JoyStick;

class PlayingScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	void PlayingScene::addTouchEvent();
	virtual bool init();
	//virtual void update(float delta);
	CCPoint convertToGL(CCSet *pTouches);
    CREATE_FUNC(PlayingScene);
   
};

#endif // __HELLOWORLD_SCENE_H__
