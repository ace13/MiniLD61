#include "Easing.hpp"

#include <algorithm>
#include <cassert>

/*
template<typename T>
Easer::Easer()
{

}
*/
// template<Easers::Linear> Easer::Easer;

void Easer::start(float dur)
{
	assert(dur >= 0 && "Duration must be positive.");

	mDuration = dur;
	mCurrent = 0;
} 

void Easer::reset()
{
	mCurrent = 0;
}

void Easer::update(float dt)
{
	mCurrent = std::min(mDuration, mCurrent + dt);
}

bool Easer::end() const
{
	return mCurrent == mDuration;
}

float Easer::operator*() const
{
	float t = mCurrent / mDuration;

	switch(mType)
	{
	case Type::In:
		return mFunc->In(t);
	case Type::Out:
		return mFunc->Out(t);
	case Type::InOut:
		return mFunc->InOut(t);
	}
}

