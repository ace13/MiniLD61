#include "GameState.hpp"

#include <FX/Particles.hpp>
#include <Game/Player.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

Player p;

GameState::GameState()
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
}
void GameState::draw(sf::RenderTarget& target)
{
	auto& pman = ParticleManager::getSingleton();

	auto view = target.getView();
	view.setCenter(0, 0);
	target.setView(view);

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

