
#include "Gamepause.h"
#include "MenuScene.h"//回到主菜单的头文件
#include "SelectingScene.h" //重新开始选择
#include "PlayingScene.h"
#include "cocos2d.h"
USING_NS_CC;
//传入一个CCrenderTexture 
//相当于一个正在运行的游戏的截图作为这个暂停对话框的背景 
//这样就看起来像是对话框在游戏界面之上，一般游戏当中都是这样子写的。
CCScene* Gamepause::scene(CCRenderTexture* sqr)
{

	CCScene *scene = CCScene::create();
	Gamepause *layer = Gamepause::create();
	scene->addChild(layer,1);//把游戏层放上面，我们还要在这上面放按钮


//增加部分：使用Game界面中截图的sqr纹理图片创建Sprite
//并将Sprite添加到GamePause场景层中
//得到窗口的大小
	CCSize visibleSize = CCDirector::getInstance()->getVisibleSize();
	CCSprite *back_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
	back_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); //放置位置,这个相对于中心位置。
	back_spr->setFlipY(true);            //翻转，因为UI坐标和OpenGL坐标不同
	back_spr->setColor(cocos2d::Color3B::GRAY); //图片颜色变灰色
	scene->addChild(back_spr);


	//添加游戏暂停背景小图，用来放按钮
	CCSprite *back_small_spr = CCSprite::create("pause.png");
	back_small_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); //放置位置,这个相对于中心位置。
	scene->addChild(back_small_spr);


	return scene;
}

bool Gamepause::init()
{

	if (!CCLayer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//继续游戏按钮
	CCMenuItemImage *pContinueItem = CCMenuItemImage::create(
		"continue.png",
		"continue.png",
		this,
		menu_selector(Gamepause::menuContinueCallback));
	pContinueItem->setScale(1.5);
	pContinueItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 30));

	//重新开始游戏按钮
	CCMenuItemImage *pRestartItem = CCMenuItemImage::create(
		"restart.png",
		"restart.png",
		this,
		menu_selector(Gamepause::menuRestart));
	pRestartItem->setScale(1.5);
	pRestartItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 40));

	//回主界面
	CCMenuItemImage *pLoginItem = CCMenuItemImage::create(
		"login.png",
		"login.png",
		this,
		menu_selector(Gamepause::menuLogin));
	pLoginItem->setScale(1.5);
	pLoginItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 110));


	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pContinueItem, pRestartItem, pLoginItem, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu, 2);


	return true;
}
void Gamepause::menuContinueCallback(Ref* pSender)
{
	Director::getInstance()->popScene();

}
//回主界面
void  Gamepause::menuRestart(Ref* pSender)
{
	Director::getInstance()->replaceScene(SelectingScene::createScene());
}
//重新开始选择
void  Gamepause::menuLogin(Ref* pSender)
{
	Director::getInstance()->replaceScene(MenuScene::createScene());
}