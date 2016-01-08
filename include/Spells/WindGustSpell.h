#pragma once

#include "global.h"
#include "Spell.h"
#include "Particles/ParticleSystem.h"

class WindGustSpell : public Spell {
public:
	WindGustSpell(float pushAcceleration);
	void load(const SpellData& bean, LevelMovableGameObject* mob, const sf::Vector2f& target) override;
	void update(const sf::Time& frameTime) override;
	void render(sf::RenderTarget& target) override;

	sf::Vector2f getConfiguredPositionOffset() const override;
	bool getConfiguredRotateSprite() const override;
	float getPushAcceleration() const;

private:
	float m_pushAcceleration;
	std::unique_ptr<particles::TextureParticleSystem> m_ps;
	particles::AngledVelocityGenerator* m_velGenerator;
	particles::BoxPositionGenerator* m_pointGenerator;

	void loadParticleSystem();

	void updateParticleSystemPosition();
};