#ifndef __Boss_H__
#define __Boss_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "CommonFunc.h"

USING_NS_CC;

class Boss : public cocos2d::Node
{
public: 
    Boss(cocos2d::Scene* scene);

    void Moving(Vec2 pos);

    Vec2 GetDirection();

    void SetPosition(Vec2 pos);

    void SetVisible(bool visible);

    float Speed, Hearth = 100;

    cocos2d::Sprite* m_player;
private:
    cocos2d::Sprite* m_Boss;

    cocos2d::Size winSize, visibleSize;

    cocos2d::Vec2 origin;
};

#endif // __Boss_H__
