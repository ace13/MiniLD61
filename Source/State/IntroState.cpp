#include "IntroState.hpp"
#include "MenuState.hpp"

#include <Menu/MainMenu.hpp>
#include <Util/Font.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <SFML/Window/Event.hpp>

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
	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
		mTime = 5;
}
void IntroState::fixed_update(float dt)
{
	if (mTime > 4)
	{
		auto& manager = getStateManager();
		manager.changeState<MenuState>(true);
		static_cast<MenuState*>(manager.getCurrentState())->pushPane(new MainMenuPane);
	}
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

		mAlphaEaser.setType(Easer::Out);
		mAlphaEaser.setFunction(new Easers::Exponential);
		mAlphaEaser.start(4, 255, 0);
	}
}
void IntroState::draw(sf::RenderTarget& target)
{
}
void IntroState::drawUI(sf::RenderTarget& target)
{
	// Draw intro scene
	sf::Sprite playingCard(mCardTexture);
	
	playingCard.setOrigin((sf::Vector2f)mCardTexture.getSize() / 2.f);
	playingCard.setPosition(target.getView().getCenter());

	float firstScale = std::min(1.f, *mScaleEaser);
	playingCard.setScale(firstScale, firstScale);
	playingCard.setRotation(*mRotationEaser);
	playingCard.setColor(sf::Color::White * sf::Color(255,255,255,*mAlphaEaser));

	if (*mScaleEaser > 1)
	{
		sf::Sprite secondCard(mCardTexture);

		secondCard.setOrigin((sf::Vector2f)mCardTexture.getSize() / 2.f);
		secondCard.setPosition(target.getView().getCenter());

		secondCard.setScale(*mScaleEaser, *mScaleEaser);
		secondCard.setRotation(*mRotationEaser);
		secondCard.setColor(sf::Color::White * sf::Color(255,255,255,255 * (2-*mScaleEaser)));

		target.draw(secondCard);
	}

	target.draw(playingCard);

	sf::Text copyroight("An Ananace production", sf::getDefaultFont(), 12U);
	auto rect = copyroight.getLocalBounds();
	copyroight.setOrigin(rect.width / 2.f, rect.height + 5);
	copyroight.setPosition(target.getView().getSize() / 2.f + sf::Vector2f(0.f, target.getView().getSize().y / 2.f));
	target.draw(copyroight);
}

