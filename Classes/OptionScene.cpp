#include "OptionScene.h"

USING_NS_CC;

Scene* OptionScene::createScene()
{
    auto scene = Scene::create();

    auto layer = OptionScene::create();

    scene->addChild(layer);

    return scene;
}

bool OptionScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    return true;
}
