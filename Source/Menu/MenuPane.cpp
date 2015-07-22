#include "MenuPane.hpp"

#include <Util/Font.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

const uint8_t SHADED_ALPHA = 97;
const float SHADED_OFFSET  = -25;
const uint8_t OPENED_ALPHA = 255;
const float OPENED_OFFSET  = 64;
const uint8_t CLOSED_ALPHA = 0;
const float CLOSED_OFFSET  = 128;

MenuPane::MenuPane() :
	mOffset(new Easers::Back, Easer::Out), mAlpha(new Easers::Linear), mState(Closed)
{
}

MenuPane::~MenuPane()
{
}

void MenuPane::draw(sf::RenderTarget& target)
{
	sf::Text title(getName(), sf::getDefaultFont(), 30U);

	title.setOrigin(0, 15);
	title.setPosition(getOffset(), 64);
	title.setColor(sf::Color(255,255,255,getAlpha()));

	target.draw(title);
}
void MenuPane::handleEvent(sf::Event&)
{

}
void MenuPane::update(float dt)
{
	mOffset.update(dt);
	mAlpha.update(dt);

	if (mOffset.end())
	{
		if (mState == Shading)
			mState = Shaded;
		else if (mState == Unshading || mState == Opening)
			mState = Open;
		else if (mState == Closing)
			mState = Closed;
	}
}

void MenuPane::setState(State s)
{
	const float ALPHA_DELAY = 0.5;
	const float OFFSET_DELAY = 1;

	mState = s;

	switch(mState)
	{
	case Shading:
		mOffset.setFunction(new Easers::Cubic);
		mOffset.setType(Easer::Out);

		mAlpha.start(ALPHA_DELAY, OPENED_ALPHA, SHADED_ALPHA);
		mOffset.start(OFFSET_DELAY, OPENED_OFFSET, SHADED_OFFSET);
		break;

	case Shaded:
		mAlpha.start(0, SHADED_ALPHA, SHADED_ALPHA);
		mOffset.start(0, SHADED_OFFSET, SHADED_OFFSET);
		break;

	case Unshading:
		mOffset.setType(Easer::In);

		mAlpha.start(ALPHA_DELAY, SHADED_ALPHA, OPENED_ALPHA);
		mOffset.start(OFFSET_DELAY, SHADED_OFFSET, OPENED_OFFSET);
		break;

	case Closing:
		mOffset.setFunction(new Easers::Exponential);

		mAlpha.start(ALPHA_DELAY, OPENED_ALPHA, CLOSED_ALPHA);
		mOffset.start(OFFSET_DELAY, OPENED_OFFSET, CLOSED_OFFSET);
		break;

	case Closed:
		mAlpha.start(0, CLOSED_ALPHA, CLOSED_ALPHA);
		mOffset.start(0, CLOSED_OFFSET, CLOSED_OFFSET);
		break;

	case Opening:
		mOffset.setFunction(new Easers::Back);

		mAlpha.start(ALPHA_DELAY, CLOSED_ALPHA, OPENED_ALPHA);
		mOffset.start(OFFSET_DELAY, -CLOSED_OFFSET, OPENED_OFFSET);
		break;

	case Open:
		mAlpha.start(0, OPENED_ALPHA, OPENED_ALPHA);
		mOffset.start(0, OPENED_OFFSET, OPENED_OFFSET);
		break;
	}
}
MenuPane::State MenuPane::getState() const
{
	return mState;
}

float MenuPane::getOffset() const
{
	return *mOffset;
}
float MenuPane::getAlpha() const
{
	return *mAlpha;
}



