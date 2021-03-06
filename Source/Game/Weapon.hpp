#pragma once

#include <SFML/System/Vector2.hpp>

#include <string>

namespace sf { class RenderTarget; }
class Entity;

class Weapon
{
public:
	Weapon();
	virtual ~Weapon();

	void init();

	virtual std::string getName() const = 0;
	virtual std::string getSprite() const = 0;

	virtual void fixed_update(float dt);
	void drawUI(sf::RenderTarget& target);

	void setFiring(bool f);

	int getLevel() const;
	void setLevel(int level);

	void setFireDir(float ang);
	float getFireDir() const;

	void setFirePos(const sf::Vector2f& firePos);
	const sf::Vector2f& getFirePos() const;

	void setOwner(Entity* ent);

protected:
	virtual void onLevel();
	virtual void fire() = 0;

	Entity* getOwner() const;
	void setFireRate(float rate);

private:
	Entity* mOwner;
	bool mFiring;
	int mLevel;
	float mFireAng, mFireRate, mCooldown;
	sf::Vector2f mFirePos;
};

namespace Weapons
{
	class Machinegun : public Weapon
	{
	public:
		std::string getName() const { return "Machinegun"; }
		std::string getSprite() const { return "Weapon/MG.png"; }

	protected:
		virtual void onLevel();
		virtual void fire();

	private:
		bool mFire;
	};

	class HeavyMachinegun : public Weapon
	{
	public:
		std::string getName() const { return "Heavy Machinegun"; }
		std::string getSprite() const { return "Weapon/HMG.png"; }

	protected:
		virtual void onLevel();
		virtual void fire();
	};

	class Missiles : public Weapon
	{
	public:
		std::string getName() const { return "Missiles"; }
		std::string getSprite() const { return "Weapon/Missiles.png"; }

	protected:
		virtual void onLevel();
		virtual void fire();
	};
}
