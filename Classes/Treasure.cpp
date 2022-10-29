#include "Treasure.h"

Treasure::Treasure(Scene* scene) {
	// Sprite
	winSize = Director::getInstance()->getWinSize();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	this->m_Treasure = Sprite::create("res\\GameScene\\Treasure1.png");
	this->m_Treasure->setPosition(Vec2::ZERO);
	//this->m_Treasure->setScale(0.1);

	//Physics, collision
	auto TreasureBody = PhysicsBody::createBox(this->m_Treasure->getContentSize());
	TreasureBody->setDynamic(false);
	TreasureBody->setCollisionBitmask(TREASURE_COLLISION_BITMASK);
	TreasureBody->setContactTestBitmask(true);
	this->m_Treasure->addComponent(TreasureBody);
	//Add to draw tree
	scene->addChild(this->m_Treasure, 1);

	num = 0;
}

void Treasure::SetPosition(Vec2 pos) {
	this->m_Treasure->setPosition(pos);
}

void Treasure::SetVisible(bool visible) {
	this->m_Treasure->setVisible(visible);
}

Vec2 Treasure::GetDirection() {
	if (this->m_Treasure != nullptr) {
		return this->m_Treasure->getPosition();
	}
	else {
		return Vec2();
	}
}

void Treasure::Roll() {
	num = random(0, 6);
}

int Treasure::Item() {
	return num;
}

void Treasure::RanPos() {
	int slot = random(0, 3);
	int rangex = random(0, 1200);
	int rangey = random(0, 1200);
	if (slot == 0) {
		this->m_Treasure->setPosition(-1200 + rangex, -1200 + rangey);
	} else
	if (slot == 1) {
		this->m_Treasure->setPosition(0 + rangex, -1200 + rangey);
	} else
	if (slot == 2) {
		this->m_Treasure->setPosition(-1200 + rangex, 0 + rangey);
	} else
	if (slot == 3) {
		this->m_Treasure->setPosition(0 + rangex, 0 + rangey);
	}
}