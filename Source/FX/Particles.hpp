#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <list>

class ParticleManager
{
public:
	enum Level
	{
		Level_UnderWater,  // Under water based entities
		Level_OverWater,   // Over water based entities
		Level_UnderGround, // Under ground based entities
		Level_OverGround,  // Over ground based entities
		Level_UnderAir,    // Under air based entities
		Level_OverAir      // Over air based entities
	};

	class Emitter
	{
	};

	struct Particle
	{
		Level Height;
		float Life, Angle, Rotation;
		sf::Color Color;
		sf::FloatRect Rect;
		sf::Vector2f Position;
		sf::Vector2f Velocity;

		friend bool operator<(const Particle& l, const Particle& r) { return l.Height < r.Height; }
	};

	static ParticleManager& getSingleton();

	void addParticle(Particle&&);
	void clearParticles();

	void variadic_update(float dt);
	void draw(sf::RenderTarget& target, Level);

private:
	std::list<Particle> mParticles;
};

namespace Particles
{
	const ParticleManager::Particle Player_Casing = {
		ParticleManager::Level_UnderAir, 0.5f, -M_PI/2.f, 0, sf::Color::Yellow,
		sf::FloatRect(0,0,5,10), sf::Vector2f(), sf::Vector2f()
	};
}
