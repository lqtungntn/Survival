#include "Player.h"

Player::Player(Scene* scene) {
	// Set Attribute
	this->Hearth = 100;
	this->Atk = 100;
	this->Def = 5;
	this->Speed = 5.0;
	this->CoolDownBomb = 0;
	this->CoolDownTrap = 0;
	this->CurrHearth = 100;
	this->Gold = 0;
	for (int i = 0; i < 7; i++) {
		ValueG[i] = 100;
	}

	// Sprite
	winSize = Director::getInstance()->getWinSize();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	this->m_character = Sprite::create("res\\GameScene\\Ninja.png");
	this->m_character->setPosition(Vec2(0, 0));
	this->m_character->setScale(0.2);

	//Physics, collision
	auto playerBody = PhysicsBody::createBox(this->m_character->getContentSize());
	playerBody->setDynamic(false);
	playerBody->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
	playerBody->setContactTestBitmask(true);
	this->m_character->addComponent(playerBody);
	//Add to draw tree
	scene->addChild(this->m_character, 1);
}

void Player::Moving() {
	if (Direction.x != 0) {
		this->m_character->setScaleX(abs(this->m_character->getScaleX()) * Direction.x);
	}
	auto playerPos = this->m_character->getPosition();
	if (Direction.x == 1 && playerPos.x < 1200)
		playerPos.x += Direction.x * Speed;
	if (Direction.x == -1 && playerPos.x > -1200)
		playerPos.x += Direction.x * Speed;
	if (Direction.y == 1 && playerPos.y < 1200)
		playerPos.y += Direction.y * Speed;
	if (Direction.y == -1 && playerPos.y > -1200)
		playerPos.y += Direction.y * Speed;
	this->m_character->setPosition(playerPos);
}

Vec2 Player::GetDirection() {
	return this->m_character->getPosition();
}