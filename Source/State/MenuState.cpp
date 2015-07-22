#include "MenuState.hpp"

MenuState::MenuState()
{
}

void MenuState::init()
{
}

void MenuState::handle_event(sf::Event& ev)
{
	if (!mMenuPanes.empty())
		mMenuPanes.front()->handleEvent(ev);
}
void MenuState::fixed_update(float dt)
{
	for (auto it = mMenuPanes.begin(); it != mMenuPanes.end();)
	{
		if ((*it)->getState() == MenuPane::Closed)
		{
			delete *it;
			it = mMenuPanes.erase(it);
		}
		else
			++it;
	}

	if (mMenuPanes.empty())
		getStateManager().removeState<MenuState>();
}
void MenuState::variadic_update(float dt)
{
	for (auto& pane : mMenuPanes)
		pane->update(dt);
}
void MenuState::draw(sf::RenderTarget& target)
{
}
void MenuState::drawUI(sf::RenderTarget& target)
{
	for (auto& pane : mMenuPanes)
		pane->draw(target);
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
	if (!mMenuPanes.empty())
		mMenuPanes.front()->setState(MenuPane::Shading);

	mMenuPanes.push_front(pane);
	pane->setState(MenuPane::Opening);

	pane->mMenu = this;
}

MenuPane* MenuState::popPane()
{
	if (mMenuPanes.empty())
		return nullptr;

	auto* ret = mMenuPanes.front();
	mMenuPanes.pop_front();

	ret->setState(MenuPane::Closing);
	if (!mMenuPanes.empty())
	{
		auto* front = mMenuPanes.front();
		if (front->getState() == MenuPane::Shaded || front->getState() == MenuPane::Shading)
			front->setState(MenuPane::Unshading);
	}

	mMenuPanes.push_back(ret);

	return ret;
}

