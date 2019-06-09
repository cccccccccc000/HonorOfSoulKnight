
#include "PlayingScene.h"
#include "SimpleAudioEngine.h"
#include "HRocker.h"

USING_NS_CC;

Scene* PlayingScene::createScene()
{
    return PlayingScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool PlayingScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//2.set background scene
	auto bgmap = Sprite::create("PlayGround.jpg");
	bgmap->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	Size mywinsize = Director::getInstance()->getWinSize();
	float winw = mywinsize.width; //获取屏幕宽度
	float winh = mywinsize.height;//获取屏幕高度
	float spx = bgmap->getTextureRect().getMaxX();
	float spy = bgmap->getTextureRect().getMaxY();
	bgmap->setScaleX(winw / spx); //设置精灵宽度缩放比例
	bgmap->setScaleY(winh / spy);
	this->addChild(bgmap, 0);

	//3.创建虚拟摇杆

//添加摇杆  
	Sprite *spRocker2 = Sprite::create("rockerBar.png");//摇杆
	Sprite *spRockerBG2 = Sprite::create("rocker.png");//摇杆背景
	HRocker* rocker2 = HRocker::HRockerWithCenter(Vec2(210.0f, 130.0f), 50.0f, spRocker2, spRockerBG2, true);
	//创建摇杆
	this->addChild(rocker2);

	//添加精灵  
	hero = Hero::create();
	hero->InitHeroSprite("hero.jpg");
	hero->setPosition(ccp(200, 400));
	this->addChild(hero, 1);
	hero->setScale(0.5);
	hero->SetAnimation("hero_run.plist", "hero_run.png", 10, true); 

	return true;

}


void PlayingScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();


}
