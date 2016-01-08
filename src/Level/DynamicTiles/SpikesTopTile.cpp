#include "Level/DynamicTiles/SpikesTopTile.h"
#include "Spell.h"

void SpikesTopTile::init() {
	setPositionOffset(sf::Vector2f(-5.f, -40.f));
	setSpriteOffset(sf::Vector2f(-5.f, -40.f));
	setBoundingBox(sf::FloatRect(0.f, 0.f, 40.f, 40.f));
}

void SpikesTopTile::load(int skinNr) {

	Animation idleAnimation(sf::seconds(10.0f));
	idleAnimation.setSpriteSheet(g_resourceManager->getTexture(ResourceID::Texture_tile_spikestop));
	idleAnimation.addFrame(sf::IntRect(0, (skinNr - 1) * m_tileSize.y * 2, m_tileSize.x, m_tileSize.y * 2));

	addAnimation(GameObjectState::Idle, idleAnimation);

	// initial values
	setState(GameObjectState::Idle);
	playCurrentAnimation(false);
}


void SpikesTopTile::onHit(LevelMovableGameObject* mob) {
	mob->setDead();
}
