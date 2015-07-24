#include "Player.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>

Player::Player() : 
	mHealth(100), mMaxHealth(100), mCurWeapon(nullptr)
{
}

Player::~Player()
{
	for (auto& w : mWeapons)
		delete w;
}

void Player::handleEvent(sf::Event& ev)
{

}
void Player::fixed_update(float dt)
{

}
void Player::variadic_update(float dt)
{

}
void Player::draw(sf::RenderTarget& target)
{

}
void Player::drawUI(sf::RenderTarget& target)
{

}

