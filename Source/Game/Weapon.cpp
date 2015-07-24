#include "Weapon.hpp"

#include <FX/Particles.hpp>

#include <random>
#include <cmath>

Weapon::Weapon() :
	mFiring(false), mLevel(1), mFireAng(M_PI / -2.f),
	mFireRate(-1), mCooldown(0)
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

void Weapon::onLevel()
{
}

void Weapon::setFireRate(float rate)
{
	mFireRate = rate;
}

using namespace Weapons;


void Machinegun::fire()
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
}
void Machinegun::onLevel()
{
	setFireRate(1.f / (4 + getLevel() * 2));
}
void HeavyMachinegun::fire()
{
	std::random_device rd;
	std::uniform_real_distribution<float> dist(-1, 1);

	float angDiff = dist(rd) * (M_PI / 12.f);
	auto p = Particles::HMG_Casing;
	p.Position = getFirePos();
	p.Velocity = sf::Vector2f(std::cos(getFireDir() + angDiff), std::sin(getFireDir() + angDiff)) * 300.f;
	p.Rotation = dist(rd) * 8.f;

	ParticleManager::addParticle(std::move(p));
	//BulletManager::linearProjectile();
}
void HeavyMachinegun::onLevel()
{
	setFireRate(1.f / (1 + getLevel()));
}
