#ifndef __SELECTING_SCENE_H__
#define __SELECTING_SCENE_H__

#include "cocos2d.h"

class SelectingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SelectingScene);

	// �л�scene
	void changescene_to_play_saber(Ref* sender);
	void changescene_to_play_archer(Ref* sender);
	void changescene_to_play_caster(Ref* sender);
};

#endif // __SELECTING_SCENE_H__
