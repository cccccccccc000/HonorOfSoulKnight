
#include "SelectingScene.h"
#include "SimpleAudioEngine.h"

#include "PlayingScene.h"

USING_NS_CC;

Scene* SelectingScene::createScene()
{
    return SelectingScene::create();
}


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// ÇÐ»» Scene to PlayingScene
void SelectingScene::changescene_to_play(Ref* sender) {

	Director::getInstance()->replaceScene(PlayingScene::createScene());
}

/*
void SelectingScene::onMouseUp(Event* event)
{
	EventMouse* e = (EventMouse*)event;



	auto moveBy = MoveBy::create(2, Vec2(0, -50));
	SABER_button1->runAction(moveBy);
}
*/
/*
bool saber_selected = true;
bool archer_selected = true;
bool caster_selected = true;


void SelectingScene::saberMove(Object* pSender)
{
	if (archer_selected == false)
	{
		auto moveBy = MoveBy::create(0, Vec2(0, 50));
		archer->runAction(moveBy);
		archer_selected == true;
	}
	if (caster_selected == false)
	{
		auto moveBy = MoveBy::create(0, Vec2(0, 50));
		caster->runAction(moveBy);
		caster_selected == true;
	}
	if (saber_selected == true)
	{
		auto moveBy = MoveBy::create(1, Vec2(0, -50));
		saber->runAction(moveBy);
		saber_selected == false;
	}
	
}

void SelectingScene::archerMove(Object* pSender)
{
	if (saber_selected == false)
	{
		auto moveBy = MoveBy::create(0, Vec2(0, 50));
		saber->runAction(moveBy);
		saber_selected == true;
	}
	if (caster_selected == false)
	{
		auto moveBy = MoveBy::create(0, Vec2(0, 50));
		caster->runAction(moveBy);
		caster_selected == true;
	}
	if (archer_selected == true)
	{
		auto moveBy = MoveBy::create(1, Vec2(0, -50));
		archer->runAction(moveBy);
		archer_selected == false;
	}
}

void SelectingScene::casterMove(Object* pSender)
{
	if (archer_selected == false)
	{
		auto moveBy = MoveBy::create(0, Vec2(0, 50));
		archer->runAction(moveBy);
		archer_selected == true;
	}
	if (saber_selected == false)
	{
		auto moveBy = MoveBy::create(0, Vec2(0, 50));
		saber->runAction(moveBy);
		saber_selected == true;
	}
	if (caster_selected == true)
	{
		auto moveBy = MoveBy::create(1, Vec2(0, -50));
		caster->runAction(moveBy);
		caster_selected == false;
	}
}
*/

bool SelectingScene::init()
{

    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto selecting_sofa = Sprite::create("selecting_sofa.png");
	if (selecting_sofa == nullptr)
	{
		problemLoading("'selecting_sofa.jpg'");
	}
	else
	{
		selecting_sofa->setScale((visibleSize.width / selecting_sofa->getContentSize().width) / 2);
		selecting_sofa->setAnchorPoint(Point(0.5, 0.5));
		selecting_sofa->setPosition(Vec2(origin.x + (visibleSize.width / 2),
			origin.y + visibleSize.height / 2));
		this->addChild(selecting_sofa, 2);
	}

	auto floor = Sprite::create("floor.png");
	if (selecting_sofa == nullptr)
	{
		problemLoading("'floor.jpg'");
	}
	else
	{
		floor->setAnchorPoint(Point(0.5, 0.5));
		floor->setPosition(Vec2(origin.x + (visibleSize.width / 2),	origin.y + visibleSize.height / 2 - 100));
		this->addChild(floor, 1);
	}


	auto saber = Sprite::create("saber.png");
	auto archer = Sprite::create("archer.png");
	auto caster = Sprite::create("caster.png");
	
	
	saber->setScale(0.3);
	archer->setScale(0.3);
	caster->setScale(0.3);

	saber->setPosition(Vec2(visibleSize.width / 2 + origin.x-130, visibleSize.height / 2 + origin.y-15));
	archer->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y-15));
	caster->setPosition(Vec2(visibleSize.width / 2 + origin.x+130, visibleSize.height / 2 + origin.y-15));

	this->addChild(saber,3);
	this->addChild(archer, 3);
	this->addChild(caster, 3);

/*	auto selecting_Listener = EventListenerMouse::create();
	selecting_Listener->onMouseUp = CC_CALLBACK_1(SelectingScene::onMouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(selecting_Listener, this);
	*/

	auto SABER_button1 = Sprite::create("SABER_button1.png");
	auto SABER_button2 = Sprite::create("SABER_button2.png");
	auto ARCHER_button1 = Sprite::create("ARCHER_button1.png");
	auto ARCHER_button2 = Sprite::create("ARCHER_button2.png");
    auto CASTER_button1 = Sprite::create("CASTER_button1.png");
	auto CASTER_button2 = Sprite::create("CASTER_button2.png");

	SABER_button1->setScale(0.5);
	ARCHER_button1->setScale(0.5);
	CASTER_button1->setScale(0.5);
	SABER_button2->setScale(0.5);
	ARCHER_button2->setScale(0.5);
	CASTER_button2->setScale(0.5);

	SABER_button1->setAnchorPoint(Point(0.5, 0.5));
	ARCHER_button1->setAnchorPoint(Point(0.5, 0.5));
	CASTER_button1->setAnchorPoint(Point(0.5, 0.5));
	SABER_button2->setAnchorPoint(Point(0.5, 0.5));
	ARCHER_button2->setAnchorPoint(Point(0.5, 0.5));
	CASTER_button2->setAnchorPoint(Point(0.5, 0.5));


	auto SABER_button = MenuItemSprite::create(
		SABER_button1,
		SABER_button2,
		CC_CALLBACK_1(SelectingScene::changescene_to_play, this));

	auto ARCHER_button = MenuItemSprite::create(
		ARCHER_button1,
		ARCHER_button2,
		CC_CALLBACK_1(SelectingScene::changescene_to_play, this));

	auto CASTER_button = MenuItemSprite::create(
		CASTER_button1,
		CASTER_button2,
		CC_CALLBACK_1(SelectingScene::changescene_to_play, this));


	auto select_menu = Menu::create(SABER_button, ARCHER_button, CASTER_button, NULL);
	select_menu->alignItemsHorizontally();
//	float padding = 50.0;
//	void alignItemsHorizontallyToCenterWithPadding(float padding);
	select_menu->setPosition(Vec2(visibleSize.width / 2 + origin.x + 70, visibleSize.height / 2 + origin.y + 170));
    this->addChild(select_menu, 2);


    auto select_title = Label::createWithTTF("Select Your Servant", "fonts/Marker Felt.ttf", 35);
    if (select_title == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
		select_title->setAnchorPoint(Point(0.5, 0.5));
		select_title->setScale((visibleSize.width / select_title->getContentSize().width) / 2);
		select_title->setPosition(Vec2(origin.x + (visibleSize.width / 2),
			origin.y + visibleSize.height - select_title->getContentSize().height- select_title->getContentSize().height));
        this->addChild(select_title, 1);
    }

	return true;
}



void SelectingScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
