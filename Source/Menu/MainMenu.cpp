#include "MainMenu.hpp"
#include "Options.hpp"

#include <State/MenuState.hpp>
#include <Util/Font.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

MainMenuPane::MainMenuPane() :
	mSelection(-1)
{
	mEntries = {
		sf::Text("New Game >", sf::getDefaultFont(), 18U),
		sf::Text("Options >", sf::getDefaultFont(), 18U),
		sf::Text("Quit >", sf::getDefaultFont(), 18U)
	};

	if (false) // hasSaveGame())
		mEntries.emplace(mEntries.begin(), "Continue Game >", sf::getDefaultFont(), 18U);

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
		sf::Color base = sf::Color::White;
		if (i == mSelection + 1) // Increment already happened
			base = sf::Color::Yellow;
		entry.setColor(base * sf::Color(255,255,255, getAlpha()));
		target.draw(entry);
	}
}
void MainMenuPane::handleEvent(sf::Event& ev)
{
	if (ev.type == sf::Event::KeyPressed)
	{
		if (ev.key.code == sf::Keyboard::Up || ev.key.code == sf::Keyboard::W)
		{
			if (--mSelection < 0)
				mSelection = mEntries.size() - 1;
		}
		else if (ev.key.code == sf::Keyboard::Down || ev.key.code == sf::Keyboard::S)
		{
			if (++mSelection >= mEntries.size())
				mSelection = 0;
		}
		else if (ev.key.code == sf::Keyboard::Return)
		{
			int offset = mEntries.size() == 4 ? 0 : 1;
			if (mSelection+offset == 0)
				newGame(true);
			else if (mSelection+offset == 1)
				newGame(false);
			else if (mSelection+offset == 2)
				options();
			else if (mSelection+offset == 3)
				quit();
		}
	}
}

void MainMenuPane::newGame(bool cont)
{
	std::cout << "[MM] Enter Game" << std::endl;
}
void MainMenuPane::options()
{
	std::cout << "[MM] Enter Options" << std::endl;
	getMenuState().pushPane(new OptionsPane());
}
void MainMenuPane::scoreboard()
{
	std::cout << "[MM] Enter Options" << std::endl;
}
void MainMenuPane::quit()
{
	std::cout << "[MM] Quit Game" << std::endl;
	getMenuState().popPane();
}

