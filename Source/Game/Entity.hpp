#pragma once

#include <SFML/System/Vector2.hpp>

class Entity
{
public:
	enum Team
	{
		Team_Player,
		Team_Enemy,
		Team_Neutral
	};

	virtual const sf::Vector2f& getPosition() const = 0;
	virtual float getRadius() const = 0;
	virtual Team getTeam() const = 0;
};
