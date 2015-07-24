#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>

class ParticleManager
{
public:
	class Emitter
	{
	};

	struct Particle
	{
		enum Level
		{
			// Level_UnderWater, // Would be invisible, so don't use it
			Level_OverWater,
			Level_OverGround,
			Level_OverAir,

			Level_MAX
		} Height;
		float Life;
		sf::Color Color;
		sf::Texture& Texture;
		sf::Vector2f Velocity;
	};

	static ParticleManager& getSingleton();

	void addParticle(const Particle&);
	void addParticle(Particle&&);

	void clearParticles();

	void variadic_update(float dt);
	void draw(sf::RenderTarget& target, Particle::Level);

private:
	std::vector<Particle> mParticles;
};
