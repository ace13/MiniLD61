#include "GameState.hpp"

#include <FX/Particles.hpp>
#include <Game/Bullets.hpp>
#include <Game/Cloud.hpp>
#include <Game/Level.hpp>
#include <Game/Player.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

Player p;

GameState::GameState() :
	mFirst(true)
{
}

GameState::~GameState()
{
}

void GameState::init()
{
	ParticleManager::init();
}
void GameState::handle_event(sf::Event& ev)
{
	p.handleEvent(ev);
}
void GameState::fixed_update(float dt)
{
	BulletManager::fixed_update(dt);
	CloudGenerator::fixed_update(dt);

	p.fixed_update(dt);
}
void GameState::variadic_update(float dt)
{
	ParticleManager::variadic_update(dt);
	BulletManager::variadic_update(dt);
	p.variadic_update(dt);

	auto vec = mCamera.getCenter();
	vec += ((p.getPosition() - sf::Vector2f(0, 1020)) - vec) * (dt * 2.5f);
	mCamera.setCenter(vec);
}
void GameState::draw(sf::RenderTarget& target)
{
	if (mFirst)
	{
		mCamera = target.getView();
		mFirst = false;
	}

	mCamera.setSize(target.getView().getSize());
	target.setView(mCamera);

	target.clear(sf::Color(22,67,126));
	// target.clear(Level::getGround().Color);
	// Level::draw(target);

	ParticleManager::draw(target, ParticleManager::Level_UnderGround);
	// Draw ground entities
	// EntityManager::draw(target, EntityManager::Level_Ground);

	ParticleManager::draw(target, ParticleManager::Level_OverGround);
	ParticleManager::draw(target, ParticleManager::Level_UnderAir);
	// Bullets are between air and ground
	BulletManager::draw(target);

	// Draw air entities
	// EntityManager::draw(target, EntityManager::Level_Air);

	// Player always on top
	p.draw(target);
	ParticleManager::draw(target, ParticleManager::Level_OverAir);
}
void GameState::drawUI(sf::RenderTarget& target)
{
	p.drawUI(target);
}

