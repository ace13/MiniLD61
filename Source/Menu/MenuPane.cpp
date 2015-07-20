#include "MenuPane.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

const uint8_t SHADED_ALPHA = 97;
const float SHADED_OFFSET  = -25;
const uint8_t OPENED_ALPHA = 255;
const float OPENED_OFFSET  = 64;
const uint8_t CLOSED_ALPHA = 0;
const float CLOSED_OFFSET  = 128;

MenuPane::MenuPane() :
	mOffset(new Easers::Bounce), mAlpha(new Easers::Cubic), mState(Closed)
{
}

MenuPane::~MenuPane()
{
}

void MenuPane::draw(sf::RenderTarget&)
{
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
			mState = Opened;
		else if (mState == Closing)
			mState = Closed;
	}
}

void MenuPane::setState(State s)
{
	mState = s;

	switch(mState)
	{
	case Shading:
		mOffset.setFunction(new Easers::Cubic);
		mOffset.setType(Easer::Out);

		mAlpha.start(1, OPENED_ALPHA, SHADED_ALPHA);
		mOffset.start(1, OPENED_OFFSET, SHADED_OFFSET);
		break;

	case Shaded:
		mAlpha.start(0, SHADED_ALPHA, SHADED_ALPHA);
		mOffset.start(0, SHADED_OFFSET, SHADED_OFFSET);
		break;

	case Unshading:
		mOffset.setType(Easer::In);

		mAlpha.start(1, SHADED_ALPHA, OPENED_ALPHA);
		mOffset.start(1, SHADED_OFFSET, OPENED_OFFSET);
		break;

	case Closing:
		mOffset.setFunction(new Easers::Exponential);

		mAlpha.start(1, OPENED_ALPHA, CLOSED_ALPHA);
		mOffset.start(1, OPENED_OFFSET, CLOSED_OFFSET);
		break;

	case Closed:
		mAlpha.start(0, CLOSED_ALPHA, CLOSED_ALPHA);
		mOffset.start(0, CLOSED_OFFSET, CLOSED_OFFSET);
		break;

	case Opening:
		mOffset.setFunction(new Easers::Bounce);

		mAlpha.start(1, CLOSED_ALPHA, OPENED_ALPHA);
		mOffset.start(1, -CLOSED_OFFSET, OPENED_OFFSET);
		break;

	case Opened:
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



