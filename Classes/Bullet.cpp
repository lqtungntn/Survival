#include "Bullet.h"

Bullet::Bullet(Scene* scene) {
	// Sprite
	winSize = Director::getInstance()->getWinSize();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	this->m_Bullet = Sprite::create("res\\GameScene\\Kunai.png");
	this->m_Bullet->setPosition(Vec2::ZERO);
	this->m_Bullet->setScale(0.2);

	//Physics, collision
	auto BulletBody = PhysicsBody::createBox(this->m_Bullet->getContentSize());
	BulletBody->setDynamic(false);
	BulletBody->setCollisionBitmask(BULLET_COLLISION_BITMASK);
	BulletBody->setContactTestBitmask(true);
	this->m_Bullet->addComponent(BulletBody);
	//Add to draw tree
	scene->addChild(this->m_Bullet, 1);
}

void Bullet::CalDir(Vec2 pos) {
	// Calculate
	Vec2 CalSpeed = (m_Bullet->getPosition() - pos);
	float angle = atan2(CalSpeed.x, CalSpeed.y) * (180 / PI);
	this->m_Bullet->setRotation(angle + 180);
	this->Speed = Vec2(sin(angle * PI / 180) * (1000.0f / AtkSpeed), cos(angle * PI / 180) * (1000.0f / AtkSpeed));
}

void Bullet::SetPosition(Vec2 pos) {
	this->m_Bullet->setPosition(pos);
}

void Bullet::SetVisible(bool visible) {
	this->m_Bullet->setVisible(visible);
}

void Bullet::Moving() { 
	this->m_Bullet->setPosition(this->m_Bullet->getPosition() - Speed);
}