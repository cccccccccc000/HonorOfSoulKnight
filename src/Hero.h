#ifndef HERO_H
#define HERO_H
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class Hero:public cocos2d::CCNode
{
public:
	Hero(void);
	~Hero(void);
	//根据图片名创建英雄
	void InitHeroSprite(char *hero_name);
	//设置动画，num为图片数目，run_direction为精灵脸朝向，false朝右
	//name_each为name_png中每一小张图片名称公共的部分
	void SetAnimation(const char *name_plist, const char *name_png,const unsigned int num, bool run_dirction);
	//停止动画
	void StopAnimation();
	//判断是否在跑动画
	bool IsRunning;
	//英雄运动的方向
	bool HeroDirection;
	CREATE_FUNC(Hero);

private:
	CCSprite* m_HeroSprite;//精灵
	char *Hero_name;//用来保存初始状态的精灵图片名称
};
#endif //HERO_H
