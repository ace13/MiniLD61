#pragma once

#include "MenuPane.hpp"

#include <SFML/Graphics/Text.hpp>
#include <list>

class MainMenuPane : public MenuPane
{
public:
	MainMenuPane();

	void draw(sf::RenderTarget&);
	void handleEvent(sf::Event&);

	std::string getName() const { return "Main Menu"; }

private:
	void newGame(bool cont);
	void options();
	void scoreboard();
	void quit();

	std::list<sf::Text> mEntries;
};
