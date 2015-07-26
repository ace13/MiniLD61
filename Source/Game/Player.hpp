#pragma once

#include "Entity.hpp"
#include "Weapon.hpp"

#include <list>

namespace sf { struct Event; class RenderTarget; }

class Player : public Entity
{
public:
	Player();
	~Player();

	void handleEvent(sf::Event& ev);
	void fixed_update(float dt);
	void variadic_update(float dt);
	void draw(sf::RenderTarget& target);
	void drawUI(sf::RenderTarget& target);

	const sf::Vector2f& getPosition() const;
	float getRadius() const { return 250.f; }
	Team getTeam() const { return Team_Player; }

private:
	float mHealth, mMaxHealth;
	sf::Vector2f mPosition;

	Weapon* mCurWeapon;
	std::list<Weapon*> mWeapons;
};

