
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



void PlayingScene::onTouchEnded(Touch* touch, Event* unused_event)
{
	auto actionTo1 = RotateTo::create(0, 0, 180);
	auto actionTo2 = RotateTo::create(0, 0, 0);
	auto touchLocation = touch->getLocation();

	touchLocation = this->convertToNodeSpace(touchLocation);


	auto playerPos = saber->getPosition();
	auto diff = touchLocation - playerPos;

	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerPos.x += tiled_map_1v1->getTileSize().width / 2;
			saber->runAction(actionTo2);
		}
		else {
			playerPos.x -= tiled_map_1v1->getTileSize().width / 2;
			saber->runAction(actionTo1);
		}
	}
	else {
		if (diff.y > 0) {
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

	this->setViewPointCenter(saber->getPosition());

}


void PlayingScene::setPlayerPosition(Point position)
{
	saber->setPosition(position);
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

/*
	auto map = TMXTiledMap::create("tiled_map_1v1.tmx");
	addChild(map, 0);
	auto layer1 = map->getLayer("ground");
	auto layer2 = map->getLayer("pic1");
	auto layer3 = map->getLayer("pic2");
*/
	TMXObjectGroup* objects = tiled_map_1v1->getObjectGroup("hero");
	CCASSERT(NULL != objects, "'hero' object group not found");

	auto playerShowUpPoint = objects->getObject("saber");
	CCASSERT(!playerShowUpPoint.empty(), "saber object not found");


	int x = playerShowUpPoint["x"].asInt();
	int y = playerShowUpPoint["y"].asInt();


	saber = Sprite::create("saber.png");
	saber->setPosition(x + tiled_map_1v1->getTileSize().width / 2, y + tiled_map_1v1->getTileSize().height / 2);
	saber->setScale(0.1);


	addChild(saber);
	setViewPointCenter(saber->getPosition());


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch * touch, Event * unused_event)->bool {return true; };
	listener->onTouchEnded = CC_CALLBACK_2(PlayingScene::onTouchEnded, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}



void PlayingScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
