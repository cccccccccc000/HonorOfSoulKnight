#ifndef __SELECTING_SCENE_H__
#define __SELECTING_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
class SelectingScene : public cocos2d::Scene
{
public:
	

    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SelectingScene);

	// ÇÐ»»scene
	void changescene_to_play(Ref* sender);

//	void onMouseUp(Event* event);

//	void saberMove(Object* pSender);
//	void archerMove(Object* pSender);
//	void casterMove(Object* pSender);


//	Sprite* SABER; //= Sprite::create("saber.png");
//	Sprite* ARCHER; //= Sprite::create("archer.png");
//	Sprite* CASTER; //= Sprite::create("caster.png");
	
//	bool saber_selected;
//	bool archer_selected;
//  bool caster_selected;
};

	

#endif // __SELECTING_SCENE_H__
