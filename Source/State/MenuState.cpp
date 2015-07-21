#include "MenuState.hpp"

void MenuState::init()
{
}

void MenuState::handle_event(sf::Event& ev)
{
}
void MenuState::fixed_update(float dt)
{
}
void MenuState::variadic_update(float dt)
{
	// for (auto& pane : mPanes)
	// 	pane->update(dt);
}
void MenuState::draw(sf::RenderTarget& target)
{
}
void MenuState::drawUI(sf::RenderTarget& target)
{
	// for (auto& pane : mPanes)
	// 	pane->draw(target);
}

// Open Pane:
// - Current top pane -> set state (shading)
// - Set New top pane
// - New top pane -> set state (opening)
//
// Close pane:
// - Current top pane -> set state (closing)
// - Set Current top pane to old pane
// - Current top pane -> set state (unshading)
//
// mPanes = Stack, push new panes on top, iterate from bottom and upwards
void MenuState::pushPane(MenuPane* pane)
{

}

MenuPane* MenuState::popPane()
{

}

