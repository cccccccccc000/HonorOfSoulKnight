
#include "Layer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Layer* EquipLayer::createLayer()
{
    return EquipLayer::create();
}

void EquipLayer::botton_callback(Ref* sender) {
	;
}

bool EquipLayer::init(){
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*
	auto botton_callback = [](Ref* sender) {
		;// your code here
	}
	*/

    auto EQUIP_button1 = Sprite::create("NEWGAME_button1.png");
	auto EQUIP_button2 = Sprite::create("NEWGAME_button2.png");
    auto EQUIP_button = MenuItemSprite::create(
		EQUIP_button1,
		EQUIP_button2,
		CC_CALLBACK_1(EquipLayer::botton_callback, this));
    //

    auto menu = Menu::create(EQUIP_button, NULL);
	menu->alignItemsVertically();
	menu->setAnchorPoint(Point(0.5, 0.5));
	menu->setPosition(Vec2(visibleSize.width / 10*2 + origin.x, visibleSize.height /10*9 + origin.y));
    this->addChild(menu, 1);

    return true;
}