#pragma once

#include <SFML/System/Vector2.hpp>

#include <string>

namespace sf { class RenderTarget; }

class Weapon
{
public:
	Weapon();
	virtual ~Weapon();

	virtual std::string getName() const = 0;
	virtual std::string getSprite() const = 0;

	virtual void fixed_update(float dt) = 0;
	void drawUI(sf::RenderTarget& target);
	
	int getLevel() const;
	void setLevel(int level);

	void setFireDir(float ang);
	float getFireDir() const;

	void setFirePos(const sf::Vector2f& firePos);
	const sf::Vector2f& getFirePos() const;

protected:
	virtual void onLevel();

private:
	int mLevel;
	float mFireAng;
	sf::Vector2f mFirePos;
};

namespace Weapons
{
	class Machinegun : public Weapon
	{
	public:
		Machinegun();

		std::string getName() const { return "Machinegun"; }
		std::string getSprite() const { return "Machinegun.png"; }

		virtual void fixed_update(float dt);

	protected:
		virtual void onLevel();

	private:
		float mFireRate, mCooldown;
	};
}

