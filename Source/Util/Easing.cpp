#include "Easing.hpp"

#include <algorithm>
#include <cassert>

Easer::Easer(Function* f, Type t) :
	mType(t), mFunc(f), mCurrent(0), mDuration(0), mStart(0), mEnd(1)
{
}

Easer::~Easer()
{
	delete mFunc;
}

void Easer::setFunction(Function* f)
{
	delete mFunc;
	mFunc = f;
}

void Easer::setType(Type t)
{
	mType = t;
}

void Easer::start(float dur, float start, float end)
{
	assert(dur >= 0 && "Duration must be positive.");

	mDuration = dur;
	mCurrent = 0;
	mStart = start;
	mEnd = end;
} 

void Easer::reset(bool reverse)
{
	mCurrent = 0;

	if (reverse)
	{
		float temp = mStart;
		mStart = mEnd;
		mEnd = temp;
	}
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
		t = mFunc->In(t);
		break;
	case Type::Out:
		t = mFunc->Out(t);
		break;
	case Type::InOut:
		t = mFunc->InOut(t);
		break;
	}

	return mStart + t * (mEnd - mStart);
}

