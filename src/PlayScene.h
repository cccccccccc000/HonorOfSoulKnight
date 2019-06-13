#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class JoyStick;

class PlayScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	void PlayScene::addTouchEvent();
	virtual bool init();
	CCPoint convertToGL(CCSet *pTouches);
    CREATE_FUNC(PlayScene);
   
};

#endif // __PLAY_SCENE_H__
