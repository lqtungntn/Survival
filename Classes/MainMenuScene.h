#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(MainMenuScene);
private:
    void GoToGameScene(cocos2d::Ref* sender);

    void GoToOptionScene(cocos2d::Ref* sender);

    void ExitGame(cocos2d::Ref* sender);
};

#endif // __MAIN_MENU_SCENE_H__
