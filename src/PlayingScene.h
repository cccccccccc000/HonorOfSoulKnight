
#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include "Layer.h"

USING_NS_CC;

class PlayingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

   virtual bool init();
   
	CREATE_FUNC(PlayingScene);
	
private:
	

};
#endif // __PLAY_SCENE_H__
