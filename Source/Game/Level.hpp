#pragma once

#include <SFML/Graphics/Color.hpp>

namespace sf { class RenderTarget; }

class Level
{
public:
	enum GroundType
	{
		Ground_Ocean,    // Battleships, small islands
		Ground_Lake,     // Smaller ships, water constructions
		Ground_Plains,   // Greenery, some trees
		Ground_Urban,    // Roads, buildings
		Ground_Military  // Paved ground, buildings, turrets, etc
	};

	struct Ground
	{
		GroundType Type;
		sf::Color Color;
	};

	const Ground& getGround();
	void draw(sf::RenderTarget& target);
};

namespace Grounds
{
	const Level::Ground Ground_Ocean = {
		Level::Ground_Ocean, sf::Color(12,32,97)
	};
	const Level::Ground Ground_Lake = {
		Level::Ground_Lake, sf::Color(42,65,127)
	};
	const Level::Ground Ground_Plains = {
		Level::Ground_Plains, sf::Color(54,220,12)
	};
	const Level::Ground Ground_Urban = {
		Level::Ground_Urban, sf::Color(129,129,129)
	};
	const Level::Ground Ground_Military = {
		Level::Ground_Military, sf::Color(79,79,79)
	};
}

