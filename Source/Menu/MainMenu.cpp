#include "MainMenu.hpp"
#include "Options.hpp"

#include <State/MenuState.hpp>
#include <Util/Font.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

MainMenuPane::MainMenuPane()
{
	mEntries = {
		sf::Text("New Game >", sf::getDefaultFont(), 18U),
		sf::Text("Options >", sf::getDefaultFont(), 18U),
		sf::Text("Quit >", sf::getDefaultFont(), 18U)
	};

	if (false) // hasSaveGame())
		mEntries.emplace(mEntries.begin(), "Continue Game >", sf::getDefaultFont(), 18U);

	setEntryCount(mEntries.size());

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
		if (i == getSelection() + 1) // Increment already happened
			base = sf::Color::Yellow;
		entry.setColor(base * sf::Color(255,255,255, getAlpha()));
		target.draw(entry);
	}
}
void MainMenuPane::handleEvent(sf::Event& ev)
{
	MenuPane::handleEvent(ev);
	const auto checkSel = [this]() {
		char realSel = getSelection() + (mEntries.size() == 4 ? 0 : 1);
		switch (realSel)
		{
			case 0:
				newGame(true); break;
			case 1:
				newGame(false); break;
			case 2:
				options(); break;
			case 3:
				quit(); break;
		}
	};

	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Return)
		checkSel();
	else if (ev.type == sf::Event::JoystickButtonPressed && ev.joystickButton.button == 0)
		checkSel();
	else if (ev.type == sf::Event::MouseMoved)
	{
		sf::Vector2f pos(ev.mouseMove.x, ev.mouseMove.y);

		char sel = -1;
		for (auto& entry : mEntries)
			if (++sel >= 0 && entry.getGlobalBounds().contains(pos))
			{
				setSelection(sel);
				break;
			}
	}
	else if (ev.type == sf::Event::MouseButtonPressed)
	{
		if (ev.mouseButton.button != sf::Mouse::Button::Left)
			return;

		sf::Vector2f pos(ev.mouseButton.x, ev.mouseButton.y);

		char sel = -1;
		for (auto& entry : mEntries)
			if (++sel >= 0 && entry.getGlobalBounds().contains(pos))
			{
				setSelection(sel);
				checkSel();
				break;
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

