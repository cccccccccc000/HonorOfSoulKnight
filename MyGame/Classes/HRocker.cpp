
#include "HRocker.h"

using namespace cocos2d;

//定义一个计时器，随时检测鼠标点击的位置
void HRocker::updatePos(float dt) {
	jsSprite->setPosition(ccpAdd(jsSprite->getPosition(), ccpMult(ccpSub(currentPoint, jsSprite->getPosition()), 0.5)));
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
void  HRocker::onTouchEnded(Touch* touch, Event* event)
{
	currentPoint = centerPoint;
	if (isFollowRole) {
		this->setVisible(false);
	}
}
HRocker* HRocker::initWithCenter(Vec2 aPoint, float aRadius, Sprite* aJsSprite, Sprite* aJsBg, bool _isFollowRole) {
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
	this->Active();//激活摇杆
	return this;
}