#pragma once

namespace sf { class RenderTarget; }

class Enemy
{
public:
	enum Type
	{
		Type_Water,  // Boats, water buildings, etc
		Type_Ground, // Cars, buildings, tanks, etc
		Type_Air,    // Aircraft, baloons, etc

		Type_Shift = 0,
		Type_Mask  = 3 << Type_Shift
	};

	enum Movement
	{
		Movement_Static, // Building, Turret, etc
		Movement_Tank,   // Boat, Car, Tank, etc
		Movement_Hover,  // Helicopter, etc
		Movement_Flight, // Airplane, etc

		Movement_Shift = 2,
		Movement_Mask  = 3 << Movement_Shift
	};

	Enemy(int flags);
	virtual ~Enemy();

	virtual void fixed_update(float dt);
	virtual void variadic_update(float dt);
	virtual void draw(sf::RenderTarget& target);

	float getHealth() const;
	void damage(float dmg);

protected:
	int getFlags() const;
	void setFlags(int flags);

	void setMaxHealth(float health);

private:
	int mFlags;
	float mHealth, mMaxHealth;
};

namespace Enemies
{
	class Airplane : public Enemy
	{
	public:
		enum Flight
		{
			Flight_Arcing, // Flies in an arc
			Flight_Linear, // Flies in a straight line
			Flight_Return, // Flies in a straight line to the edge, then turns around

			Flight_Shift = 4,
			Flight_Mask  = 3 << Flight_Shift
		};

		Airplane();
		~Airplane();

		void fixed_update(float dt);
		void variadic_update(float dt);
		void draw(sf::RenderTarget& target);

	private:
	}
}

