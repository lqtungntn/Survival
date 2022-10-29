#ifndef __SHOP_SCENE_H__
#define __SHOP_SCENE_H__

#include "cocos2d.h"
#include "CommonFunc.h"

class ShopScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(ShopScene);

    Player* m_player;

    Bullet* m_bullet;

    Mine* m_mine;

    Trap* m_trap;

    Label* Attribute[7], *Gold[7], *PlayerGold;
private:

    void GoToGameScene(cocos2d::Ref* sender);

    void UpdateHearth(cocos2d::Ref* sender);

    void UpdateAtkSpeed(cocos2d::Ref* sender);

    void UpdateDefense(cocos2d::Ref* sender);

    void UpdateAttack(cocos2d::Ref* sender);

    void UpdateSpeed(cocos2d::Ref* sender);

    void UpdateRegen(cocos2d::Ref* sender);

    void UpdateBomb(cocos2d::Ref* sender);
};

#endif // __SHOP_SCENE_H__
