#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace sf { class RenderTarget; }

class BulletManager
{
public:
	struct LinearProjectile
	{
		// Source entity
		sf::Vector2f Position;
		float Angle, Speed;
		sf::Color Color;
		sf::FloatRect Rect;
		int Trail;
	};

	struct SeekingProjectile
	{
		// Source entity
		sf::Vector2f Position;
		// Target entity
		float Speed;
		sf::Color Color;
		sf::FloatRect Rect;
		sf::FloatRect TrailRect;
		int TrailLength;
	};

	struct LinearBeam
	{
		sf::Vector2f Position;
		float Angle;
		sf::Color Color;
		sf::FloatRect Rect;
	};

	static void fixed_update(float dt);
	static void variadic_update(float dt);
	static void draw(sf::RenderTarget& target);

	static void linearProjectile(LinearProjectile&& proj);
	static void seekingProjectile(SeekingProjectile&& proj);
	static void linearBeam(LinearBeam&& beam);

private:


};
