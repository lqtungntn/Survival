#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Bullet : public cocos2d::Node
{
public: 
    Bullet(cocos2d::Scene* scene);

    void Moving();

    void CalDir(Vec2 pos);

    void SetPosition(Vec2 pos);

    void SetVisible(bool visible);

    Vec2 Speed;

    int AtkSpeed = 100;

    bool NeedReset = false;

    cocos2d::Sprite* m_player;
private:
    cocos2d::Sprite* m_Bullet;

    cocos2d::Size winSize, visibleSize;

    cocos2d::Vec2 origin;
};

#endif // __BULLET_H__
