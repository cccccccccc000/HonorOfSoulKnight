#include "PlayScene.h"
#include "cocos2d.h"


Scene* PlayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PlayScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(sprite);

	//注册监听
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);//阻止向下传递
	scheduleUpdate();
	listener->onTouchBegan = [](Touch* t, Event* e)
	{
		//获取事件绑定的target（目标）
		auto target = static_cast<Sprite*>(e->getCurrentTarget());
		//获取当前单击点所在相对按钮位置的坐标
		Point locationInNode = target->convertToNodeSpace(t->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (!rect.containsPoint(locationInNode))
		{
			log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
			target->setOpacity(180);
			return true;
		}
		return false;
	};

	listener->onTouchMoved = [](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		//显示当前精灵的坐标位置
		log("x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
		auto mymove = MoveTo::create(10,Point(touch->getLocation().x, touch->getLocation().y));//第一个参数是移动的时间
		target->runAction(mymove);//存在一个问题是，有时候会移动到别的地方
	};
	listener->onTouchEnded = [=](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		log("sprite onTouchesEnded.. ");
		target->setOpacity(255);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite);

	return true;
}
