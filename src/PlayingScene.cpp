
#include "PlayingScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* PlayingScene::createScene()
{
    return PlayingScene::create();
}


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void PlayingScene::setViewPointCenter(Point position) {
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
void PlayingScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode code, Event* unused_event)
{
	auto playerPos = _hero->getPosition();
	if (code == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || code == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		if (code == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
			playerPos.x += tiled_map_1v1->getTileSize().width / 2;
			_hero->setFlipX(false);
		}
		else {
			playerPos.x -= tiled_map_1v1->getTileSize().width / 2;
			_hero->setFlippedX(true);
		}
	}
	else {
		if (code == EventKeyboard::KeyCode::KEY_UP_ARROW) {
			playerPos.y += tiled_map_1v1->getTileSize().height / 2;
		}
		else {
			playerPos.y -= tiled_map_1v1->getTileSize().height / 2;
		}
	}

	if (playerPos.x <= (tiled_map_1v1->getMapSize().width * tiled_map_1v1->getMapSize().width) &&
		playerPos.y <= (tiled_map_1v1->getMapSize().height * tiled_map_1v1->getMapSize().height) &&
		playerPos.y >= 0 &&
		playerPos.x >= 0)
	{
		this->setPlayerPosition(playerPos);
	}

	this->setViewPointCenter(_hero->getPosition());

}


void PlayingScene::setPlayerPosition(Point position)
{
	_hero->setPosition(position);
}

bool PlayingScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	std::string file = "tiled_map_1v1.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	tiled_map_1v1 = TMXTiledMap::createWithXML(str->getCString(), "");
	ground = tiled_map_1v1->layerNamed("ground");


	addChild(tiled_map_1v1, -1);
	auto map = TMXTiledMap::create("tiled_map_1v1.tmx");
	addChild(map, 0);
	auto layer1 = map->getLayer("ground");
	auto layer2 = map->getLayer("pic1");
	auto layer3 = map->getLayer("pic2");

	TMXObjectGroup* objects = tiled_map_1v1->getObjectGroup("hero");
//	CCASSERT(NULL != objects, "'hero' object group not found");

	auto playerShowUpPoint = objects->getObject("_hero");
	//CCASSERT(!playerShowUpPoint.empty(), "_hero object not found");


	int x = playerShowUpPoint["x"].asInt();
	int y = playerShowUpPoint["y"].asInt()；


	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/role.plist", "images/role.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/ui.plist", "images/ui.pvr.ccz");

	//add player
	_hero = Player::create(Player::PlayerType::HERO);
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
	_listener_touch->onTouchBegan = CC_CALLBACK_2(PlayingScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener_touch, this);

	auto attackItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(PlayingScene::attackCallback, this));

	attackItem->setPosition(Vec2(origin.x + visibleSize.width - attackItem->getContentSize().width / 2,
		origin.y + attackItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(attackItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	_progress = Progress::create("player-progress-bg.png", "player-progress-fill.png");
	_progress->setPosition(_progress->getContentSize().width / 2, this->getContentSize().height - _progress->getContentSize().height / 2);
	this->addChild(_progress);
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event * event) {
		log("KeyPress:%d", keyCode);
		if (keyCode ==EventKeyboard::KeyCode::KEY_UP_ARROW|| keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW|| keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW|| keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
			return true;
		else
			return false;
	};
	listener->onKeyReleased = CC_CALLBACK_2(PlayingScene::onKeyReleased,this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void PlayingScene::menuCloseCallback(cocos2d::Ref* pSender)
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

bool PlayingScene::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 pos = this->convertToNodeSpace(touch->getLocation());
	_hero->walkTo(pos);
	log("MainScene::onTouchBegan");
	_enemy->autoDoAction(_hero);



	return true;
}

void PlayingScene::attackCallback(Ref* pSender)
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
