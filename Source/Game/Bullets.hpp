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
		sf::Vector2f Position;
		float Angle, Speed;
		sf::Color Color;
		sf::FloatRect Rect;
	};

	struct SeekingProjectile
	{

	};

	struct LinearBeam
	{

	};

	static void fixed_update(float dt);
	static void variadic_update(float dt);
	static void draw(sf::RenderTarget& target);

	static void linearProjectile(LinearProjectile&& proj);
	static void seekingProjectile(SeekingProjectile&& proj);
	static void linearBeam(LinearBeam&& beam);

private:


};
