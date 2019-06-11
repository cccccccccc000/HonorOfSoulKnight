#include "Hero.h"  
USING_NS_CC;
USING_NS_CC_EXT;
Hero::Hero(void)
{
	IsRunning = false;//没在放动画  
	HeroDirection = false;//向右运动  
	Hero_name = NULL;
}

Hero::~Hero(void)
{

}
void Hero::InitHeroSprite(char *hero_name)
{
	Hero_name = hero_name;
	this->m_HeroSprite = CCSprite::create(hero_name);
	this->addChild(m_HeroSprite);
}
//动画播放，可以是跑、攻击、死亡、受伤等  
void Hero::SetAnimation(const char *name_plist, const char *name_png,unsigned int num, bool run_directon)
{
	if (HeroDirection != run_directon)
	{
		HeroDirection = run_directon;
		m_HeroSprite->setFlipX(run_directon);
	}
	if (IsRunning)
		return;
	//将图片加载到精灵帧缓存池  
	CCSpriteFrameCache *m_frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	m_frameCache->addSpriteFramesWithFile(name_plist, name_png);
	CCAnimation* animation = CCAnimation::create();
	char nameBuf[100];
	for (int i = 0; i < num; i++)
	{
		memset(nameBuf, 0, sizeof(nameBuf));
		sprintf(nameBuf, "%d.png", i);
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(nameBuf));
    }
	if (HeroDirection != run_directon)
	{
		HeroDirection = run_directon;

	}
	animation->setLoops(-1);//表示无限循环播放  
	animation->setDelayPerUnit(0.1f);//每两张图片的时间隔，图片数目越少，间隔最小就越小  

	 //将动画包装成一个动作  
	CCAnimate* act = CCAnimate::create(animation);


	m_HeroSprite->runAction(act);
	IsRunning = true;

}
void Hero::StopAnimation()
{
	if (!IsRunning)
		return;
	m_HeroSprite->stopAllActions();//当前精灵停止所有动画  

	//恢复精灵原来的初始化贴图   
	this->removeChild(m_HeroSprite, TRUE);//把原来的精灵删除掉  
	m_HeroSprite = CCSprite::create(Hero_name);//恢复精灵原来的贴图样子  
	m_HeroSprite->setFlipX(HeroDirection);
	this->addChild(m_HeroSprite);
	IsRunning = false;
	IsRunning = false;
}
