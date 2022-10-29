#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "CommonFunc.h"

USING_NS_CC;

class Monster : public cocos2d::Node
{
public: 
    Monster(cocos2d::Scene* scene, int tag);

    void Moving(Vec2 pos);

    Vec2 GetDirection();

    void SetPosition(Vec2 pos);

    void SetVisible(bool visible);

    int Hearth, Atk, Def, SlowCount = 0, Gold;

    float AtkSpeed, Speed, Slow = 1.0f;

    cocos2d::Sprite* m_player;
private:
    cocos2d::Sprite* m_monster;

    cocos2d::Size winSize, visibleSize;

    cocos2d::Vec2 origin;
};

#endif // __MONSTER_H__
