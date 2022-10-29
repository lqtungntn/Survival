#include "ShopScene.h"
#include "Definitions.h"
#include "MainMenuScene.h"
#include <string>

USING_NS_CC;

Scene* ShopScene::createScene()
{
    auto scene = Scene::create();

    auto layer = ShopScene::create();

    Director::getInstance()->setAnimationInterval(1.0f / 30);

    scene->addChild(layer);

    return scene;
}

bool ShopScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto winSize = Director::getInstance()->getWinSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->m_player = Global_Player;
    this->m_bullet = Global_Bullet;
    
    // Draw Attack
    auto AtkLogo = MenuItemImage::create("res\\GameScene\\Attack.png", "res\\GameScene\\Attack.png", CC_CALLBACK_1(ShopScene::UpdateAttack, this));
    AtkLogo->setPosition(Point(winSize.width / 9, winSize.height / 9 * 8));

    // Draw Attribute
    Attribute[0] = Label::createWithTTF(StringUtils::format(std::to_string(this->m_player->Atk).c_str()), "fonts/arial.ttf", visibleSize.height * 0.1f);
    Attribute[0]->setColor(Color3B::RED);
    Attribute[0]->setPosition(Point(winSize.width / 9 * 3, winSize.height / 9 * 8));
    this->addChild(Attribute[0]);

    // Draw Gold
    Gold[0] = Label::createWithTTF(StringUtils::format(std::to_string(this->m_player->ValueG[0]).c_str()), "fonts/arial.ttf", visibleSize.height * 0.1f);
    Gold[0]->setColor(Color3B::YELLOW);
    Gold[0]->setPosition(Point(winSize.width / 9 * 5, winSize.height / 9 * 8));
    this->addChild(Gold[0]);

    // Draw Defense
    auto DefLogo = MenuItemImage::create("res\\GameScene\\Defense.png", "res\\GameScene\\Defense.png", CC_CALLBACK_1(ShopScene::UpdateDefense, this));
    DefLogo->setPosition(Point(winSize.width / 9, winSize.height / 9 * 7));

    // Draw Attribute
    Attribute[1] = Label::createWithTTF(StringUtils::format(std::to_string(this->m_player->Def).c_str()), "fonts/arial.ttf", visibleSize.height * 0.1f);
    Attribute[1]->setColor(Color3B::RED);
    Attribute[1]->setPosition(Point(winSize.width / 9 * 3, winSize.height / 9 * 7));
    this->addChild(Attribute[1]);

    // Draw Gold
    Gold[1] = Label::createWithTTF(StringUtils::format(std::to_string(this->m_player->ValueG[1]).c_str()), "fonts/arial.ttf", visibleSize.height * 0.1f);
    Gold[1]->setColor(Color3B::YELLOW);
    Gold[1]->setPosition(Point(winSize.width / 9 * 5, winSize.height / 9 * 7));
    this->addChild(Gold[1]);

    // Draw Hearth
    auto HeathLogo = MenuItemImage::create("res\\GameScene\\Hearth.png", "res\\GameScene\\Hearth.png", CC_CALLBACK_1(ShopScene::UpdateHearth, this));
    HeathLogo->setPosition(Point(winSize.width / 9, winSize.height / 9 * 6));

    // Draw Attribute
    Attribute[2] = Label::createWithTTF(StringUtils::format(std::to_string(this->m_player->Hearth).c_str()), "fonts/arial.ttf", visibleSize.height * 0.1f);
    Attribute[2]->setColor(Color3B::RED);
    Attribute[2]->setPosition(Point(winSize.width / 9 * 3, winSize.height / 9 * 6));
    this->addChild(Attribute[2]);

    // Draw Gold
    Gold[2] = Label::createWithTTF(StringUtils::format(std::to_string(this->m_player->ValueG[2]).c_str()), "fonts/arial.ttf", visibleSize.height * 0.1f);
    Gold[2]->setColor(Color3B::YELLOW);
    Gold[2]->setPosition(Point(winSize.width / 9 * 5, winSize.height / 9 * 6));
    this->addChild(Gold[2]);

    // Draw Attack Speed
    auto AtkSpeedLogo = MenuItemImage::create("res\\GameScene\\AtkSpeed.png", "res\\GameScene\\AtkSpeed.png", CC_CALLBACK_1(ShopScene::UpdateAtkSpeed, this));
    AtkSpeedLogo->setPosition(Point(winSize.width / 9, winSize.height / 9 * 5));

    // Draw Attribute
    Attribute[3] = Label::createWithTTF(StringUtils::format(std::to_string(this->m_bullet->AtkSpeed).c_str()), "fonts/arial.ttf", visibleSize.height * 0.1f);
    Attribute[3]->setColor(Color3B::RED);
    Attribute[3]->setPosition(Point(winSize.width / 9 * 3, winSize.height / 9 * 5));
    this->addChild(Attribute[3]);

    // Draw Gold
    Gold[3] = Label::createWithTTF(StringUtils::format(std::to_string(this->m_player->ValueG[3]).c_str()), "fonts/arial.ttf", visibleSize.height * 0.1f);
    Gold[3]->setColor(Color3B::YELLOW);
    Gold[3]->setPosition(Point(winSize.width / 9 * 5, winSize.height / 9 * 5));
    this->addChild(Gold[3]);

    // Draw Speed
    auto SpeedLogo = MenuItemImage::create("res\\GameScene\\Speed.png", "res\\GameScene\\Speed.png", CC_CALLBACK_1(ShopScene::UpdateSpeed, this));
    SpeedLogo->setPosition(Point(winSize.width / 9, winSize.height / 9 * 4));

    // Draw Attribute
    Attribute[4] = Label::createWithTTF(StringUtils::format("%.1f", this->m_player->Speed), "fonts/arial.ttf", visibleSize.height * 0.1f);
    Attribute[4]->setColor(Color3B::RED);
    Attribute[4]->setPosition(Point(winSize.width / 9 * 3, winSize.height / 9 * 4));
    this->addChild(Attribute[4]);

    // Draw Gold
    Gold[4] = Label::createWithTTF(StringUtils::format(std::to_string(this->m_player->ValueG[4]).c_str()), "fonts/arial.ttf", visibleSize.height * 0.1f);
    Gold[4]->setColor(Color3B::YELLOW);
    Gold[4]->setPosition(Point(winSize.width / 9 * 5, winSize.height / 9 * 4));
    this->addChild(Gold[4]);

    // Draw Regen
    auto RegenLogo = MenuItemImage::create("res\\GameScene\\Regen.png", "res\\GameScene\\Regen.png", CC_CALLBACK_1(ShopScene::UpdateRegen, this));
    RegenLogo->setPosition(Point(winSize.width / 9, winSize.height / 9 * 3));

    // Draw Attribute
    Attribute[5] = Label::createWithTTF(StringUtils::format("%.1f", this->m_player->Regen), "fonts/arial.ttf", visibleSize.height * 0.1f);
    Attribute[5]->setColor(Color3B::RED);
    Attribute[5]->setPosition(Point(winSize.width / 9 * 3, winSize.height / 9 * 3));
    this->addChild(Attribute[5]);

    // Draw Gold
    Gold[5] = Label::createWithTTF(StringUtils::format(std::to_string(this->m_player->ValueG[5]).c_str()), "fonts/arial.ttf", visibleSize.height * 0.1f);
    Gold[5]->setColor(Color3B::YELLOW);
    Gold[5]->setPosition(Point(winSize.width / 9 * 5, winSize.height / 9 * 3));
    this->addChild(Gold[5]);

    // Draw Bomb
    auto BombLogo = MenuItemImage::create("res\\GameScene\\Bomb.png", "res\\GameScene\\Bomb.png", CC_CALLBACK_1(ShopScene::UpdateBomb, this));
    BombLogo->setPosition(Point(winSize.width / 9, winSize.height / 9 * 2));

    // Draw Attribute
    Attribute[6] = Label::createWithTTF(StringUtils::format("%.1f", this->m_player->Regen), "fonts/arial.ttf", visibleSize.height * 0.1f);
    Attribute[6]->setColor(Color3B::RED);
    Attribute[6]->setPosition(Point(winSize.width / 9 * 3, winSize.height / 9 * 2));
    this->addChild(Attribute[6]);

    // Draw Gold
    Gold[6] = Label::createWithTTF(StringUtils::format(std::to_string(this->m_player->ValueG[6]).c_str()), "fonts/arial.ttf", visibleSize.height * 0.1f);
    Gold[6]->setColor(Color3B::YELLOW);
    Gold[6]->setPosition(Point(winSize.width / 9 * 5, winSize.height / 9 * 2));
    this->addChild(Gold[6]);

    // Draw Exit
    auto ExitLogo = MenuItemImage::create("res\\MainMenuScene\\ExitButton.png", "res\\MainMenuScene\\ExitButtonClicked.png", CC_CALLBACK_1(ShopScene::GoToGameScene, this));
    ExitLogo->setPosition(Point(winSize.width / 9, winSize.height / 9 * 1));

    // Draw Player Gold
    PlayerGold = Label::createWithTTF(StringUtils::format(std::to_string(this->m_player->Gold).c_str()), "fonts/arial.ttf", visibleSize.height * 0.1f);
    PlayerGold->setColor(Color3B::YELLOW);
    PlayerGold->setPosition(Point(winSize.width / 9 * 5, winSize.height / 9 * 1));
    this->addChild(PlayerGold);

    // Draw Menu
    auto menu = Menu::create(AtkLogo, DefLogo, HeathLogo, AtkSpeedLogo, SpeedLogo, RegenLogo, ExitLogo, BombLogo, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu);

    return true;
}

void ShopScene::GoToGameScene(cocos2d::Ref* sender) {
    Director::getInstance()->resume();
    Director::getInstance()->popScene();
}

void ShopScene::UpdateHearth(cocos2d::Ref* sender) {
    if (m_player->Gold >= this->m_player->ValueG[2]) {
        this->m_player->Hearth += 25;
        this->m_player->CurrHearth += 25;
        Attribute[2]->setString(std::to_string(this->m_player->Atk).c_str());
        m_player->Gold -= this->m_player->ValueG[2];
        PlayerGold->setString(std::to_string(this->m_player->Gold).c_str());
        this->m_player->ValueG[2] += 25;
        Gold[2]->setString(std::to_string(this->m_player->ValueG[2]).c_str());
    }
}

void ShopScene::UpdateAtkSpeed(cocos2d::Ref* sender) {
    if (m_player->Gold >= this->m_player->ValueG[3]) {
        if (this->m_bullet->AtkSpeed > 4) {
            this->m_bullet->AtkSpeed -= 4;
            Attribute[3]->setString(std::to_string(this->m_player->Atk).c_str());
            m_player->Gold -= this->m_player->ValueG[3];
            PlayerGold->setString(std::to_string(this->m_player->Gold).c_str());
            this->m_player->ValueG[3] += 25;
            Gold[3]->setString(std::to_string(this->m_player->ValueG[3]).c_str());
        }
    }
}

void ShopScene::UpdateDefense(cocos2d::Ref* sender) {
    if (m_player->Gold >= this->m_player->ValueG[1]) {
        this->m_player->Def += 10;
        Attribute[1]->setString(std::to_string(this->m_player->Def).c_str());
        m_player->Gold -= this->m_player->ValueG[1];
        PlayerGold->setString(std::to_string(this->m_player->Gold).c_str());
        this->m_player->ValueG[1] += 10;
        Gold[1]->setString(std::to_string(this->m_player->ValueG[1]).c_str());
    }
}

void ShopScene::UpdateAttack(cocos2d::Ref* sender) {
    if (m_player->Gold >= this->m_player->ValueG[0]) {
        this->m_player->Atk += 25;
        Attribute[0]->setString(std::to_string(this->m_player->Atk).c_str());
        m_player->Gold -= this->m_player->ValueG[0];
        PlayerGold->setString(std::to_string(this->m_player->Gold).c_str());
        this->m_player->ValueG[0] += 25;
        Gold[0]->setString(std::to_string(this->m_player->ValueG[0]).c_str());
    }
}

void ShopScene::UpdateSpeed(cocos2d::Ref* sender) {
    if (m_player->Gold >= this->m_player->ValueG[4]) {
        this->m_player->Speed += 2.5f;
        Attribute[4]->setString(StringUtils::format("%.1f", this->m_player->Speed).c_str());
        m_player->Gold -= this->m_player->ValueG[4];
        PlayerGold->setString(std::to_string(this->m_player->Gold).c_str());
        this->m_player->ValueG[4] += 25;
        Gold[4]->setString(std::to_string(this->m_player->ValueG[4]).c_str());
    }
}

void ShopScene::UpdateRegen(cocos2d::Ref* sender) {
    if (m_player->Gold >= this->m_player->ValueG[5]) {
        this->m_player->Regen += 1;
        Attribute[5]->setString(StringUtils::format("%d", this->m_player->Regen).c_str());
        m_player->Gold -= this->m_player->ValueG[5];
        PlayerGold->setString(std::to_string(this->m_player->Gold).c_str());
        this->m_player->ValueG[5] += 25;
        Gold[5]->setString(std::to_string(this->m_player->ValueG[5]).c_str());
    }
}

void ShopScene::UpdateBomb(cocos2d::Ref* sender) {
    if (m_player->Gold >= this->m_player->ValueG[6]) {
        this->m_mine->Damage += 25;
        this->m_trap->Damage += 25;
        Attribute[6]->setString(StringUtils::format("%d", this->m_mine->Damage).c_str());
        m_player->Gold -= this->m_player->ValueG[6];
        PlayerGold->setString(std::to_string(this->m_player->Gold).c_str());
        this->m_player->ValueG[6] += 25;
        Gold[6]->setString(std::to_string(this->m_player->ValueG[6]).c_str());
    }
}