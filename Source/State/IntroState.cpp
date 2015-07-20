#include "IntroState.hpp"
#include "MenuState.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

IntroState::IntroState() :
	mTime(0), mAlphaEaser(new Easers::Quadratic), mScaleEaser(new Easers::Quintic), mRotationEaser(new Easers::Linear)
{
	mAlphaEaser.start(2, 128, 255);
	mScaleEaser.start(4, 0.25, 2);
	mRotationEaser.start(1.5, -45, 22.5); 

	mScaleEaser.update(2);
}

void IntroState::init()
{
	mCardTexture.loadFromFile("Resources/PlayingCard.png");
}

void IntroState::handle_event(sf::Event& ev)
{
}
void IntroState::fixed_update(float dt)
{
	if (mTime > 5)
		getStateManager().changeState<MenuState>();
}
void IntroState::variadic_update(float dt)
{
	mTime += dt;

	mAlphaEaser.update(dt);
	mScaleEaser.update(dt);
	mRotationEaser.update(dt);

	if (mRotationEaser.end())
	{
		mRotationEaser.setType(Easer::Out);
		mRotationEaser.setFunction(new Easers::Quadratic);
		mRotationEaser.start(10, 22.5, 360);
	}
}
void IntroState::draw(sf::RenderTarget& target)
{
	// Draw intro scene
	sf::Sprite playingCard(mCardTexture);
	
	playingCard.setOrigin((sf::Vector2f)mCardTexture.getSize() / 2.f);
	playingCard.setPosition((sf::Vector2f)target.getSize() / 2.f);

	float firstScale = std::min(1.f, *mScaleEaser);
	playingCard.setScale(firstScale, firstScale);
	playingCard.setRotation(*mRotationEaser);
	playingCard.setColor(sf::Color::White * sf::Color(255,255,255,*mAlphaEaser));

	if (*mScaleEaser > 1)
	{
		sf::Sprite secondCard(mCardTexture);

		secondCard.setOrigin((sf::Vector2f)mCardTexture.getSize() / 2.f);
		secondCard.setPosition((sf::Vector2f)target.getSize() / 2.f);

		secondCard.setScale(*mScaleEaser, *mScaleEaser);
		secondCard.setRotation(*mRotationEaser);
		secondCard.setColor(sf::Color::White * sf::Color(255,255,255,255 * (2-*mScaleEaser)));

		target.draw(secondCard);
	}

	target.draw(playingCard);
}

