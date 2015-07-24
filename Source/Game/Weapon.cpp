#include "Weapon.hpp"

#include <FX/Particles.hpp>

#include <random>
#include <cmath>

Weapon::Weapon() :
	mLevel(1), mFireAng(M_PI / -2.f)
{
}

Weapon::~Weapon()
{
}

void Weapon::drawUI(sf::RenderTarget& target)
{
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

void Weapon::onLevel()
{
}

using namespace Weapons;

Machinegun::Machinegun() :
	mFireRate(0), mCooldown(0)
{
	onLevel();
}

void Machinegun::fixed_update(float dt)
{
	mCooldown -= dt;
	if (mCooldown <= 0)
	{
		std::random_device rd;
		std::uniform_real_distribution<float> dist(-1, 1);

		float angDiff = dist(rd) * (M_PI / 8.f);
		auto p = Particles::MG_Casing;
		p.Position = getFirePos();
		p.Velocity = sf::Vector2f(std::cos(getFireDir() + angDiff), std::sin(getFireDir() + angDiff)) * 200.f;
		p.Rotation = dist(rd) * 5.f;

		ParticleManager::addParticle(std::move(p));
		//BulletManager::linearProjectile();

		mCooldown = mFireRate;
	}
}

void Machinegun::onLevel()
{
	mFireRate = 1.f / (getLevel() * 5);
}
