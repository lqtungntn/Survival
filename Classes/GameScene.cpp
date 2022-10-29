#include "GameScene.h"
#include "GameOverScene.h"
#include "audio/include/AudioEngine.h"

Scene* GameScene::createScene()
{
    auto scene = GameScene::create();

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//disable default gravity
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

    return scene;
}

bool GameScene::init()
{
    if ( !GameScene::initWithPhysics() )
    {
        return false;
    }

    winSize = Director::getInstance()->getWinSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Event
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyRelease, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// Sound
	BulletS = AudioEngine::play2d("Audio/Arrow.wav", true, 0.0);
	coinS = AudioEngine::play2d("Audio/coin.wav", true, 0.0);
	MonsterAtkS = AudioEngine::play2d("Audio/monsterAtk.mp3", true, 0.0);
	MonsterDeadS = AudioEngine::play2d("Audio/dead.wav", true, 0.0);
	MusicBoxS = AudioEngine::play2d("Audio/music_box.mp3", true, 0.0);
	BGS = AudioEngine::play2d("Audio/BGmp3.mp3", true, 0.0);
	AudioEngine::pauseAll();
	AudioEngine::setCurrentTime(BGS, 0);
	AudioEngine::setVolume(BGS, Global_Volumn);
	AudioEngine::resume(BGS);

    // Draw BackGround
    auto backgroundSprite = Sprite::create("res\\GameScene\\map.jpg");
    backgroundSprite->setPosition(Point(0, 0));
    backgroundSprite->setScale(winSize.width / backgroundSprite->getContentSize().width * 4, winSize.height / backgroundSprite->getContentSize().height * 4);
    this->addChild(backgroundSprite, 0);

    // Draw Player
	m_player = new Player(this);

	// Draw Boss
	m_boss = new Boss(this);
	m_boss->setPosition(Point(0, 0));
	m_boss->SetVisible(false);

	// Draw Boss
	m_musicBox = new MusicBox(this);
	m_musicBox->SetPosition(Point(0, 0));
	m_musicBox->SetVisible(false);
	m_musicBox->AudioID = MusicBoxS;
	AudioEngine::pause(m_musicBox->AudioID);

	// Draw Monster
	for (int i = 0; i < MONSTER_LIMIT; i++) {
		m_mons.push_back(new Monster(this, i));
		m_monsVisible.push_back(false);
		m_monsAtk.push_back(100);
		m_mons[i]->SetVisible(m_monsVisible[i]);
		m_mons[i]->SetPosition(Vec2(sin(static_cast<float>(cocos2d::random(0, 360)) * PI / 180) * 1000, cos(static_cast<float>(cocos2d::random(0, 360)) * PI / 180) * 1000));
	}

	// Draw coin
	for (int i = 0; i < COIN_LIMIT; i++) {
		m_coin.push_back(new Coin(this, i));
		m_coin[i]->SetVisible(false);
		m_coin[i]->SetPosition(winSize);
	}

	// Draw Gold
	for (int i = 0; i <= COIN_LIMIT; i++) {
		m_goldArr[i] = Label::createWithTTF(StringUtils::format("%d", 0), "fonts/arial.ttf", 25.0f);
		m_goldArr[i]->setColor(Color3B::RED);
		m_goldArr[i]->setPosition(Point(0, 0));
		m_goldArr[i]->setVisible(false);
		m_GAC[i] = 0;
		this->addChild(m_goldArr[i], 3);
	}

	// Draw Bullet
	m_bullet = new Bullet(this);

	// Draw Treasure
	m_treasure = new Treasure(this);
	m_treasure->RanPos();

	// Draw UI
	UIFollowPlayer();

	// Draw Trap
	for (int i = 0; i < TRAP_LIMIT; i++) {
		m_trap.push_back(new Trap(this, i + MONSTER_LIMIT));
		m_trapVisible.push_back(false);
		m_trap[i]->SetVisible(m_trapVisible[i]);
		m_trap[i]->SetPosition(Vec2(0, 0));
	}

	// Draw Mine
	for (int i = 0; i < MINE_LIMIT; i++) {
		m_mine.push_back(new Mine(this, i + MONSTER_LIMIT + TRAP_LIMIT));
		m_mineVisible.push_back(false);
		m_mine[i]->SetVisible(m_mineVisible[i]);
		m_mine[i]->SetPosition(Vec2(0, 0));
	}

	// Check physic
	auto contactEnterListener = EventListenerPhysicsContact::create();
	contactEnterListener->onContactBegin = [this](cocos2d::PhysicsContact& contact) {
		PhysicsBody* a = contact.getShapeA()->getBody();
		PhysicsBody* b = contact.getShapeB()->getBody();
		// Collide monster with bullet
		if ((0 <= a->getCollisionBitmask() && a->getCollisionBitmask() < MONSTER_LIMIT && b->getCollisionBitmask() == BULLET_COLLISION_BITMASK) ||
			(0 <= b->getCollisionBitmask() && b->getCollisionBitmask() < MONSTER_LIMIT && a->getCollisionBitmask() == BULLET_COLLISION_BITMASK)) {
			if (a->getCollisionBitmask() != BULLET_COLLISION_BITMASK && m_monsVisible[a->getCollisionBitmask()]) {
				if (m_mons[a->getCollisionBitmask()]->Hearth - m_player->Atk <= 0) {
					m_monsVisible[a->getCollisionBitmask()] = false;
					m_mons[a->getCollisionBitmask()]->SetVisible(false);
					MonsterDeath(a->getCollisionBitmask());
				}
				else {
					m_mons[a->getCollisionBitmask()]->Hearth -= m_player->Atk;
				}
				m_bullet->NeedReset = true;
				m_ResetBullet = false;
			}
			if (b->getCollisionBitmask() != BULLET_COLLISION_BITMASK && m_monsVisible[b->getCollisionBitmask()]) {
				if (m_mons[b->getCollisionBitmask()]->Hearth - m_player->Atk <= 0) {
					m_monsVisible[b->getCollisionBitmask()] = false;
					m_mons[b->getCollisionBitmask()]->SetVisible(false);
					MonsterDeath(b->getCollisionBitmask());
				}
				else {
					m_mons[b->getCollisionBitmask()]->Hearth -= m_player->Atk;
				}
				m_bullet->NeedReset = true;
				m_ResetBullet = false;
			}
		}
		
		// Collide monster with mine
		if ((0 <= a->getCollisionBitmask() && a->getCollisionBitmask() < MONSTER_LIMIT && MONSTER_LIMIT + TRAP_LIMIT <= b->getCollisionBitmask() && b->getCollisionBitmask() < MONSTER_LIMIT + MINE_LIMIT + TRAP_LIMIT) ||
			(0 <= b->getCollisionBitmask() && b->getCollisionBitmask() < MONSTER_LIMIT && MONSTER_LIMIT + TRAP_LIMIT <= a->getCollisionBitmask() && a->getCollisionBitmask() < MONSTER_LIMIT + MINE_LIMIT + TRAP_LIMIT)) {
			if (0 <= a->getCollisionBitmask() && a->getCollisionBitmask() < MONSTER_LIMIT && m_monsVisible[a->getCollisionBitmask()]) {
				if (m_mons[a->getCollisionBitmask()]->Hearth - m_mine[b->getCollisionBitmask() - MONSTER_LIMIT - TRAP_LIMIT]->Damage <= 0) {
					m_monsVisible[a->getCollisionBitmask()] = false;
					m_mons[a->getCollisionBitmask()]->SetVisible(false);
					MonsterDeath(a->getCollisionBitmask());
				}
				else {
					m_mons[a->getCollisionBitmask()]->Hearth -= m_mine[b->getCollisionBitmask() - MONSTER_LIMIT - TRAP_LIMIT]->Damage;
				}
				m_mineVisible[b->getCollisionBitmask() - MONSTER_LIMIT - TRAP_LIMIT] = false;
				m_mine[b->getCollisionBitmask() - MONSTER_LIMIT - TRAP_LIMIT]->SetVisible(false);
				mineCount--;
			}
			if (0 <= b->getCollisionBitmask() && b->getCollisionBitmask() < MONSTER_LIMIT && m_monsVisible[b->getCollisionBitmask()]) {
				if (m_mons[b->getCollisionBitmask()]->Hearth - m_mine[a->getCollisionBitmask() - MONSTER_LIMIT - TRAP_LIMIT]->Damage <= 0) {
					m_monsVisible[b->getCollisionBitmask()] = false;
					m_mons[b->getCollisionBitmask()]->SetVisible(false);
					MonsterDeath(b->getCollisionBitmask());
				}
				else {
					m_mons[b->getCollisionBitmask()]->Hearth -= m_mine[a->getCollisionBitmask() - MONSTER_LIMIT - TRAP_LIMIT]->Damage;
				}
				m_mineVisible[a->getCollisionBitmask() - MONSTER_LIMIT - TRAP_LIMIT] = false;
				m_mine[a->getCollisionBitmask() - MONSTER_LIMIT - TRAP_LIMIT]->SetVisible(false);
				mineCount--;
			}
		}

		// Collide monster with trap
		if ((0 <= a->getCollisionBitmask() && a->getCollisionBitmask() < MONSTER_LIMIT && MONSTER_LIMIT <= b->getCollisionBitmask() && b->getCollisionBitmask() < MONSTER_LIMIT + TRAP_LIMIT) ||
			(0 <= b->getCollisionBitmask() && b->getCollisionBitmask() < MONSTER_LIMIT && MONSTER_LIMIT <= a->getCollisionBitmask() && a->getCollisionBitmask() < MONSTER_LIMIT + TRAP_LIMIT)) {
			if (0 <= a->getCollisionBitmask() && a->getCollisionBitmask() < MONSTER_LIMIT && m_monsVisible[a->getCollisionBitmask()]) {
				if (m_mons[a->getCollisionBitmask()]->Hearth - m_trap[b->getCollisionBitmask() - MONSTER_LIMIT]->Damage <= 0) {
					m_monsVisible[a->getCollisionBitmask()] = false;
					m_mons[a->getCollisionBitmask()]->SetVisible(false);
					m_mons[a->getCollisionBitmask()]->Slow = 0.0;
					m_mons[a->getCollisionBitmask()]->SlowCount = 0;
					m_monsAtk[a->getCollisionBitmask()] = 0;
					MonsterDeath(a->getCollisionBitmask());
				}
				else {
					m_monsAtk[a->getCollisionBitmask()] = 0;
					m_mons[a->getCollisionBitmask()]->Hearth -= m_trap[b->getCollisionBitmask() - MONSTER_LIMIT]->Damage;
				}
				m_trapVisible[b->getCollisionBitmask() - MONSTER_LIMIT] = false;
				m_trap[b->getCollisionBitmask() - MONSTER_LIMIT]->SetVisible(false);
				trapCount--;
			}
			if (0 <= b->getCollisionBitmask() && b->getCollisionBitmask() < MONSTER_LIMIT && m_monsVisible[b->getCollisionBitmask()]) {
				if (m_mons[b->getCollisionBitmask()]->Hearth - m_trap[a->getCollisionBitmask() - MONSTER_LIMIT]->Damage <= 0) {
					m_monsVisible[b->getCollisionBitmask()] = false;
					m_mons[b->getCollisionBitmask()]->SetVisible(false);
					m_mons[b->getCollisionBitmask()]->Slow = 0.0;
					m_mons[b->getCollisionBitmask()]->SlowCount = 0;
					m_monsAtk[b->getCollisionBitmask()] = 0;
					MonsterDeath(b->getCollisionBitmask());
				}
				else {
					m_monsAtk[b->getCollisionBitmask()] = 0;
					m_mons[b->getCollisionBitmask()]->Hearth -= m_trap[a->getCollisionBitmask() - MONSTER_LIMIT]->Damage;
				}
				m_trapVisible[a->getCollisionBitmask() - MONSTER_LIMIT] = false;
				m_trap[a->getCollisionBitmask() - MONSTER_LIMIT]->SetVisible(false);
				trapCount--;
			}
		}

		// Collide monster with player
		if ((0 <= a->getCollisionBitmask() && a->getCollisionBitmask() < MONSTER_LIMIT && b->getCollisionBitmask() == PLAYER_COLLISION_BITMASK) ||
			(0 <= b->getCollisionBitmask() && b->getCollisionBitmask() < MONSTER_LIMIT && a->getCollisionBitmask() == PLAYER_COLLISION_BITMASK)) {
			if (a->getCollisionBitmask() != PLAYER_COLLISION_BITMASK) {
				if (m_monsAtk[a->getCollisionBitmask()] == 100 && m_monsVisible[a->getCollisionBitmask()]) {
					m_player->CurrHearth -= MAX(0, m_mons[a->getCollisionBitmask()]->Atk - m_player->Def);
					m_monsAtk[a->getCollisionBitmask()] = 0;
				}
			}
			if (b->getCollisionBitmask() != PLAYER_COLLISION_BITMASK) {
				if (m_monsAtk[b->getCollisionBitmask()] == 100 && m_monsVisible[b->getCollisionBitmask()]) {
					m_player->CurrHearth -= MAX(0, m_mons[b->getCollisionBitmask()]->Atk - m_player->Def);
					m_monsAtk[b->getCollisionBitmask()] = 0;
				}
			}
		}

		// Collide treasure with player
		if ((a->getCollisionBitmask() == PLAYER_COLLISION_BITMASK && b->getCollisionBitmask() == TREASURE_COLLISION_BITMASK) ||
			(b->getCollisionBitmask() == PLAYER_COLLISION_BITMASK && a->getCollisionBitmask() == TREASURE_COLLISION_BITMASK)) {
			m_treasure->Roll();
			m_GAC[MONSTER_LIMIT] = 100;
			if (m_treasure->Item() == 0) {
				int num = random(10, 100);
				m_goldArr[MONSTER_LIMIT]->setString(StringUtils::format("+%dGold", num));
				this->m_player->Gold += num;
			}
			else if (m_treasure->Item() == 1) {
				int num = 25;
				m_goldArr[MONSTER_LIMIT]->setString(StringUtils::format("+%dAtk", num));
				this->m_player->Atk += num;
			}
			else if (m_treasure->Item() == 2) {
				int num = 25;
				m_goldArr[MONSTER_LIMIT]->setString(StringUtils::format("+%dHearth", num));
				this->m_player->Hearth += num;
				this->m_player->CurrHearth += num;
			}
			else if (m_treasure->Item() == 3) {
				int num = 4;
				m_goldArr[MONSTER_LIMIT]->setString(StringUtils::format("+%dAtkSpeed", num));
				if (this->m_bullet->AtkSpeed > 4) {
					this->m_bullet->AtkSpeed -= num;
				}
			}
			else if (m_treasure->Item() == 4) {
				int num = 5;
				m_goldArr[MONSTER_LIMIT]->setString(StringUtils::format("+%dDef", num));
				this->m_player->Def += num;
			}
			else if (m_treasure->Item() == 5) {
				int num = 1;
				m_goldArr[MONSTER_LIMIT]->setString(StringUtils::format("+%dSpeed", num));
				this->m_player->Speed += num;
			}
			else if (m_treasure->Item() == 6) {
				int num = 1;
				m_goldArr[MONSTER_LIMIT]->setString(StringUtils::format("+%dRegen", num));
				this->m_player->Regen += num;
			}
			m_goldArr[MONSTER_LIMIT]->setPosition(m_treasure->GetDirection());
			m_goldArr[MONSTER_LIMIT]->setVisible(true);
			m_treasure->RanPos();
		}
		
		// Collide treasure with player
		if ((COIN_COLLISION_BITMASK <= a->getCollisionBitmask() && a->getCollisionBitmask() < COIN_COLLISION_BITMASK + COIN_LIMIT && b->getCollisionBitmask() == PLAYER_COLLISION_BITMASK) ||
			(COIN_COLLISION_BITMASK <= b->getCollisionBitmask() && b->getCollisionBitmask() < COIN_COLLISION_BITMASK + COIN_LIMIT && a->getCollisionBitmask() == PLAYER_COLLISION_BITMASK)) {
			if (a->getCollisionBitmask() != PLAYER_COLLISION_BITMASK){ 
				if (m_coin[a->getCollisionBitmask() - COIN_COLLISION_BITMASK]->isVisible()) {
					TakeCoin(a->getCollisionBitmask() - COIN_COLLISION_BITMASK);
				}
			}
			if (b->getCollisionBitmask() != PLAYER_COLLISION_BITMASK) {
				if (m_coin[b->getCollisionBitmask() - COIN_COLLISION_BITMASK]->isVisible()) {
					TakeCoin(b->getCollisionBitmask() - COIN_COLLISION_BITMASK);
				}
			}
		}

		if (BossCount > BOSS_COUNT) {
			// Collide boss with player
			if ((a->getCollisionBitmask() == BOSS_COLLISION_BITMASK && b->getCollisionBitmask() == PLAYER_COLLISION_BITMASK) ||
				(b->getCollisionBitmask() == BOSS_COLLISION_BITMASK && a->getCollisionBitmask() == PLAYER_COLLISION_BITMASK)) {
				this->m_player->CurrHearth = 0;
			}

			// Collide music box with player
			if ((a->getCollisionBitmask() == MUSIC_BOX_COLLISION_BITMASK && b->getCollisionBitmask() == PLAYER_COLLISION_BITMASK) ||
				(b->getCollisionBitmask() == MUSIC_BOX_COLLISION_BITMASK && a->getCollisionBitmask() == PLAYER_COLLISION_BITMASK)) {
				this->m_musicBox->RanPos();
				this->m_boss->Hearth -= 25;
			}
		}

		return true;
	};

	schedule(CC_SCHEDULE_SELECTOR(GameScene::UpdateMonster), 5.0f);
	schedule(CC_SCHEDULE_SELECTOR(GameScene::SpawnMonster), 1.0f);
	schedule(CC_SCHEDULE_SELECTOR(GameScene::MovingMonster), 1.0f / 30);
	schedule(CC_SCHEDULE_SELECTOR(GameScene::ResetBullet), 0.01f);
	schedule(CC_SCHEDULE_SELECTOR(GameScene::FireBullet), 0.01f);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactEnterListener, this);

    scheduleUpdate();

    return true;
}

void GameScene::FireBullet(float dt) {
	if (this->m_player->CurrHearth <= 0) {
		AudioEngine::pauseAll();
		auto scene = GameOverScene::createScene();
		Global_Is_Win = false;
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	}
	else 
	if (this->m_boss->Hearth <= 0) {
		AudioEngine::pauseAll();
		auto scene = GameOverScene::createScene();
		Global_Is_Win = true;
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	}
	if (BossCount < BOSS_COUNT) {
		if (m_ResetBullet) {
			m_bullet->Moving();
		}
		for (int i = 0; i < MONSTER_LIMIT; i++) {
			if (m_monsAtk[i] < 100) {
				m_monsAtk[i] += 2;
			}
		}
		BossCount++;
	} else
	if (BossCount == BOSS_COUNT) {
		m_boss->SetVisible(true);
		m_boss->setPosition(Point(0, 0));
		m_playerLight->setVisible(true);
		for (int i = 0; i < MONSTER_LIMIT; i++) {
			MonsterDeath(i);
		}
		m_bullet->SetVisible(false);
		m_musicBox->RanPos();
		m_musicBox->SetVisible(true);
		BossHeartBar->setVisible(true);
		BGBossHeartBar->setVisible(true);
		BossCount++;
		AudioEngine::pauseAll();
	} else {
		m_boss->Moving(m_player->GetDirection());
		m_musicBox->PlayerPos(m_player->GetDirection());
		BossHeartBar->setPercent(m_boss->Hearth);
	}
}

void GameScene::UpdateMonster(float dt) {
	if (BossCount < BOSS_COUNT) {
		for (int i = 0; i < MONSTER_LIMIT; i++) {
			m_mons[i]->Atk += 1;
			m_mons[i]->Hearth += 5;
			m_mons[i]->Def += 1;
		}
	}
	else {
		m_boss->Speed += 0.1;
	}
}

void GameScene::ResetBullet(float dt) {
	if (m_bullet->NeedReset || m_ResetBullet == false) {
		m_bullet->SetPosition(m_player->GetDirection());
		m_bullet->CalDir(m_mons[nearPlayer]->GetDirection());
		m_bullet->NeedReset = false;
	}
	if (m_bullet->AtkSpeed == FrameCount) {
		m_bullet->SetPosition(m_player->GetDirection());
		m_bullet->CalDir(m_mons[nearPlayer]->GetDirection());
		m_bullet->NeedReset = false;
		m_ResetBullet = true;
		FrameCount = 0;
	}
	else {
		FrameCount++;
	}

	if (m_player->CoolDownBomb > 0)
		m_player->CoolDownBomb--;
	if (m_player->CoolDownTrap > 0)
		m_player->CoolDownTrap--;
	for (int i = 0; i < MONSTER_LIMIT; i++) {
		if (m_mons[i]->SlowCount != 0) {
			m_mons[i]->SlowCount--;
		}
		else {
			m_mons[i]->Slow = 1.0f;
		}
	}

	for (int i = 0; i <= MONSTER_LIMIT; i++) {
		if (m_GAC[i] != 0) {
			m_GAC[i]--;
		}
		else {
			m_goldArr[i]->setVisible(false);
		}
	}
}

void GameScene::SpawnMonster(float dt) {
	if (BossCount < BOSS_COUNT) {
		if (m_player->CurrHearth < m_player->Hearth) {
			m_player->CurrHearth = MIN(m_player->CurrHearth + m_player->Regen, m_player->Hearth);
		}
		if (m_player->CurrHearth > m_player->Hearth) {
			m_player->CurrHearth = m_player->Hearth;
		}

		for (int i = 0; i < MONSTER_LIMIT; i++) {
			if (m_monsVisible[i] == false) {
				m_monsVisible[i] = true;
				m_mons[i]->Hearth = 100;
				m_mons[i]->SetVisible(m_monsVisible[i]);
				m_mons[i]->SetPosition(Vec2(sin(static_cast<float>(cocos2d::random(0, 360)) * PI / 180) * 1000 + m_player->GetDirection().x, cos(static_cast<float>(cocos2d::random(0, 360)) * PI / 180) * 1000 + m_player->GetDirection().y));
				break;
			}
		}
	}
}

void GameScene::MovingMonster(float dt) {
	if (BossCount < BOSS_COUNT) {
		int ssMax = INT32_MAX;
		nearPlayer = 0;
		for (int i = 0; i < MONSTER_LIMIT; i++) {
			if (m_monsVisible[i]) {
				m_mons[i]->Moving(m_player->GetDirection());
				Vec2 MDir = m_mons[i]->GetDirection();
				if (ssMax > abs(MDir.x - m_player->GetDirection().x) + abs(MDir.y - m_player->GetDirection().y)) {
					nearPlayer = i;
					ssMax = abs(MDir.x - m_player->GetDirection().x) + abs(MDir.y - m_player->GetDirection().y);
				}
			}
		}
	}
}

void GameScene::UIFollowPlayer() {
	Canvas->setPosition(0, 0);

	// Hearth Bar
	BGHeartBar = cocos2d::ui::LoadingBar::create("res/GameScene/RedBar.png");
	BGHeartBar->setPosition(Point(winSize.width * -0.3f, winSize.height * 0.45f));
	BGHeartBar->setDirection(cocos2d::ui::LoadingBar::Direction::LEFT);
	BGHeartBar->setPercent(100);
	Canvas->addChild(BGHeartBar);

	HeartBar = cocos2d::ui::LoadingBar::create("res/GameScene/GreenBar.png");
	HeartBar->setDirection(cocos2d::ui::LoadingBar::Direction::LEFT);
	HeartBar->setPosition(Point(winSize.width * -0.3f, winSize.height * 0.45f));
	HeartBar->setPercent(100);
	Canvas->addChild(HeartBar);

	// Gold
	m_playerGold = Label::createWithTTF(StringUtils::format("%d", this->m_player->Gold), "fonts/arial.ttf", 25.0f);
	m_playerGold->setColor(Color3B::MAGENTA);
	m_playerGold->setPosition(Point(winSize.width * 0.25f, winSize.height * 0.45f));
	Canvas->addChild(m_playerGold);

	// Light
	m_playerLight = Sprite::create("res/GameScene/light3.png");
	m_playerLight->setPosition(Point(0, 0));
	m_playerLight->setVisible(false);
	m_playerLight->setScale(20.0f);
	Canvas->addChild(m_playerLight);

	// Hearth Bar
	BGBossHeartBar = cocos2d::ui::LoadingBar::create("res/GameScene/RedBar.png");
	BGBossHeartBar->setPosition(Point(winSize.width * -0.3f, winSize.height * 0.45f));
	BGBossHeartBar->setDirection(cocos2d::ui::LoadingBar::Direction::LEFT);
	BGBossHeartBar->setScale(1.5, 2.5);
	BGBossHeartBar->setPercent(100);
	BGBossHeartBar->setVisible(false);
	Canvas->addChild(BGBossHeartBar);

	BossHeartBar = cocos2d::ui::LoadingBar::create("res/GameScene/GreenBar.png");
	BossHeartBar->setDirection(cocos2d::ui::LoadingBar::Direction::LEFT);
	BossHeartBar->setPosition(Point(winSize.width * -0.3f, winSize.height * 0.45f));
	BossHeartBar->setScale(1.5, 2.5);
	BossHeartBar->setPercent(100);
	BossHeartBar->setVisible(false);
	Canvas->addChild(BossHeartBar);

	this->addChild(Canvas, 5);
}

void GameScene::update(float dt) {
	for (int i = 0; i < MINE_LIMIT; i++) {
		m_mine[i]->Damage = m_mine[0]->Damage;
		m_trap[i]->Damage = m_trap[0]->Damage;
	}

	if (m_player != nullptr) {
		m_player->Moving();
		cam = Camera::getDefaultCamera();
		cam->setPositionX(m_player->GetDirection().x);
		cam->setPositionY(m_player->GetDirection().y);
		float cal = (float)(m_player->CurrHearth * 100) / m_player->Hearth;
		HeartBar->setPercent(MAX(0, cal));
		m_playerGold->setString(StringUtils::format("Gold: %d", this->m_player->Gold));
		Canvas->setPosition(m_player->GetDirection());
	}
}

void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* evt) {
	switch (key) {
	case EventKeyboard::KeyCode::KEY_A:
		m_player->Direction.x = -1;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		m_player->Direction.x = 1;
		break;
	case EventKeyboard::KeyCode::KEY_W:
		m_player->Direction.y = 1;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		m_player->Direction.y = -1;
		break;
	}
}

void GameScene::onKeyRelease(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* evt) {
	switch (key) {
	case EventKeyboard::KeyCode::KEY_A:
		m_player->Direction.x = 0;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		m_player->Direction.x = 0;
		break;
	case EventKeyboard::KeyCode::KEY_W:
		m_player->Direction.y = 0;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		m_player->Direction.y = 0;
		break;
	case EventKeyboard::KeyCode::KEY_Z:
		if (m_player->CoolDownBomb == 0 && mineCount < MINE_LIMIT) {
			m_player->CoolDownBomb = 100;
			for (int i = 0; i < MINE_LIMIT; i++) {
				if (m_mineVisible[i] == false) {
					m_mineVisible[i] = true;
					m_mine[i]->SetPosition(m_player->GetDirection());
					m_mine[i]->SetVisible(true);
					break;
				}
			}
			mineCount++;
		}
		break;
	case EventKeyboard::KeyCode::KEY_X:
		if (m_player->CoolDownTrap == 0 && trapCount < TRAP_LIMIT) {
			m_player->CoolDownTrap = 100;
			for (int i = 0; i < TRAP_LIMIT; i++) {
				if (m_trapVisible[i] == false) {
					m_trapVisible[i] = true;
					m_trap[i]->SetPosition(m_player->GetDirection());
					m_trap[i]->SetVisible(true);
					break;
				}
			}
			trapCount++;
		}
		break;
	case EventKeyboard::KeyCode::KEY_P:
		Global_Player = m_player;
		Global_Bullet = m_bullet;
		Global_Mine = m_mine[0];
		Global_Trap = m_trap[0];
		Director::getInstance()->pause();
		Director::getInstance()->pushScene(ShopScene::createScene());
		break;
	}
}

void GameScene::MonsterDeath(int idx) {
	for (int i = 0; i < COIN_LIMIT; i++) {
		if (m_coin[i]->IsVisible() == false) {
			m_coin[i]->SetVisible(true);
			m_coin[i]->SetPosition(m_mons[idx]->GetDirection());
			m_coin[i]->gold = m_mons[idx]->Gold;
			break;
		}
	}
}

void GameScene::TakeCoin(int idx) {
	this->m_player->Gold += m_coin[idx]->gold;
	this->m_GAC[idx] = 100;
	this->m_goldArr[idx]->setVisible(true);
	this->m_goldArr[idx]->setPosition(this->m_coin[idx]->GetDirection());
	this->m_goldArr[idx]->setString(StringUtils::format("+%dGold", m_coin[idx]->gold));
	m_coin[idx]->SetVisible(false);
}

GameScene::~GameScene() {
	delete m_player;
	delete m_treasure;
	delete m_boss;
	delete m_musicBox;
}