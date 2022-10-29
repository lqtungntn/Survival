#include "Trap.h"

Trap::Trap(Scene* scene, int tag) {
	this->Damage = 100;

	// Sprite
	winSize = Director::getInstance()->getWinSize();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	this->m_Trap = Sprite::create("res\\GameScene\\Trap1.png");
	this->m_Trap->setPosition(Vec2::ZERO);
	this->m_Trap->setScale(0.2);

	//Physics, collision
	auto TrapBody = PhysicsBody::createBox(this->m_Trap->getContentSize());
	TrapBody->setDynamic(false);
	TrapBody->setCollisionBitmask(tag);
	TrapBody->setContactTestBitmask(true);
	this->m_Trap->addComponent(TrapBody);
	//Add to draw tree
	scene->addChild(this->m_Trap, 1);
}

void Trap::SetPosition(Vec2 pos) {
	this->m_Trap->setPosition(pos);
}

void Trap::SetVisible(bool visible) {
	this->m_Trap->setVisible(visible);
}