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

	struct Particle
	{
		Level Height;
		float Life, Angle, Rotation;
		sf::Color Color;
		sf::FloatRect Rect;
		sf::Vector2f Position;
		sf::Vector2f Velocity;

		friend bool operator<(const Particle& l, const Particle& r) { return l.Height < r.Height; }

		// This is set by the particle manager
		float StartLife;
	};

	static void init();

	static void addParticle(Particle&&);
	static void clearParticles();

	static void variadic_update(float dt);
	static void draw(sf::RenderTarget& target, Level);

private:
	static std::list<Particle> mParticles;
};

namespace Particles
{
	const ParticleManager::Particle Cloud_Puff {
		ParticleManager::Level_UnderAir, 10.f, 0, 0, sf::Color(179,179,179,179),
		sf::FloatRect(100,100,200,200), sf::Vector2f(), sf::Vector2f(0, 500)
	};
	const ParticleManager::Particle MG_Casing {
		ParticleManager::Level_UnderAir, 3.5f, 0, 0, sf::Color(255,255,96),
		sf::FloatRect(0,0,4,12), sf::Vector2f(), sf::Vector2f()
	};
	const ParticleManager::Particle HMG_Casing {
		ParticleManager::Level_UnderAir, 5.5f, 0, 0, sf::Color(179,179,0),
		sf::FloatRect(4,0,8,24), sf::Vector2f(), sf::Vector2f()
	};
}

