#include "GameOverScene.h"
#include "Definitions.h"
#include "GameScene.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
    auto scene = Scene::create();

    auto layer = GameOverScene::create();

    Director::getInstance()->setAnimationInterval(1.0f / 30);

    scene->addChild(layer);

    return scene;
}

bool GameOverScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto winSize = Director::getInstance()->getWinSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Draw Logo
    auto logoSprite = Sprite::create("res\\SplashScene\\SurvivalLogo.png");
    logoSprite->setPosition(Point(winSize.width / 2, winSize.height / 5 * 4));
    logoSprite->setScale(0.5, 0.5);
    this->addChild(logoSprite, 1);

    // Draw Attribute
    std::string str;
    if (Global_Is_Win) {
        str = "YOU WIN";
    }
    else {
        str = "YOU LOSE";
    }
    auto state = Label::createWithTTF(StringUtils::format(str.c_str()), "fonts/arial.ttf", visibleSize.height * 0.1f);
    state->setColor(Color3B::RED);
    state->setPosition(Point(winSize.width / 2, winSize.height / 5 * 3));
    this->addChild(state);

    // Draw Play Button
    auto playItem = MenuItemImage::create("res\\GameScene\\TryButton.png", "res\\GameScene\\TryButtonClicked.png", CC_CALLBACK_1(GameOverScene::GoToGameScene, this));
    playItem->setPosition(Point(winSize.width / 2, winSize.height / 5 * 2));

    // Draw Menu
    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu);
    return true;
}

void GameOverScene::GoToGameScene(cocos2d::Ref* sender) {
    auto scene = GameScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void GameOverScene::onEnter() {
    AudioEngine::pauseAll();
}