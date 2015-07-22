#include "MainMenu.hpp"

#include <Util/Font.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

MainMenuPane::MainMenuPane() :
	mSelection(-1)
{
	mEntries = {
		sf::Text("New Game >", sf::getDefaultFont(), 18U),
		sf::Text("Options >", sf::getDefaultFont(), 18U),
		sf::Text("Quit >", sf::getDefaultFont(), 18U)
	};

	for (auto& entry : mEntries)
	{
		auto rect = entry.getLocalBounds();
		entry.setOrigin(0, rect.height / 2.f);
	}
}

void MainMenuPane::draw(sf::RenderTarget& target)
{
	MenuPane::draw(target);

	int i = 0;
	for (auto& entry : mEntries)
	{
		entry.setPosition(getOffset(), 128 + (i++) * 30);
		entry.setColor(sf::Color(255,255,255, getAlpha()));
		target.draw(entry);
	}
}
void MainMenuPane::handleEvent(sf::Event& ev)
{

}

void MainMenuPane::newGame(bool cont)
{
}
void MainMenuPane::options()
{
}
void MainMenuPane::scoreboard()
{
}
void MainMenuPane::quit()
{
}

