#pragma once

namespace sf { struct Vector2f; }

class Entity
{
public:
	enum Team
	{
		Team_Player,
		Team_Enemy,
		Team_Neutral
	};

	const sf::Vector2f& getPosition() const = 0;
	float getRadius() const = 0;
	Team getTeam() const = 0;
};
