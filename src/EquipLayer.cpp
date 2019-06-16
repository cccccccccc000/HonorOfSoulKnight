
#include "Layer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Layer* EquipLayer::createLayer()
{
	return EquipLayer::create();
}

void EquipLayer::death_number_my_hero_add_one() {
	int_death_number_my_hero++;
	string_death_number_my_hero = std::to_string(int_death_number_my_hero);
}

void EquipLayer::death_number_enemy_hero_add_one() {
	int_death_number_enemy_hero++;
	string_death_number_enemy_hero = std::to_string(int_death_number_enemy_hero);
}

// create equips and its label
#define MENU_AND_LABEL(string_equip_name,name_equip_number,Attribute_buff,int_money_number,int_set_width,string_buff_label,name_equip_menu)\
{\
	auto equip_name = Sprite::create(string_equip_name);\
	name_equip_number = MenuItemSprite::create(equip_name, equip_name,\
		[=](Ref* sender) {\
		Scene * sence =  Director::sharedDirector()->getRunningScene();\
		sence.hero_player_->PurchaseItem(Attribute_buff, int_money_number);\
	});\
	name_equip_number->setAnchorPoint(Point(0.5, 0.5));\
	name_equip_number->setPosition(Vec2(visibleSize.width /10 * int_set_width + origin.x, visibleSize.height *0.5 + origin.y));\
	auto equip_label = black_system_label(string_buff_label,17);\
	name_equip_menu = MenuItemLabel::create(equip_label);\
	name_equip_menu->setAnchorPoint(Point(0.5, 0.5));\
	name_equip_menu->setPosition(Vec2(visibleSize.width /10 * int_set_width + origin.x, visibleSize.height *0.4 + origin.y));\
}\


bool EquipLayer::init() {
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto black_system_label = [](std::string str, int word_size) {
		auto label = Label::createWithSystemFont(str, "Arial", word_size);
		label->setColor(Color3B(0, 0, 0));
		label->setAnchorPoint(Point(0.5, 0.5));
		return label;
	};

	//create equip display with all of equips
	{
		// create the backgroud of equip display
		equip_display = Sprite::create("equipbackground.jpg");
		equip_display->setAnchorPoint(Point(0.5, 0.5));
		equip_display->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, visibleSize.height *0.5 + origin.y));
		equip_display->setVisible(false);
		addChild(equip_display, 1);

		// first equip and its callback function
		MenuItemSprite* equip1;
		MenuItemLabel* equip1_label;
		std::string equip_name1 = "redshoe.png";
		Attribute attribute1 = { MELEE,0,0,0,0,0,20,0,0,0,0,0,0,0,40 };
		std::string str_buff1 = "Red Shoe\n$1000\nadd attack\nadd speed";
		int money1 = 1000, set_width1 = 1;
		MENU_AND_LABEL(equip_name1, equip1, attribute1, money1, set_width1, str_buff1, equip1_label);

		// second equip and its callback function 
		MenuItemSprite* equip2;
		MenuItemLabel* equip2_label;
		std::string equip_name2 = "blueshoe.png";
		Attribute attribute2 = { MELEE,0,0,0,0,0,0,0,20,0,0,0,0,0,40 };
		std::string str_buff2 = "Blue Shoe\n$1000\nadd magic\nadd speed";
		int money2 = 1000, set_width2 = 2;
		MENU_AND_LABEL(equip_name2, equip2, attribute2, money2, set_width2, str_buff2, equip2_label);

		// third equip and its callback function 
		MenuItemSprite* equip3;
		MenuItemLabel* equip3_label;
		std::string equip_name3 = "greenshoe.png";
		Attribute attribute3 = { MELEE,0,0,0,0,0,0,20,0,20,0,0,0,0,40 };
		std::string str_buff3 = "Green Shoe\n$1000\nadd defend\nadd speed";
		int money3 = 1000, set_width3 = 3;
		MENU_AND_LABEL(equip_name3, equip3, attribute3, money3, set_width3, str_buff3, equip3_label);

		// 4th equip and its callback function 
		MenuItemSprite* equip4;
		MenuItemLabel* equip4_label;
		std::string equip_name4 = "littlemagic.png";
		Attribute attribute4 = { MELEE,0,0,0,0,0,0,0,50,0,0,0,0,0,0 };
		std::string str_buff4 = "Little Magic\n$1000\nadd magic";
		int money4 = 1000, set_width4 = 4;
		MENU_AND_LABEL(equip_name4, equip4, attribute4, money4, set_width4, str_buff4, equip4_label);

		// 5th equip and its callback function 
		MenuItemSprite* equip5;
		MenuItemLabel* equip5_label;
		std::string equip_name5 = "bigmagic.png";
		Attribute attribute5 = { MELEE,0,0,0,0,0,0,0,100,0,0,0,0,0,0 };
		std::string str_buff5 = "Big Magic\n$1500\nadd magic";
		int money5 = 1500, set_width5 = 5;
		MENU_AND_LABEL(equip_name5, equip5, attribute5, money5, set_width5, str_buff5, equip5_label);

		// 6th equip and its callback function 
		MenuItemSprite* equip6;
		MenuItemLabel* equip6_label;
		std::string equip_name6 = "littleattack.png";
		Attribute attribute6 = { MELEE,0,0,0,0,0,50,0,0,0,0,0,0,0,0 };
		std::string str_buff6 = "Little Attack\n$1000\nadd attack";
		int money6 = 1000, set_width6 = 6;
		MENU_AND_LABEL(equip_name6, equip6, attribute6, money6, set_width6, str_buff6, equip6_label);

		// 7th equip and its callback function 
		MenuItemSprite* equip7;
		MenuItemLabel* equip7_label;
		std::string equip_name7 = "bigattack.png";
		Attribute attribute7 = { MELEE,0,0,0,0,0,100,0,0,0,0,0,0,0,0 };
		std::string str_buff7 = "Big Attack\n$1500\nadd attack";
		int money7 = 1500, set_width7 = 7;
		MENU_AND_LABEL(equip_name7, equip7, attribute7, money7, set_width7, str_buff7, equip7_label);

		// 8th equip and its callback function 
		MenuItemSprite* equip8;
		MenuItemLabel* equip8_label;
		std::string equip_name8 = "bigattackdefend.png";
		Attribute attribute8 = { MELEE,0,0,0,0,0,0,40,0,0,0,0,0,0,0 };
		std::string str_buff8 = "Attack Defend\n$1500\nadd defend";
		int money8 = 1500, set_width8 = 8;
		MENU_AND_LABEL(equip_name8, equip8, attribute8, money8, set_width8, str_buff8, equip8_label);

		// 9th equip and its callback function 
		MenuItemSprite* equip9;
		MenuItemLabel* equip9_label;
		std::string equip_name9 = "bigmagicdefend.png";
		Attribute attribute9 = { MELEE,0,0,0,0,0,0,0,0,40,0,0,0,0,0 };
		std::string str_buff9 = "Magic Defend\n$1500\nadd defend";
		int money9 = 1500, set_width9 = 9;
		MENU_AND_LABEL(equip_name9, equip9, attribute9, money9, set_width9, str_buff9, equip9_label);

		//create label to back to maplayer with its callback function
		auto label_back = Label::createWithSystemFont("Back To Playing", "Thonburi", 40);
		label_back->setColor(Color3B(0, 0, 0));
		auto menu_label_back = MenuItemLabel::create(label_back,
			[this](Ref* sender) {
			equip_display->setVisible(false);
			equip_display_Menu->setVisible(false);
			equip_display_label->setVisible(false);
		});
		menu_label_back->setAnchorPoint(Point(0.5, 0.5));
		menu_label_back->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, visibleSize.height *0.6 + origin.y));

		//create menu of equips
		equip_display_Menu = Menu::create(equip1, equip2, equip3, equip4, equip5, equip6, equip7, equip8, equip9, NULL);
		equip_display_Menu->setPosition(Point::ZERO);
		equip_display_Menu->setVisible(false);
		addChild(equip_display_Menu, 2);

		//create menu of equips label
		equip_display_label = Menu::create(menu_label_back, equip1_label, equip2_label, equip3_label, equip4_label, equip5_label, equip6_label, equip7_label, equip8_label, equip9_label, NULL);
		equip_display_label->setPosition(Point::ZERO);
		equip_display_label->setVisible(false);
		addChild(equip_display_label, 2);
	}

	//create botton of equip and the callback function to visible equip display
	{
		auto EQUIP_button1 = Sprite::create("EquipLable.png");
		auto EQUIP_button2 = Sprite::create("EquipLable.png");
		auto EQUIP_button = MenuItemSprite::create(
			EQUIP_button1,
			EQUIP_button2,
			[this](Ref* sender) {
			// callback
			equip_display->setVisible(true);
			equip_display_Menu->setVisible(true);
			equip_display_label->setVisible(true);
		});
		EQUIP_button->setAnchorPoint(Point(0, 0));
		EQUIP_button->setPosition(Vec2(visibleSize.width * 0 + origin.x, visibleSize.height *0.88 + origin.y));

		Menu* equip_Menu = Menu::create(EQUIP_button, NULL);
		equip_Menu->setPosition(Point::ZERO);
		this->addChild(equip_Menu, 1);
	}

	//create level label
	{
		Scene * now_scene = Director::sharedDirector()->getRunningScene();
		auto level_label = black_system_label(std::to_string(now_scene->hero_player->GetLevel()), 40);
		level_label->setVisible(false);
		addChild(level_label, 2);
	}

	//create botton of board and the callback function to visible board display
	{
		auto BOARD_button1 = Sprite::create("EquipLable.png");
		auto BOARD_button2 = Sprite::create("EquipLable.png");
		auto BOARD_button = MenuItemSprite::create(
			BOARD_button1,
			BOARD_button2,
			[this](Ref* sender) {
			equip_display->setVisible(true);
			level_label->setVisible(true);
		});
		BOARD_button->setAnchorPoint(Point(0, 0));
		BOARD_button->setPosition(Vec2(visibleSize.width * 0 + origin.x, visibleSize.height *0.75 + origin.y));

		Menu* board_Menu = Menu::create(BOARD_button, NULL);
		board_Menu->setPosition(Point::ZERO);
		this->addChild(board_Menu, 1);
	}

	//create label of board ,for exemple " Equip " and " 1 : 1 "
	{
		auto equip_label = Label::createWithSystemFont("Equip", "Arial", 40);
		equip_label->enableOutline(Color4B::WHITE, 1);
		equip_label->setAnchorPoint(Point(0, 0));
		equip_label->setPosition(Vec2(visibleSize.width *0.12 + origin.x, visibleSize.height *0.91 + origin.y));
		this->addChild(equip_label, 2);

		auto board_label = Label::createWithSystemFont(string_death_number_enemy_hero, "Arial", 40);
		board_label->enableOutline(Color4B::WHITE, 1);
		board_label->setAnchorPoint(Point(0, 0));
		board_label->setPosition(Vec2(visibleSize.width *0.12 + origin.x, visibleSize.height *0.785 + origin.y));
		this->addChild(board_label, 2);

		auto board_labe2 = Label::createWithSystemFont(":", "Arial", 40);
		board_labe2->enableOutline(Color4B::WHITE, 1);
		board_labe2->setAnchorPoint(Point(0, 0));
		board_labe2->setPosition(Vec2(visibleSize.width *0.16 + origin.x, visibleSize.height *0.785 + origin.y));
		this->addChild(board_labe2, 2);

		auto board_labe3 = Label::createWithSystemFont(string_death_number_enemy_hero, "Arial", 40);
		board_labe3->enableOutline(Color4B::WHITE, 1);
		board_labe3->setAnchorPoint(Point(0, 0));
		board_labe3->setPosition(Vec2(visibleSize.width *0.19 + origin.x, visibleSize.height *0.785 + origin.y));
		this->addChild(board_labe3, 2);
	}

	//create pause menu
	{
		MenuItemImage *pCloseItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", this,
			menu_selector(MapLayer::menuPauseCallback));

		pCloseItem->setPosition(Vec2(visibleSize.width *0.96 + origin.x, visibleSize.height *0.05 + origin.y));

		Menu* pMenu = Menu::create(pCloseItem, NULL);
		pMenu->setPosition(Point::ZERO);
		this->addChild(pMenu, 1);
	}

	{
		SkillButton* mSkillButton = SkillButton::createSkillButton(2.f, "stencil.png", "normal.png", "Click.png");
		mSkillButton->setPosition(ccp(visibleSize.width - 150, 60));
		addChild(mSkillButton, 2);
		SkillButton* mSkillButton2 = SkillButton::createSkillButton(2.f, "stencil.png", "normal2.png", "Click2.png");
		mSkillButton2->setPosition(ccp(visibleSize.width - 350, 60));
		addChild(mSkillButton2, 2);
		SkillButton* mSkillButton3 = SkillButton::createSkillButton(2.f, "stencil.png", "normal3.png", "Click3.png");
		mSkillButton3->setPosition(ccp(visibleSize.width - 250, 60));
		addChild(mSkillButton3, 2);
	}

	return true;
}