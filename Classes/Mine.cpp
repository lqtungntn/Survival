#include "Mine.h"

Mine::Mine(Scene* scene, int tag) {
	this->Damage = 100;

	// Sprite
	winSize = Director::getInstance()->getWinSize();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	this->m_Mine = Sprite::create("res\\GameScene\\MineBomb.png");
	this->m_Mine->setPosition(Vec2::ZERO);
	this->m_Mine->setScale(0.2);

	//Physics, collision
	auto MineBody = PhysicsBody::createBox(this->m_Mine->getContentSize());
	MineBody->setDynamic(false);
	MineBody->setCollisionBitmask(tag);
	MineBody->setContactTestBitmask(true);
	this->m_Mine->addComponent(MineBody);
	//Add to draw tree
	scene->addChild(this->m_Mine, 1);
}

void Mine::SetPosition(Vec2 pos) {
	this->m_Mine->setPosition(pos);
}

void Mine::SetVisible(bool visible) {
	this->m_Mine->setVisible(visible);
}