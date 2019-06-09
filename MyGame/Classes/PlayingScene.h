
#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include "Hero.h"
#include "HRocker.h"

class PlayingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();  
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(PlayingScene);
private:
	HRocker* rocker;
	Hero* hero;
};

#endif // __PLAY_SCENE_H__
