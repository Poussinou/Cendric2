#include "LevelMainCharacter.h"
#include "Screens/LevelScreen.h"

LevelMainCharacter::LevelMainCharacter(Level* level) : LevelMovableGameObject(level) {
	m_spellManager = new SpellManager(this);
	m_isQuickcast = g_resourceManager->getConfiguration().isQuickcast;
}

LevelMainCharacter::~LevelMainCharacter() {
	g_resourceManager->deleteResource(ResourceID::Texture_mainChar);
	m_spellKeyMap.clear();
}

void LevelMainCharacter::handleAttackInput() {
	if (g_inputController->isActionLocked()) return;
	// update current spell
	for (auto const &it : m_spellKeyMap) {
		if (g_inputController->isKeyJustPressed(it.first)) {
			if (m_isQuickcast) {
				m_spellManager->setCurrentSpell(it.second);
				m_spellManager->executeCurrentSpell(g_inputController->getMousePosition());
				if (m_invisibilityLevel > 0) {
					setInvisibilityLevel(0);
				}
			}
			else {
				m_spellManager->setAndExecuteSpell(it.second);
			}
			g_inputController->lockAction();
		}
	}

	// handle attack input
	if (g_inputController->isMouseJustPressedLeft()) {
		m_spellManager->executeCurrentSpell(g_inputController->getMousePosition());
		g_inputController->lockAction();
		if (m_invisibilityLevel > 0) {
			setInvisibilityLevel(0);
		}
	}
}

void LevelMainCharacter::handleMovementInput() {
	float newAccelerationX = 0;

	if (g_inputController->isKeyActive(Key::Left)) {
		m_nextIsFacingRight = false;
		newAccelerationX -= getConfiguredWalkAcceleration();
	}
	if (g_inputController->isKeyActive(Key::Right)) {
		m_nextIsFacingRight = true;
		newAccelerationX += getConfiguredWalkAcceleration();
	}
	if (g_inputController->isKeyJustPressed(Key::Jump) && m_isGrounded) {
		setVelocityY(m_isFlippedGravity ? getConfiguredMaxVelocityY() : -getConfiguredMaxVelocityY()); // first jump vel will always be max y vel. 
	}

	setAcceleration(sf::Vector2f(newAccelerationX, (m_isFlippedGravity ? -getConfiguredGravityAcceleration() : getConfiguredGravityAcceleration())));
}

void LevelMainCharacter::loadWeapon() {
	// chop is always set.
	m_spellKeyMap.clear();
	m_spellKeyMap.insert({ Key::Chop, 0 });

	if (m_core == nullptr || m_core->getWeapon() == nullptr) {
		g_logger->logWarning("LevelMainCharacter::loadWeapon", "character core is not set or weapon not found.");
		m_spellManager->addSpell(SpellBean::getSpellBean(SpellID::Chop));
		return;
	}
	const Weapon* weapon = m_core->getWeapon();

	int spellNr = 0;
	m_spellKeyMap.insert({ Key::FirstSpell, weapon->getCurrentSpellForSlot(0) == SpellID::VOID ? -1 : ++spellNr });
	m_spellKeyMap.insert({ Key::SecondSpell, weapon->getCurrentSpellForSlot(1) == SpellID::VOID ? -1 : ++spellNr });
	m_spellKeyMap.insert({ Key::ThirdSpell, weapon->getCurrentSpellForSlot(2) == SpellID::VOID ? -1 : ++spellNr });
	m_spellKeyMap.insert({ Key::FourthSpell, weapon->getCurrentSpellForSlot(3) == SpellID::VOID ? -1 : ++spellNr });
	m_spellKeyMap.insert({ Key::FifthSpell, weapon->getCurrentSpellForSlot(4) == SpellID::VOID ? -1 : ++spellNr });

	// get spells and add to spell manager
	m_spellManager->clearSpells();

	// handle chop spell
	SpellBean chop = SpellBean::getSpellBean(SpellID::Chop);
	chop.boundingBox = weapon->getWeaponChopRect();
	chop.cooldown = weapon->getWeaponCooldown();
	chop.damage = weapon->getWeaponChopDamage();
	chop.iconTextureRect = sf::IntRect(weapon->getIconTextureLocation().x, weapon->getIconTextureLocation().y, 50, 50);
	m_spellManager->addSpell(chop);

	// handle other spells
	for (int i = 0; i < 5; i++) {
		if (weapon->getCurrentSpellForSlot(i) == SpellID::VOID) continue;
		SpellBean newBean = SpellBean::getSpellBean(weapon->getCurrentSpellForSlot(i));
		switch (i) {
		case 0:
			newBean.inputKey = Key::FirstSpell;
			break;
		case 1:
			newBean.inputKey = Key::SecondSpell;
			break;
		case 2:
			newBean.inputKey = Key::ThirdSpell;
			break;
		case 3:
			newBean.inputKey = Key::FourthSpell;
			break;
		case 4:
			newBean.inputKey = Key::FifthSpell;
			break;
		default:
			// unexpected
			return;
		}

		// add modifiers for this slot
		if (weapon->getCurrentModifiersForSlot(i) == nullptr) {
			m_spellManager->addSpell(newBean);
			continue;
		}
		std::vector<SpellModifier> spellModifiers;
		for (auto& mod : *(weapon->getCurrentModifiersForSlot(i))) {
			spellModifiers.push_back(mod);
		}
		m_spellManager->addSpell(newBean, spellModifiers);
	}
}

void LevelMainCharacter::setCharacterCore(CharacterCore* core) {
	m_core = core;
	m_attributes = core->getTotalAttributes();
	setPosition(core->getData().currentLevelPosition);
	loadWeapon();
}

void LevelMainCharacter::setInvisibilityLevel(int level) {
	if (level < 0 || level > 4) return;
	m_invisibilityLevel = level;
	if (m_invisibilityLevel == 0) {
		dynamic_cast<LevelScreen*>(m_screen)->removeTypedBuffs(SpellID::Invisibility);
		setSpriteColor(sf::Color::White, sf::milliseconds(1));
	}
	else {
		// sets the color for a "sufficiently long" time. Other actions will reset invisibility.
		setSpriteColor(sf::Color(255, 255, 255, 75), sf::seconds(1000));
	}
}

int LevelMainCharacter::getInvisibilityLevel() const {
	return m_invisibilityLevel;
}

void LevelMainCharacter::addDamage(int damage) {
	// damage taken will remove invisibility
	setInvisibilityLevel(0);
	LevelMovableGameObject::addDamage(damage);
}

void LevelMainCharacter::load() {
	setBoundingBox(sf::FloatRect(0.f, 0.f, 30.f, 100.f));
	setSpriteOffset(sf::Vector2f(-25.f, -20.f));

	Animation walkingAnimation;
	walkingAnimation.setSpriteSheet(g_resourceManager->getTexture(ResourceID::Texture_mainChar));
	walkingAnimation.addFrame(sf::IntRect(0, 0, 80, 120));
	walkingAnimation.addFrame(sf::IntRect(80, 0, 80, 120));
	walkingAnimation.addFrame(sf::IntRect(160, 0, 80, 120));
	walkingAnimation.addFrame(sf::IntRect(240, 0, 80, 120));
	walkingAnimation.addFrame(sf::IntRect(320, 0, 80, 120));
	walkingAnimation.addFrame(sf::IntRect(400, 0, 80, 120));
	walkingAnimation.addFrame(sf::IntRect(480, 0, 80, 120));
	walkingAnimation.addFrame(sf::IntRect(560, 0, 80, 120));

	addAnimation(GameObjectState::Walking, walkingAnimation);

	Animation idleAnimation;
	idleAnimation.setSpriteSheet(g_resourceManager->getTexture(ResourceID::Texture_mainChar));
	idleAnimation.addFrame(sf::IntRect(640, 0, 80, 120));

	addAnimation(GameObjectState::Idle, idleAnimation);

	Animation jumpingAnimation;
	jumpingAnimation.setSpriteSheet(g_resourceManager->getTexture(ResourceID::Texture_mainChar));
	jumpingAnimation.addFrame(sf::IntRect(720, 0, 80, 120));

	addAnimation(GameObjectState::Jumping, jumpingAnimation);

	Animation fightingAnimation(sf::milliseconds(70));
	fightingAnimation.setSpriteSheet(g_resourceManager->getTexture(ResourceID::Texture_mainChar));
	fightingAnimation.addFrame(sf::IntRect(800, 0, 80, 120));
	fightingAnimation.addFrame(sf::IntRect(880, 0, 80, 120));
	fightingAnimation.addFrame(sf::IntRect(960, 0, 80, 120));
	fightingAnimation.addFrame(sf::IntRect(1040, 0, 80, 120));
	fightingAnimation.addFrame(sf::IntRect(1040, 0, 80, 120));

	addAnimation(GameObjectState::Fighting, fightingAnimation);

	Animation deadAnimation;
	deadAnimation.setSpriteSheet(g_resourceManager->getTexture(ResourceID::Texture_mainChar));
	deadAnimation.addFrame(sf::IntRect(1120, 0, 80, 120));

	addAnimation(GameObjectState::Dead, deadAnimation);

	// initial values
	m_state = GameObjectState::Idle;
	m_isFacingRight = true;
	setCurrentAnimation(getAnimation(m_state), !m_isFacingRight);
	playCurrentAnimation(true);

	setDebugBoundingBox(sf::Color::White);
}

float LevelMainCharacter::getConfiguredMaxVelocityY() const {
	return 600.0f;
}

float LevelMainCharacter::getConfiguredMaxVelocityX() const {
	return 200.0f;
}

float LevelMainCharacter::getConfiguredDampingGroundPersS() const {
	return 0.999f;
}

sf::Time LevelMainCharacter::getConfiguredFightAnimationTime() const {
	return sf::milliseconds(5 * 70);
}

GameObjectType LevelMainCharacter::getConfiguredType() const {
	return GameObjectType::_MainCharacter;
}

void LevelMainCharacter::lootItem(const std::string& item, int quantity) const {
	if (LevelScreen* levelScreen = dynamic_cast<LevelScreen*>(m_screen)) {
		levelScreen->notifyItemChange(item, quantity);
	}
}

void LevelMainCharacter::removeItems(const std::string& item, int quantity) const {
	if (LevelScreen* levelScreen = dynamic_cast<LevelScreen*>(m_screen)) {
		levelScreen->notifyItemChange(item, -quantity);
	}
}

void LevelMainCharacter::lootItems(std::map<std::string, int>& items) const {
	for (auto it : items) {
		lootItem(it.first, it.second);
	}
}

void LevelMainCharacter::addGold(int gold) const {
	if (LevelScreen* levelScreen = dynamic_cast<LevelScreen*>(m_screen)) {
		levelScreen->notifyItemChange("gold", gold);
	}
}

void LevelMainCharacter::removeGold(int gold) const {
	if (LevelScreen* levelScreen = dynamic_cast<LevelScreen*>(m_screen)) {
		levelScreen->notifyItemChange("gold", -gold);
	}
}
