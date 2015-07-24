#include "GameState.hpp"

#include <FX/Particles.hpp>
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
}
void GameState::handle_event(sf::Event& ev)
{
	p.handleEvent(ev);
}
void GameState::fixed_update(float dt)
{
	p.fixed_update(dt);
}
void GameState::variadic_update(float dt)
{
	ParticleManager::variadic_update(dt);
	p.variadic_update(dt);

	auto vec = mCamera.getCenter();
	vec += ((p.getPosition() - sf::Vector2f(0, 700)) - vec) * (dt * 2.5f);
	mCamera.setCenter(vec);
}
void GameState::draw(sf::RenderTarget& target)
{
	if (mFirst)
	{
		mCamera = target.getView();
		mFirst = false;
	}

	target.setView(mCamera);

	ParticleManager::draw(target, ParticleManager::Level_UnderWater);
	// Draw water entitie

	ParticleManager::draw(target, ParticleManager::Level_OverWater);
	ParticleManager::draw(target, ParticleManager::Level_UnderGround);
	// Draw ground entities

	ParticleManager::draw(target, ParticleManager::Level_OverGround);
	ParticleManager::draw(target, ParticleManager::Level_UnderAir);
	// Draw air entities

	// Player always on top
	p.draw(target);
	ParticleManager::draw(target, ParticleManager::Level_OverAir);
}
void GameState::drawUI(sf::RenderTarget& target)
{
	p.drawUI(target);
}

