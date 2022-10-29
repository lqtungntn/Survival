#include "MusicBox.h"
#include "audio/include/AudioEngine.h"

MusicBox::MusicBox(Scene* scene) {
	// Sprite
	winSize = Director::getInstance()->getWinSize();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	this->m_MusicBox = Sprite::create("res\\GameScene\\MusicBox.png");
	this->m_MusicBox->setPosition(Vec2::ZERO);
	this->m_MusicBox->setScale(0.5);

	//Physics, collision
	auto MusicBoxBody = PhysicsBody::createBox(this->m_MusicBox->getContentSize());
	MusicBoxBody->setDynamic(false);
	MusicBoxBody->setCollisionBitmask(MUSIC_BOX_COLLISION_BITMASK);
	MusicBoxBody->setContactTestBitmask(true);
	this->m_MusicBox->addComponent(MusicBoxBody);
	//Add to draw tree
	scene->addChild(this->m_MusicBox, 1);
}

void MusicBox::SetPosition(Vec2 pos) {
	this->m_MusicBox->setPosition(pos);
}

void MusicBox::SetVisible(bool visible) {
	this->m_MusicBox->setVisible(visible);
}

Vec2 MusicBox::GetDirection() {
	if (this->m_MusicBox != nullptr) {
		return this->m_MusicBox->getPosition();
	}
	else {
		return Vec2();
	}
}

bool MusicBox::IsVisible() {
	return this->m_MusicBox->isVisible();
}

void MusicBox::RanPos() {
	int slot = random(0, 3);
	int rangex = random(0, 1200);
	int rangey = random(0, 1200);
	if (slot == 0) {
		this->m_MusicBox->setPosition(-1200 + rangex, -1200 + rangey);
	}
	else
		if (slot == 1) {
			this->m_MusicBox->setPosition(0 + rangex, -1200 + rangey);
		}
		else
			if (slot == 2) {
				this->m_MusicBox->setPosition(-1200 + rangex, 0 + rangey);
			}
			else
				if (slot == 3) {
					this->m_MusicBox->setPosition(0 + rangex, 0 + rangey);
				}
}

void MusicBox::PlayerPos(Vec2 pos) {
	PPos = pos;
	
	AudioEngine::resume(AudioID);
	float distance = pow(pow(this->m_MusicBox->getPosition().x - PPos.x, 2) + pow(this->m_MusicBox->getPosition().y - PPos.y, 2), 0.5);

	if (distance < 2000.0f) {
		AudioEngine::setVolume(AudioID, (1.0f - distance / 2000.0f) * Global_Volumn);
	}
	else {
		AudioEngine::setVolume(AudioID, 0);
	}

}