#ifndef __TREASURE_H__
#define __TREASURE_H__

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Treasure : public cocos2d::Node
{
public: 
    Treasure(cocos2d::Scene* scene);

    void Roll();

    void RanPos();

    int Item();

    Vec2 GetDirection();

    void SetPosition(Vec2 pos);

    void SetVisible(bool visible);

    cocos2d::Sprite* m_player;
private:
    cocos2d::Sprite* m_Treasure;

    cocos2d::Size winSize, visibleSize;

    cocos2d::Vec2 origin;

    int num;
};

#endif // __TREASURE_H__
