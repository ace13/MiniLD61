#pragma once

#include "State/StateManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

class Application
{
public:
	Application(int argc, char** argv);
	~Application();

	void run();

private:
	StateManager mState;
	sf::RenderWindow mWindow;
	sf::View mGameView, mUIView;
};

