#include "Options.hpp"

#include <State/MenuState.hpp>
#include <Util/Font.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

OptionsPane::OptionsPane()
{
	mEntries = {
		sf::Text("[ I Am an Option ]", sf::getDefaultFont(), 18U),
		sf::Text("[ Option too ]", sf::getDefaultFont(), 18U),
		sf::Text("<< Back", sf::getDefaultFont(), 18U)
	};

	setEntryCount(mEntries.size());

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
		if (i == getSelection() + 1) // Increment already happened
			base = sf::Color::Yellow;
		entry.setColor(base * sf::Color(255,255,255, getAlpha()));
		target.draw(entry);
	}
}
void OptionsPane::handleEvent(sf::Event& ev)
{
	MenuPane::handleEvent(ev);
	const auto checkSel = [this]() {
		if (getSelection() == 2)
			back();
	};

	if (ev.type == sf::Event::KeyPressed)
	{
		if (ev.key.code == sf::Keyboard::Return)
			checkSel();
		else if (ev.key.code == sf::Keyboard::Escape)
			back();
	}
	else if (ev.type == sf::Event::JoystickButtonPressed)
	{
		if (ev.joystickButton.button == 0)
			checkSel();
		else if (ev.joystickButton.button == 1)
			back();
	}
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
void OptionsPane::back()
{
	std::cout << "[MM] Close Options" << std::endl;
	getMenuState().popPane();
}

