#pragma once

#include "State/StateManager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class Application
{
public:
	Application(int argc, char** argv);
	~Application();

	void run();

private:
	StateManager mState;
	sf::RenderWindow mWindow;
};

