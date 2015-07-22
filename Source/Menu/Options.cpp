#include "Options.hpp"

#include <State/MenuState.hpp>
#include <Util/Font.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

OptionsPane::OptionsPane() :
	mSelection(-1)
{
	mEntries = {
		sf::Text("[ I Am an Option ]", sf::getDefaultFont(), 18U),
		sf::Text("[ Option too ]", sf::getDefaultFont(), 18U),
		sf::Text("<< Back", sf::getDefaultFont(), 18U)
	};

	for (auto& entry : mEntries)
	{
		auto rect = entry.getLocalBounds();
		entry.setOrigin(0, rect.height / 2.f);
	}
}

void OptionsPane::draw(sf::RenderTarget& target)
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
void OptionsPane::handleEvent(sf::Event& ev)
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
			if (mSelection == 2)
				back();
		}
		else if (ev.key.code == sf::Keyboard::Escape)
			back();
	}
}
void OptionsPane::back()
{
	std::cout << "[MM] Close Options" << std::endl;
	getMenuState().popPane();
}

