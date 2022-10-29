#include "MainMenuScene.h"
#include "GameScene.h"
#include "OptionScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    auto scene = Scene::create();

    auto layer = MainMenuScene::create();

    scene->addChild(layer);

    return scene;
}

bool MainMenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    // Get Scene Value
    auto winSize = Director::getInstance()->getWinSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Draw BackGround
    auto backgroundSprite = Sprite::create("res\\MainMenuScene\\background.jpg");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    backgroundSprite->setScale(winSize.width / backgroundSprite->getContentSize().width, winSize.height / backgroundSprite->getContentSize().height);
    this->addChild(backgroundSprite, 0);

    // Draw Logo
    auto logoSprite = Sprite::create("res\\SplashScene\\SurvivalLogo.png");
    logoSprite->setPosition(Point(winSize.width / 2, winSize.height / 5 * 4));
    logoSprite->setScale(0.5, 0.5);
    this->addChild(logoSprite, 1);

    // Draw Play Button
    auto playItem = MenuItemImage::create("res\\MainMenuScene\\PlayButton.png", "res\\MainMenuScene\\PlayButtonClicked.png", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
    playItem->setPosition(Point(winSize.width / 2, winSize.height / 5 * 3));
    
    // Draw Option Button
    auto optionItem = MenuItemImage::create("res\\MainMenuScene\\OptionButton.png", "res\\MainMenuScene\\OptionButtonClicked.png", CC_CALLBACK_1(MainMenuScene::GoToOptionScene, this));
    optionItem->setPosition(Point(winSize.width / 2, winSize.height / 5 * 2));

    // Draw Exit Button
    auto exitItem = MenuItemImage::create("res\\MainMenuScene\\ExitButton.png", "res\\MainMenuScene\\ExitButtonClicked.png", CC_CALLBACK_1(MainMenuScene::ExitGame, this));
    exitItem->setPosition(Point(winSize.width / 2, winSize.height / 5 * 1));

    // Draw Menu
    auto menu = Menu::create(playItem, optionItem, exitItem, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu);
    return true;
}

void MainMenuScene::GoToGameScene(cocos2d::Ref* sender) {
    auto scene = GameScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MainMenuScene::GoToOptionScene(cocos2d::Ref* sender) {
    auto scene = OptionScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MainMenuScene::ExitGame(cocos2d::Ref* sender) {
    Director::getInstance()->end();
}