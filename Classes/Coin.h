#ifndef __Coin_H__
#define __Coin_H__

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Coin : public cocos2d::Node
{
public: 
    Coin(cocos2d::Scene* scene, int tag);

    Vec2 GetDirection();

    void SetPosition(Vec2 pos);

    void SetVisible(bool visible);

    bool IsVisible();

    cocos2d::Sprite* m_player;

    int gold = 0;
private:
    cocos2d::Sprite* m_Coin;

    cocos2d::Size winSize, visibleSize;

    cocos2d::Vec2 origin;
};

#endif // __Coin_H__
