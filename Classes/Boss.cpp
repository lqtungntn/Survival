#include "Boss.h"

Boss::Boss(Scene* scene) {
	// Set Attribute
	this->Speed = 0.0;

	// Sprite
	winSize = Director::getInstance()->getWinSize();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	this->m_Boss = Sprite::create("res\\GameScene\\Boss.png");
	this->m_Boss->setPosition(Vec2::ZERO);
	this->m_Boss->setScale(2.0);

	//Physics, collision
	auto BossBody = PhysicsBody::createBox(this->m_Boss->getContentSize());
	BossBody->setDynamic(false);
	BossBody->setCollisionBitmask(BOSS_COLLISION_BITMASK);
	BossBody->setContactTestBitmask(true);
	this->m_Boss->addComponent(BossBody);
	//Add to draw tree
	scene->addChild(this->m_Boss, 1);
}

void Boss::SetPosition(Vec2 pos) {
	this->m_Boss->setPosition(pos);
}

void Boss::SetVisible(bool visible) {
	this->m_Boss->setVisible(visible);
}

void Boss::Moving(Vec2 pos) {
	if (this->m_Boss != nullptr) {
		Vec2 CalSpeed = (this->m_Boss->getPosition() - pos);
		if (CalSpeed.x != 0) {
			this->m_Boss->setScaleX(CalSpeed.x > 0 ? 2.0 : -2.0);
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
		this->m_Boss->setPosition(this->m_Boss->getPosition() + speed);
	}
}

Vec2 Boss::GetDirection() {
	if (this->m_Boss != nullptr) {
		return this->m_Boss->getPosition();
	}
	else {
		return Vec2();
	}
}