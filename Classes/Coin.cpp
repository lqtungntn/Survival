#include "Coin.h"

Coin::Coin(Scene* scene, int tag) {
	// Sprite
	winSize = Director::getInstance()->getWinSize();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	this->m_Coin = Sprite::create("res\\GameScene\\coin.png");
	this->m_Coin->setPosition(Vec2::ZERO);
	this->m_Coin->setScale(0.5);

	//Physics, collision
	auto CoinBody = PhysicsBody::createBox(this->m_Coin->getContentSize());
	CoinBody->setDynamic(false);
	CoinBody->setCollisionBitmask(COIN_COLLISION_BITMASK + tag);
	CoinBody->setContactTestBitmask(true);
	this->m_Coin->addComponent(CoinBody);
	//Add to draw tree
	scene->addChild(this->m_Coin, 1);
}

void Coin::SetPosition(Vec2 pos) {
	this->m_Coin->setPosition(pos);
}

void Coin::SetVisible(bool visible) {
	this->m_Coin->setVisible(visible);
}

Vec2 Coin::GetDirection() {
	if (this->m_Coin != nullptr) {
		return this->m_Coin->getPosition();
	}
	else {
		return Vec2();
	}
}

bool Coin::IsVisible() {
	return this->m_Coin->isVisible();
}