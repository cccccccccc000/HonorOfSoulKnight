
#ifndef __Player__
#define __Player__
#include "cocos2d.h"
#include "Progress.h"

USING_NS_CC;

class Player : public Sprite
{
public:
    enum PlayerType
    {
        HERO,
        ENEMY
    };
    bool initWithPlayerType(PlayerType type);
    static Player* create(PlayerType type);
    void addAnimation();
    void playAnimationForever(std::string animationName);
    void playAnimation(std::string animationName);
    void walkTo(Vec2 dest);
    Sequence* getSeq() { return _seq; }
    void getHit();
    void autoDoAction(Player* hero);
    void autoAttack(Player* hero);
    Progress* getProgress() { return _progress; }
private:
    PlayerType _type;
    std::string _name;
    int _animationNum = 5;
    float _speed;
    std::vector<int> _animationFrameNums;
    std::vector<std::string> _animationNames;
    Sequence* _seq;
    Progress* _progress;
	bool _isShowBar;
};

#endif
