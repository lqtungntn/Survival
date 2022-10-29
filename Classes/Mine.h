#ifndef __MINE_H__
#define __MINE_H__

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Mine : public cocos2d::Node
{
public: 
    Mine(cocos2d::Scene* scene, int tag);

    void SetPosition(Vec2 pos);

    void SetVisible(bool visible);

    int Damage;
private:
    cocos2d::Sprite* m_Mine;

    cocos2d::Size winSize, visibleSize;

    cocos2d::Vec2 origin;
};

#endif // __MINE_H__
