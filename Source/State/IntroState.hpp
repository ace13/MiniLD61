#pragma once

#include "StateManager.hpp"

#include <Util/Easing.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

class IntroState : public IState
{
public:
	IntroState();

	void init();

	void handle_event(sf::Event& ev);
	void fixed_update(float dt);
	void variadic_update(float dt);
	void draw(sf::RenderTarget& target);
	void drawUI(sf::RenderTarget& target);

	std::string getName() const { return "IntroState"; }

private:
	float mTime;
	sf::Texture mCardTexture;

	Easer mAlphaEaser, mScaleEaser, mRotationEaser;
};
