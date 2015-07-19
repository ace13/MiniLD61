#include "IntroState.hpp"
#include "MenuState.hpp"

void IntroState::init()
{
	mTime = 0;
}

void IntroState::handle_event(sf::Event& ev)
{
}
void IntroState::fixed_update(float dt)
{
	if (mTime > 5)
		getStateManager().changeState<MenuState>();
}
void IntroState::variadic_update(float dt)
{
	mTime += dt;
}
void IntroState::draw(sf::RenderTarget& target)
{
	// Draw intro scene
}

