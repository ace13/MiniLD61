#pragma once

#include "StateManager.hpp"
#include <Menu/MenuPane.hpp>

#include <SFML/System/Clock.hpp>

#include <list>

class MenuState : public IState
{
public:
	MenuState();
	~MenuState();

	void init();

	void handle_event(sf::Event& ev);
	void fixed_update(float dt);
	void variadic_update(float dt);
	void draw(sf::RenderTarget& target);
	void drawUI(sf::RenderTarget& target);

	std::string getName() const { return "MenuState"; }

	void pushPane(MenuPane* pane);
	MenuPane* popPane();

private:
	std::list<MenuPane*> mMenuPanes;
};
