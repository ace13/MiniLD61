#include "Weapon.hpp"
#include "Entity.hpp"

#include "Bullets.hpp"
#include <FX/Particles.hpp>

#include <random>
#include <cmath>

Weapon::Weapon() :
	mOwner(nullptr), mFiring(false), mLevel(1),
	mFireAng(M_PI / -2.f), mFireRate(-1), mCooldown(0)
{
}

Weapon::~Weapon()
{
}

void Weapon::init()
{
	onLevel();
}

void Weapon::fixed_update(float dt)
{
	if (mFireRate < 0)
		return;

	mCooldown = std::max(0.f, mCooldown - dt);
	if (mCooldown <= 0 && mFiring)
	{
		fire();

		mCooldown = mFireRate;
	}
}

void Weapon::drawUI(sf::RenderTarget& target)
{
}

void Weapon::setFiring(bool f)
{
	mFiring = f;
}

int Weapon::getLevel() const
{
	return mLevel;
}
void Weapon::setLevel(int level)
{
	mLevel = level;
	onLevel();
}

void Weapon::setFireDir(float ang)
{
	mFireAng = ang;
}
float Weapon::getFireDir() const
{
	return mFireAng;
}

void Weapon::setFirePos(const sf::Vector2f& pos)
{
	mFirePos = pos;
}
const sf::Vector2f& Weapon::getFirePos() const
{
	return mFirePos;
}

void Weapon::setOwner(Entity* ent)
{
	mOwner = ent;
}
Entity* Weapon::getOwner() const
{
	return mOwner;
}

void Weapon::onLevel()
{
}

void Weapon::setFireRate(float rate)
{
	mFireRate = rate;
}


/*
 *  Weapons
 */

using namespace Weapons;

void Machinegun::fire()
{
	mFire = !mFire;

	std::random_device rd;
	std::uniform_real_distribution<float> dist(-1, 1);

	float angDiff = dist(rd) * (M_PI / 7.5f);
	auto p = Particles::MG_Casing;
	p.Position = getFirePos() + (mFire ? sf::Vector2f(75, 175) : sf::Vector2f(-75, 175));
	p.Velocity = sf::Vector2f(std::cos(getFireDir() + angDiff), std::sin(getFireDir() + angDiff)) * 100.f;
	p.Rotation = dist(rd) * 5.f;

	BulletManager::linearProjectile({
		getOwner(), p.Position, getFireDir() + angDiff / 15.f, 1200, sf::Color(255,255,170), sf::FloatRect(0,0,4,15), 3
	});
	ParticleManager::addParticle(std::move(p));
}
void Machinegun::onLevel()
{
	setFireRate(1.f / (6 + getLevel() * 3));
}
void HeavyMachinegun::fire()
{
	std::random_device rd;
	std::uniform_real_distribution<float> dist(-1, 1);

	float angDiff = dist(rd) * (M_PI / 12.f);
	auto p = Particles::HMG_Casing;
	p.Position = getFirePos();
	p.Velocity = sf::Vector2f(std::cos(getFireDir() + angDiff), std::sin(getFireDir() + angDiff)) * 200.f;
	p.Rotation = dist(rd) * 8.f;

	BulletManager::linearProjectile({
		getOwner(), p.Position, getFireDir() + angDiff / 10.f, 2400, sf::Color(190,190,0), sf::FloatRect(0,0,10,30), 8
	});
	ParticleManager::addParticle(std::move(p));
}
void HeavyMachinegun::onLevel()
{
	setFireRate(1.f / (1 + getLevel() / 2));
}
void Missiles::fire()
{
	for (bool f = true; f; f=!f)
	{
		BulletManager::seekingProjectile({
			getOwner(), getFirePos() + (f ? sf::Vector2f(75, 175) : sf::Vector2f(-75, 175)),
			nullptr, 200.f, sf::Color::Yellow, sf::FloatRect(0,0,15,50), sf::FloatRect(0,0,10,5), 10
		});
	}
}
void Missiles::onLevel()
{
	setFireRate(1.f / (1 + getLevel() / 4));
}
