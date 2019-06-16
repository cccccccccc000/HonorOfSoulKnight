
#include "Gamepause.h"
#include "MenuScene.h"//�ص����˵���ͷ�ļ�
#include "SelectingScene.h" //���¿�ʼѡ��
#include "PlayingScene.h"
#include "cocos2d.h"
USING_NS_CC;
//����һ��CCrenderTexture 
//�൱��һ���������е���Ϸ�Ľ�ͼ��Ϊ�����ͣ�Ի���ı��� 
//�����Ϳ��������ǶԻ�������Ϸ����֮�ϣ�һ����Ϸ���ж���������д�ġ�
CCScene* Gamepause::scene(CCRenderTexture* sqr)
{

	CCScene *scene = CCScene::create();
	Gamepause *layer = Gamepause::create();
	scene->addChild(layer,1);//����Ϸ������棬���ǻ�Ҫ��������Ű�ť


//���Ӳ��֣�ʹ��Game�����н�ͼ��sqr����ͼƬ����Sprite
//����Sprite��ӵ�GamePause��������
//�õ����ڵĴ�С
	CCSize visibleSize = CCDirector::getInstance()->getVisibleSize();
	CCSprite *back_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
	back_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); //����λ��,������������λ�á�
	back_spr->setFlipY(true);            //��ת����ΪUI�����OpenGL���겻ͬ
	back_spr->setColor(cocos2d::Color3B::GRAY); //ͼƬ��ɫ���ɫ
	scene->addChild(back_spr);


	//�����Ϸ��ͣ����Сͼ�������Ű�ť
	CCSprite *back_small_spr = CCSprite::create("pause.png");
	back_small_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); //����λ��,������������λ�á�
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

	//������Ϸ��ť
	CCMenuItemImage *pContinueItem = CCMenuItemImage::create(
		"continue.png",
		"continue.png",
		this,
		menu_selector(Gamepause::menuContinueCallback));
	pContinueItem->setScale(1.5);
	pContinueItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 30));

	//���¿�ʼ��Ϸ��ť
	CCMenuItemImage *pRestartItem = CCMenuItemImage::create(
		"restart.png",
		"restart.png",
		this,
		menu_selector(Gamepause::menuRestart));
	pRestartItem->setScale(1.5);
	pRestartItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 40));

	//��������
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
//��������
void  Gamepause::menuRestart(Ref* pSender)
{
	Director::getInstance()->replaceScene(SelectingScene::createScene());
}
//���¿�ʼѡ��
void  Gamepause::menuLogin(Ref* pSender)
{
	Director::getInstance()->replaceScene(MenuScene::createScene());
}