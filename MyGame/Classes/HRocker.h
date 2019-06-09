#ifndef HRocker_H
#define HRocker_H
#include "cocos2d.h"

using namespace cocos2d;

class HRocker :public Layer {
public:
	//初始化 aPoint是摇杆中心 aRadius是摇杆半径 aJsSprite是摇杆控制点 aJsBg是摇杆背景
	static HRocker*  HRockerWithCenter(Vec2 point, float Radius, Sprite* aJsSprite, Sprite* aJsBg, bool _isFollowRole);
	//启动摇杆
	void Active();
	//解除摇杆
	void Inactive();
	Vec2 getDirection();

private:
	EventListenerTouchOneByOne* touchListener;
	HRocker * initWithCenter(Vec2 point, float aRadius, Sprite* aJsSprite, Sprite* aJsBg, bool _isFollowRole);
	Vec2 centerPoint;//摇杆中心
	Vec2 currentPoint;//摇杆当前位置
	bool active;//是否激活摇杆
	float radius;//摇杆半径
	Sprite *jsSprite;
	bool isFollowRole;//是否跟随用户点击
	float getVelocity();
	void  updatePos(float dt);
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);

	CREATE_FUNC(HRocker);
};

#endif