
#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include<iterator>
#include "Layer.h"

USING_NS_CC;

class PlayingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    static cocos2d::Scene* createSceneWithHero(Species species);

   virtual bool init();
   
	CREATE_FUNC(PlayingScene);

    void IncreaseTime();

    void BuffTimerOn();

    void BulletTimerOn();

    void SelectTargetForD();

    void SelectTargetForR();

    void SelectTarget();

    void AiAttack();

    inline int GetTimeSecond() {return this->current_time_second_;}

    inline int GetTimeMinute() {return this->current_time_second_/60;}
    //members
    Hero* hero_player_;

    Hero* hero_enemy_;
 
    Attacker* r_tower_;
    Attacker* r_ancient_;
    Attacker* r_fountain_;

    Attacker* d_tower_;
    Attacker* d_ancient_;
    Attacker* d_fountain_;

    std::vector<Creeps*> r_creeps_;
    std::vector<Creeps*> d_creeps_;

    std::map<Bullet*,cocos2d::MoveTo*> bullet_seq;
	
private:
	int current_time_second_=0;
    
    bool timer_pause_;



};
#endif // __PLAY_SCENE_H__
