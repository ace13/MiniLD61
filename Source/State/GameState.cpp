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
}
void GameState::fixed_update(float dt)
{
	p.fixed_update(dt);
}
void GameState::variadic_update(float dt)
{
	ParticleManager::getSingleton().variadic_update(dt);
	p.variadic_update(dt);

	auto vec = mCamera.getCenter();
	vec += (p.getPosition() - vec) * (dt * 2.5f);
	mCamera.setCenter(vec);
}
void GameState::draw(sf::RenderTarget& target)
{
	if (mFirst)
	{
		mCamera = target.getView();
		mFirst = false;
	}

	auto& pman = ParticleManager::getSingleton();

	target.setView(mCamera);

	pman.draw(target, ParticleManager::Level_UnderWater);
	// Draw water entitie

	pman.draw(target, ParticleManager::Level_OverWater);
	pman.draw(target, ParticleManager::Level_UnderGround);
	// Draw ground entities

	pman.draw(target, ParticleManager::Level_OverGround);
	pman.draw(target, ParticleManager::Level_UnderAir);
	// Draw air entities

	// Player always on top
	p.draw(target);
	pman.draw(target, ParticleManager::Level_OverAir);
}
void GameState::drawUI(sf::RenderTarget& target)
{

}

