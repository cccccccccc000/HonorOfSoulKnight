
#include "PlayingScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* PlayingScene::createScene()
{
    auto scene = PlayingScene::create();

	auto maplayer = MapLayer::create();
	scene->addChild(maplayer, -1);

	auto equiplayer = EquipLayer::create();
	scene->addChild(equiplayer, 1);

	return scene;
}


bool PlayingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    

	return true;
}

