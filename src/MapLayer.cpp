#include "GamePause.h"
#include "Layer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Layer* MapLayer::createLayer()
{
    return MapLayer::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}




bool MapLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	std::string file = "tiled_map_1v1.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	tiled_map_1v1 = TMXTiledMap::createWithXML(str->getCString(), "");
	ground = tiled_map_1v1->layerNamed("ground");
	unblocked = tiled_map_1v1->layerNamed("unblocked");
	unblocked->setVisible(false);
	addChild(tiled_map_1v1, -1);


	TMXObjectGroup* objects = tiled_map_1v1->getObjectGroup("hero");
	CCASSERT(NULL != objects, "'hero' object group not found");

	auto playerShowUpPoint = objects->getObject("_hero");
	CCASSERT(!playerShowUpPoint.empty(), "player object not found");


	int x = playerShowUpPoint["x"].asInt();
	int y = playerShowUpPoint["y"].asInt();


	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/role.plist", "images/role.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/ui.plist", "images/ui.pvr.ccz");

	//add player
	_hero = Player::create(Player::PlayerType::HERO);
	_hero->setPosition(Point(x, y));
	setViewPointCenter(_hero->getPosition());
	_hero->setScale(0.8);
	this->addChild(_hero);

	//add enemy1
	_enemy = Player::create(Player::PlayerType::ENEMY);
	_enemy->setPosition(origin.x + visibleSize.width - _enemy->getContentSize().width , origin.y + visibleSize.height );
	this->addChild(_enemy);

	_hero->playAnimationForever("stay");
	_enemy->playAnimationForever("stay");

	_listener_touch = EventListenerTouchOneByOne::create();
	_listener_touch->onTouchBegan = CC_CALLBACK_2(MapLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener_touch, this);


	_progress = Progress::create("player-progress-bg.png", "player-progress-fill.png");
	_progress->setPosition(_progress->getContentSize().width / 2, this->getContentSize().height - _progress->getContentSize().height / 2);
	this->addChild(_progress);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(MapLayer::onKeyReleased,this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);



	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(MapLayer::menuPauseCallback));

	pCloseItem->setPosition(Vec2(visibleSize.width - pCloseItem->getContentSize().width / 2,
		visibleSize.height - pCloseItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu, 1);

	return true;
}

void MapLayer::menuCloseCallback(cocos2d::Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

bool MapLayer::onTouchBegan(Touch* touch, Event* event)
{
	Point pos = this->convertToNodeSpace(touch->getLocation());

	if (canMove(pos) == true) {
		log("x = %f, y = %f", pos.x, pos.y);
		_enemy->autoDoAction(_hero);
		this->setViewPointCenter(_hero->getPosition());
		if (_seq)
			_hero->stopAction(_seq);
		auto curPos = _hero->getPosition();
		if (curPos.x > pos.x)
			_hero->setFlippedX(true);
		else
			_hero->setFlippedX(false);
		auto diff = pos - curPos;
		auto time = diff.getLength() / 100;
		auto moveTo = MoveTo::create(time, pos);
		auto func = [&]()
		{
			_hero->stopAllActions();
			_hero->playAnimationForever("stay");
			_seq = nullptr;
		};
		auto callback = CallFunc::create(func);
		_hero->stopAllActions();
		_hero->playAnimationForever("walk");
		_seq = Sequence::create(moveTo, callback, nullptr);

		_hero->runAction(_seq);


		return true;
	}
	else {
		return false;
	}
}

void MapLayer::menuPauseCallback(Ref* pSender)
{

	//得到窗口的大小
	CCSize visibleSize = CCDirector::getInstance()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width, visibleSize.height);
	CCScene *scene = CCDirector::sharedDirector()->getRunningScene();
	//遍历当前类的所有子节点信息，画入renderTexture中。
	//这里类似截图。
	renderTexture->begin();
	this->visit();
	renderTexture->end();

	//将游戏界面暂停，压入场景堆栈。并切换到GamePause界面
	CCDirector::sharedDirector()->pushScene(Gamepause::scene(renderTexture));
}

 Point MapLayer::tileToWin(Point position) //实际坐标转换为瓦片地图坐标
{
	int x = position.x / tiled_map_1v1->getTileSize().width;
	int y = ((tiled_map_1v1->getMapSize().height * tiled_map_1v1->getTileSize().height) - position.y) / tiled_map_1v1->getTileSize().height;
	return Point(x, y);
}

 Point MapLayer::winToTile(Point position)
 {
	 int x = position.x * tiled_map_1v1->getTileSize().width;
	 int y = (tiled_map_1v1->getMapSize().height * tiled_map_1v1->getTileSize().height) - position.y * tiled_map_1v1->getTileSize().height;
	 return Point(x, y);
 }


void MapLayer::setViewPointCenter(Point position) {
	auto winSize = Director::getInstance()->getWinSize();


	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (tiled_map_1v1->getMapSize().width * this->tiled_map_1v1->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (tiled_map_1v1->getMapSize().height * tiled_map_1v1->getTileSize().height) - winSize.height / 2);
	auto actualPosition = Point(x, y);

	auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actualPosition;
	this->setPosition(viewPoint);
}

void MapLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode code, Event* unused_event)
{
	if (code == EventKeyboard::KeyCode::KEY_A)
	{
		_hero->stopAllActions();
		_hero->playAnimation("attack");
		Vec2 del = _hero->getPosition() - _enemy->getPosition();
		float distance = del.length();
		log(String::createWithFormat("distance == %f", distance)->getCString());
		if (distance <= 100.0) {
			_enemy->getHit();
		}
		_enemy->autoAttack(_hero);
		_progress->setProgress(_hero->getProgress()->getProgress());
	}

}


bool MapLayer::canMove(Point position)  //判断是否在地图范围内
{
	Point tileCoord = this->tileToWin(position);
	int tileGid = unblocked->getTileGIDAt(tileCoord);
	if (tileGid) {
		auto properties = tiled_map_1v1->getPropertiesForGID(tileGid).asValueMap();
		if (!properties.empty()) {
			auto canMove = properties["unblocked"].asString();
			if ("true" == canMove) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	
}