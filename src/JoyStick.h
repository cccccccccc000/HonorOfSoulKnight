#ifndef JoyStick_h
#define JoyStick_h

#include "cocos2d.h"

/*定义摇杆方向的枚举*/
typedef enum direction
{
	STAY = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	R_UP, //右上
	R_DOWN,
	L_UP,
	L_DOWN

}RDIRECTION;

class JoyStick : public cocos2d::Layer
{
public:
	virtual bool init() override;

	CREATE_FUNC(JoyStick);

	virtual void onEnter() override;
	virtual void onExit() override;

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;

	/*检查当前角度并设置方向*/
	void checkDirection(float angle);

	cocos2d::Sprite* getRocker();
	cocos2d::Sprite* getRockerBg();
	float getAngle();
	RDIRECTION getDir();

private:
	cocos2d::EventListenerTouchOneByOne* listener;  /*定义为成员变量，方便移除监听*/
	cocos2d::Sprite* rocker;  /*方便获取*/
	cocos2d::Sprite* rocker_bg;  /*方便获取*/
	RDIRECTION dir;
	float angle;  /*当前的弧度*/
};

#endif /* JoyStick_hpp */