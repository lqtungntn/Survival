#ifndef __MusicBox_H__
#define __MusicBox_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "CommonFunc.h"

USING_NS_CC;

class MusicBox : public cocos2d::Node
{
public: 
    MusicBox(cocos2d::Scene* scene);

    Vec2 GetDirection();

    void SetPosition(Vec2 pos);

    void SetVisible(bool visible);

    bool IsVisible();

    void RanPos();

    void PlayerPos(Vec2 pos);

    int gold = 0;

    int AudioID;
private:
    cocos2d::Sprite* m_MusicBox;

    cocos2d::Size winSize, visibleSize;

    cocos2d::Vec2 origin, PPos;

    
};

#endif // __MusicBox_H__
