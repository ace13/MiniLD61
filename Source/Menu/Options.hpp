#pragma once

#include "MenuPane.hpp"

#include <SFML/Graphics/Text.hpp>
#include <list>

class OptionsPane : public MenuPane
{
public:
	OptionsPane();

	void draw(sf::RenderTarget&);
	void handleEvent(sf::Event&);

	std::string getName() const { return "Options"; }

private:
	void back();

	char mSelection;
	std::list<sf::Text> mEntries;
};
