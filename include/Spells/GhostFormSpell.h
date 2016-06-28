#pragma once

#include "global.h"
#include "Spells/Spell.h"

class LevelEquipment;

class GhostFormSpell : public Spell {
public:
	GhostFormSpell(const AttributeData& additionalDamage);
	virtual ~GhostFormSpell();
	
	void load(const SpellData& bean, LevelMovableGameObject* mob, const sf::Vector2f& target) override;
	void update(const sf::Time& frameTime) override;
	void render(sf::RenderTarget& target) override;
	void execOnHit(LevelMovableGameObject* target) override;

	bool getConfiguredRotateSprite() const override;

	void setDisposed() override;

private:
	LevelEquipment* m_mask = nullptr;
	static const sf::Color GHOST_COLOR;
	bool m_isFacingRight = true;

	particles::TextureParticleSystem* m_ps;
	particles::AngledVelocityGenerator* m_velGenerator;
	particles::ParticleSpawner* m_particleSpawner;

	void loadParticleSystem(float startSpeed);
	void loadMask();

	void updateParticleSystemPosition();

	AttributeData m_additionalDamage;
};