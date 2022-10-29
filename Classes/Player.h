#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Player : public cocos2d::Node
{
public: 
    Player(cocos2d::Scene* scene);

    void Moving();

    Vec2 GetDirection();

    Vec2 Direction;

    int Hearth, Atk, Def, CoolDownBomb, CoolDownTrap, Gold, CurrHearth, Regen = 1;

    int ValueG[7];

    float Speed;
private:
    cocos2d::Sprite* m_character;

    cocos2d::Size winSize, visibleSize;

    cocos2d::Vec2 origin;
};

#endif // __PLAYER_H__
