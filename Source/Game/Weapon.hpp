#pragma once

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

private:
	int mLevel;
};

namespace Weapons
{
	class Machinegun : public Weapon
	{
	public:
		std::string getName() const { return "Machinegun"; }
		std::string getSprite() const { return "Machinegun.png"; }

		virtual void fixed_update(float dt);

	private:
		float mFireRate, mCooldown;
	};
}

