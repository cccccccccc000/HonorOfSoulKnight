#pragma once
#ifndef __Gamepause__H__
#define __Gamepause__H__
#include "cocos2d.h"
USING_NS_CC;
class Gamepause : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene(CCRenderTexture* sqr);
	CREATE_FUNC(Gamepause);
	//继续游戏
	void menuContinueCallback(Ref* pSender);
	//重新开始游戏
	void menuRestart(Ref* pSender);
	//回主界面
	void menuLogin(Ref* pSender);

};

#endif // __Gamepause_H__
