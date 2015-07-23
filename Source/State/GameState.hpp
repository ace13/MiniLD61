#pragma once

#include "StateManager.hpp"

class GameState : public IState
{
public:
	GameState();
	~GameState();

	void init();

	void handle_event(sf::Event& ev);
	void fixed_update(float dt);
	void variadic_update(float dt);
	void draw(sf::RenderTarget& target);
	void drawUI(sf::RenderTarget& target);

	std::string getName() const { return "GameState"; }

private:

};

