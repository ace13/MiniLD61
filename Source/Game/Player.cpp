#include "Player.hpp"

#include <FX/Particles.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

#include <random>

sf::Texture playerTex;

Player::Player() : 
	mHealth(100), mMaxHealth(100), mCurWeapon(nullptr)
{
	playerTex.loadFromFile("Resources/Player.png");

	mPosition = sf::Vector2f(100, 250);
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
	static float asdf = 1;

	asdf -= dt;
	if (asdf <= 0)
	{
		auto& man = ParticleManager::getSingleton();
		std::random_device rd;

		std::uniform_real_distribution<float> dist(-1, 1);

		auto p = Particles::Player_Casing;
		p.Position = mPosition - sf::Vector2f(0, playerTex.getSize().y / 2.5f);
		p.Velocity.x = dist(rd) * 50;
		p.Velocity.y = -100;
		p.Rotation = dist(rd) * 5;
		
		man.addParticle(std::move(p));
		asdf = 0.1;
	}
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

