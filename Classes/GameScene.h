#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Monster.h"
#include "Bullet.h"
#include "Trap.h"
#include "Mine.h"
#include "ShopScene.h"
#include <vector>
#include "ui/CocosGUI.h"
#include "Treasure.h"
#include "Coin.h"
#include "Boss.h"
#include "MusicBox.h"

USING_NS_CC;
using namespace std;

class GameScene : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();

    void update(float dt);

    void FireBullet(float dt);

    void ResetBullet(float dt);

    void SpawnMonster(float dt);

    void UpdateMonster(float dt);

    void MovingMonster(float dt);

    void MonsterDeath(int idx);

    void TakeCoin(int idx);

    void UIFollowPlayer();

    CREATE_FUNC(GameScene);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* evt);

    void onKeyRelease(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* evt);

    ~GameScene();
private:
    Node* Canvas = new Node();
    cocos2d::ui::LoadingBar* HeartBar, * BGHeartBar, *BossHeartBar, * BGBossHeartBar;
    Label* m_playerGold, *m_goldArr[COIN_LIMIT + 2];

    int m_GAC[COIN_LIMIT + 2];

    cocos2d::Sprite* m_playerLight;
    Player* m_player;
    Boss* m_boss;
    MusicBox* m_musicBox;

    vector<Monster*> m_mons;
    vector<bool> m_monsVisible;
    vector<int> m_monsAtk;

    vector<Coin*> m_coin;

    vector<Mine*> m_mine;
    vector<bool> m_mineVisible;
    int mineCount = 0;

    vector<Trap*> m_trap;
    vector<bool> m_trapVisible;
    int trapCount = 0, BossCount = 0;
    
    Bullet* m_bullet;
    bool m_ResetBullet = true;

    int delay = 0, nearPlayer = 0, FrameCount = 0;

    Camera* cam;

    Size winSize;

    Treasure* m_treasure;

    // Audio
    int BulletS, coinS, MonsterAtkS, MonsterDeadS, MusicBoxS, BGS;
};

#endif // __GAME_SCENE_H__
