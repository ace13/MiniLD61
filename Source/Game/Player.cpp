#include "Player.hpp"

#include <FX/Particles.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <random>

sf::Texture playerTex;

Player::Player() :
	mHealth(100), mMaxHealth(100), mCurWeapon(nullptr)
{
	playerTex.loadFromFile("Resources/Player.png");

	mPosition = sf::Vector2f(100, 250);

	mWeapons.push_back(new Weapons::Machinegun);
	mWeapons.push_back(new Weapons::HeavyMachinegun);

	for (auto& w : mWeapons)
		w->init();

	mCurWeapon = mWeapons.front();
}

Player::~Player()
{
	for (auto& w : mWeapons)
		delete w;
}

void Player::handleEvent(sf::Event& ev)
{
	if (ev.type == sf::Event::KeyPressed)
	{
		if (ev.key.code == sf::Keyboard::Tab)
		{
			bool found = false;
			auto lastWeap = mCurWeapon;
			mCurWeapon = nullptr;
			for (auto& w : mWeapons)
			{
				if (w == lastWeap)
					found = true;
				else if (found)
				{
					mCurWeapon = w;
					break;
				}
			}

			if (!mCurWeapon)
				mCurWeapon = mWeapons.front();

			std::cout << "[WP] " << mCurWeapon->getName() << std::endl;

			lastWeap->setFiring(false);
			mCurWeapon->setFiring(true);
		}
		else if (ev.key.code >= sf::Keyboard::Num1 && ev.key.code <= sf::Keyboard::Num9)
		{
			int level = ev.key.code - sf::Keyboard::Num0;
			mCurWeapon->setLevel(level);
		}
	}
}
void Player::fixed_update(float dt)
{
	mCurWeapon->setFirePos(mPosition - sf::Vector2f(0, 100));

	for(auto& w : mWeapons)
		w->fixed_update(dt);
}
void Player::variadic_update(float dt)
{

}
void Player::draw(sf::RenderTarget& target)
{
	sf::Sprite player(playerTex);
	player.setOrigin((sf::Vector2f)playerTex.getSize() / 2.f);
	player.setPosition(mPosition);

	target.draw(player);
}
void Player::drawUI(sf::RenderTarget& target)
{

}

const sf::Vector2f& Player::getPosition() const
{
	return mPosition;
}

