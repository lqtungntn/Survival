#include "SplashScene.h"
#include "Definitions.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    auto scene = Scene::create();

    auto layer = SplashScene::create();

    Director::getInstance()->setAnimationInterval(1.0f / 30);

    scene->addChild(layer);

    return scene;
}

bool SplashScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->scheduleOnce(CC_SCHEDULE_SELECTOR(SplashScene::GoToMainMenuScene), DISPLAY_TIME_SPLASH_SCEEN);
    auto backgroundSprite = Sprite::create("res\\SplashScene\\SurvivalLogo.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(backgroundSprite);

    return true;
}

void SplashScene::GoToMainMenuScene(float dt) {
    auto scene = MainMenuScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}