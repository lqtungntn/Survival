#include "Monster.h"

Monster::Monster(Scene* scene, int tag) {
	// Set Attribute
	this->Hearth = 50;
	this->Atk = 10;
	this->Def = 5;
	this->AtkSpeed = 1.0;
	this->Speed = 4.0;
	this->Gold = Hearth * Def / (Atk * 2);

	// Sprite
	winSize = Director::getInstance()->getWinSize();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	this->m_monster = Sprite::create("res\\GameScene\\Golem.png");
	this->m_monster->setPosition(Vec2::ZERO);
	this->m_monster->setScale(0.1);

	//Physics, collision
	auto monsterBody = PhysicsBody::createBox(this->m_monster->getContentSize());
	monsterBody->setDynamic(false);
	monsterBody->setCollisionBitmask(tag);
	monsterBody->setContactTestBitmask(true);
	this->m_monster->addComponent(monsterBody);
	//Add to draw tree
	scene->addChild(this->m_monster, 1);
}

void Monster::SetPosition(Vec2 pos) {
	this->m_monster->setPosition(pos);
}

void Monster::SetVisible(bool visible) {
	this->m_monster->setVisible(visible);
}

void Monster::Moving(Vec2 pos) {
	if (this->m_monster != nullptr) {
		Vec2 CalSpeed = (this->m_monster->getPosition() - pos);
		if (CalSpeed.x != 0) {
			this->m_monster->setScaleX(CalSpeed.x > 0 ? 0.1 : -0.1);
		}
		Vec2 speed;
		if (CalSpeed.x < 0) {
			speed.x = (Speed > abs(CalSpeed.x)) ? abs(CalSpeed.x) : Speed;
		}
		else {
			speed.x = (Speed > abs(CalSpeed.x)) ? -abs(CalSpeed.x) : -Speed;
		}
		if (CalSpeed.y < 0) {
			speed.y = (Speed > abs(CalSpeed.y)) ? abs(CalSpeed.y) : Speed;
		}
		else {
			speed.y = (Speed > abs(CalSpeed.y)) ? -abs(CalSpeed.y) : -Speed;
		}
		this->m_monster->setPosition(this->m_monster->getPosition() + speed * Slow);
	}
}

Vec2 Monster::GetDirection() {
	if (this->m_monster != nullptr) {
		return this->m_monster->getPosition();
	}
	else {
		return Vec2();
	}
}