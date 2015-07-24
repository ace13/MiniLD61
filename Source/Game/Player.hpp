#pragma once

#include "Weapon.hpp"
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

	Weapon* mCurWeapon;
	std::list<Weapon*> mWeapons;
};

