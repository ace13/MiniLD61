#pragma once

#include "Weapon.hpp"

#include <SFML/System/Vector2.hpp>

#include <list>

namespace sf { struct Event; class RenderTarget; }

class Player
{
public:
	Player();
	~Player();

	void handleEvent(sf::Event& ev);
	void fixed_update(float dt);
	void variadic_update(float dt);
	void draw(sf::RenderTarget& target);
	void drawUI(sf::RenderTarget& target);

private:
	float mHealth, mMaxHealth;
	sf::Vector2f mPosition;

	Weapon* mCurWeapon;
	std::list<Weapon*> mWeapons;
};

