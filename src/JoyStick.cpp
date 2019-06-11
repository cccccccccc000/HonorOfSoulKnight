#include "JoyStick.h"

USING_NS_CC;

bool JoyStick::init()
{
	if (!Layer::init()) {
		return false;
	}

	/*1. 创建摇杆的背景*/
	rocker_bg = Sprite::create("joystickBg.png");
	rocker_bg->setPosition(Vec2(150, 150));
	addChild(rocker_bg);

	/*2. 创建摇杆*/
	rocker = Sprite::create("joystick.png");
	rocker->setPosition(Vec2(150, 150));
	addChild(rocker);

	return true;
}

/*当前对象被加入到父类节点上会调用该方法*/
void JoyStick::onEnter()
{
	/*首先调用父类的onEnter方法*/
	Layer::onEnter();

	/*开启单点触摸的监听, 可以用auto*/
	listener = EventListenerTouchOneByOne::create();

	/*可以使用lambda表达式来创建，但那样看起来太乱, 这里我们还是使用回调函数*/
	listener->onTouchBegan = CC_CALLBACK_2(JoyStick::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(JoyStick::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(JoyStick::onTouchEnded, this);

	/*注册监听*/
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}

/*当前对象从父类上移除时会调用该方法*/
void JoyStick::onExit()
{
	/*从分发中心移除注册的监听*/
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

	/*最后调用父类的onExit()方法*/
	Layer::onExit();
}

bool JoyStick::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	/*当触摸开始的时候， 如果触摸点的位置和我们中心点位置的距离 < 圆的半径 我们才能Move*/

	/*获取圆心点和半径*/
	float radius = rocker_bg->getContentSize().width / 2;
	Vec2 center = rocker_bg->getPosition();

	if (touch->getLocation().distance(center) > radius) {
		return false;
	}
	else {
		rocker->setPosition(Vec2(touch->getLocation()));
		return true;
	}

}

void JoyStick::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	/*当触摸移动的时候， 如果触摸点的位置和我们中心点位置的距离 < 圆的半径 */

	/*获取圆心点和半径*/
	float radius = rocker_bg->getContentSize().width / 2;
	Vec2 center = rocker_bg->getPosition();
	/*获取触摸点位置*/
	Vec2 touch_pos = touch->getLocation();
	float dis = touch_pos.distance(center);
	angle = acos((touch_pos.x - center.x) / dis);
	if (touch_pos.y > center.y) {
		checkDirection(angle);
	}
	else {
		checkDirection(-angle);
	}

	if (dis <= radius) {
		rocker->setPosition(Vec2(touch_pos));
	}
	else {
		/*如果在上半圆*/
		if (touch_pos.y > center.y) {
			rocker->setPosition(Vec2(center.x + radius * cos(angle), center.y + radius * sin(angle)));
		}
		else {
			rocker->setPosition(Vec2(center.x + radius * cos(angle), center.y - radius * sin(angle)));
		}
	}


}

void JoyStick::checkDirection(float angle)
{
	/*右方向*/
	if (angle >= -M_PI / 8.0 && angle <= M_PI / 8.0) {
		dir = RIGHT;
	}
	/*右边走 -八分之派 到 八分之派*/
	if (angle >= -(M_PI / 8.0) && angle <= M_PI / 8.0) {
		dir = RIGHT;
	}
	/*右上方向 八分之派 到 八分之三派*/
	else if (angle >= M_PI / 8.0 && angle < 3 * M_PI / 8.0) {
		dir = R_UP;
	}
	/*上方向 八分之三派 到 八分之五派*/
	else if (angle >= 3 * M_PI / 8.0 && angle <= 5 * M_PI / 8.0) {
		dir = UP;
	}
	/*左上方向 八分之5派 到 八分之七派*/
	else if (angle > 5 * M_PI / 8.0 && angle < 7 * M_PI / 8.0) {
		dir = L_UP;
	}
	/*左方向*/
	else if ((angle >= 7 * M_PI / 8.0 && angle <= M_PI) || (angle <= -7 * M_PI / 8.0 && angle >= -M_PI)) {
		dir = LEFT;
	}
	/*左下方向*/
	else if (angle > -7 * M_PI / 8.0 && angle < -5 * M_PI / 8.0) {
		dir = L_DOWN;
	}
	/*下方向*/
	else if (angle >= -5 * M_PI / 8.0 && angle <= -3 * M_PI / 8.0) {
		dir = DOWN;
	}
	/*右下方向*/
	else if (angle > -3 * M_PI / 8.0 && angle < -M_PI / 8.0) {
		dir = R_DOWN;
	}

}

void JoyStick::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	/*在结束触摸时，将摇杆归为原来位置*/
	rocker->setPosition(rocker_bg->getPosition());
	dir = STAY;
}

Sprite* JoyStick::getRocker()
{
	return rocker;
}
Sprite* JoyStick::getRockerBg()
{
	return rocker_bg;
}

float JoyStick::getAngle()
{
	return angle;
}

RDIRECTION JoyStick::getDir()
{
	return dir;
}
/*
#include "HRocker.h"

using namespace cocos2d;

//定义一个计时器，随时检测鼠标点击的位置
void HRocker::updatePos(float dt) {
	jsSprite->setPosition(ccpAdd(jsSprite->getPosition(), ccpMult(ccpSub(currentPoint, jsSprite->getPosition()), 0.5)));
}

bool HRocker::init()
{
	if (!Layer::init())
	{
		return false;
	}
	rocker_bg = Sprite
}
//启动摇杆
void HRocker::Active()
{
	if (!active) {
		active = true;
		schedule(schedule_selector(HRocker::updatePos));//添加刷新函数
		//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
		touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);

		touchListener->onTouchBegan = CC_CALLBACK_2(HRocker::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(HRocker::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(HRocker::onTouchEnded, this);
		// 注册事件监听机制
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	}
	else {
	}
}
//解除摇杆
void   HRocker::Inactive()
{
	if (active) {
		active = false;
		this->unschedule(schedule_selector(HRocker::updatePos));//删除刷新
		_eventDispatcher->removeEventListener(touchListener);//删除委托
	}
	else {
	}
}
//摇杆方位
Vec2 HRocker::getDirection()
{

	return ccpNormalize(ccpSub(centerPoint, currentPoint));
}
//摇杆力度
float HRocker::getVelocity()
{
	return ccpDistance(centerPoint, currentPoint);
}
HRocker* HRocker::HRockerWithCenter(Vec2 point, float aRadius, Sprite* aJsSprite, Sprite* aJsBg, bool _isFollowRole) {
	HRocker *jstick = HRocker::create();
	jstick->initWithCenter(point, aRadius, aJsSprite, aJsBg, _isFollowRole);
	return jstick;
}
bool HRocker::onTouchBegan(Touch* touch, Event* event)
{
	if (!active)
		return false;
	this->setVisible(true);
	Vec2 touchPoint = touch->getLocationInView();
	touchPoint = Director::sharedDirector()->convertToGL(touchPoint);
	if (!isFollowRole) {
		if (ccpDistance(touchPoint, centerPoint) > radius) {
			return false;
		}
	}
	currentPoint = touchPoint;
	if (isFollowRole) {
		centerPoint = currentPoint;
		jsSprite->setPosition(currentPoint);
		this->getChildByTag(88)->setPosition(currentPoint);
	}
	return true;
}
void  HRocker::onTouchMoved(Touch* touch, Event* event)
{
	Vec2 touchPoint = touch->getLocationInView();
	touchPoint = Director::sharedDirector()->convertToGL(touchPoint);
	if (ccpDistance(touchPoint, centerPoint) > radius)
	{
		currentPoint = ccpAdd(centerPoint, ccpMult(ccpNormalize(ccpSub(touchPoint, centerPoint)), radius));
	}
	else {
		currentPoint = touchPoint;
	}
}
void HRocker::checkDirection(float angle)
{
	/*右方向
	if (angle >= -M_PI / 4.0 && angle <= M_PI / 4.0) {
		dir = RIGHT;
	}
	/*上方向 
	else if (angle >= M_PI / 4.0 && angle < 3 * M_PI / 4.0) {
		dir = UP;
	}
	/*左方向
	else if ((angle >= 3 * M_PI / 4.0 && angle <= M_PI) || (angle <= -3 * M_PI / 4.0 && angle >= -M_PI)) {
		dir = LEFT;
	}
	/*下方向
	else if (angle >= -3 * M_PI / 4.0 && angle <= -M_PI / 4.0) {
		dir = DOWN;
	}

}
void  HRocker::onTouchEnded(Touch* touch, Event* event)
{
	currentPoint = centerPoint;
	if (isFollowRole) {
		this->setVisible(false);
	}
}
/*HRocker* HRocker::initWithCenter(Vec2 aPoint, float aRadius, Sprite* aJsSprite, Sprite* aJsBg, bool _isFollowRole) {
	isFollowRole = _isFollowRole;
	active = false;
	radius = aRadius;
	if (!_isFollowRole) {
		centerPoint = aPoint;
	}
	else {
		centerPoint = ccp(0, 0);
	}
	currentPoint = centerPoint;

	jsSprite = aJsSprite;
	jsSprite->setPosition(centerPoint);
	aJsBg->setPosition(centerPoint);
	aJsBg->setTag(88);
	this->addChild(aJsBg);
	this->addChild(jsSprite);
	if (isFollowRole) {
		this->setVisible(false);
	}
	this->Active();
	return this;
}
float HRocker::getAngle()
{
	return angle;
}
RDIRECTION HRocker::getDir()
{
	return dir;
}*/