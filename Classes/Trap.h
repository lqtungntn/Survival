#ifndef __TRAP_H__
#define __TRAP_H__

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Trap : public cocos2d::Node
{
public: 
    Trap(cocos2d::Scene* scene, int tag);

    void SetPosition(Vec2 pos);

    void SetVisible(bool visible);

    int Damage;
private:
    cocos2d::Sprite* m_Trap;

    cocos2d::Size winSize, visibleSize;

    cocos2d::Vec2 origin;
};

#endif // __TRAP_H__
