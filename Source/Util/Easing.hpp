#pragma once

#include <cmath>

class Easer
{
public:
	struct Function
	{
		virtual ~Function() { }
		virtual float In(float t) const = 0;
		virtual float Out(float t) const = 0;
		inline float InOut(float t) const { return (t < 0.5 ? In(t * 2) * 0.5 : Out(t * 2) * 0.5); }
	};

	enum Type
	{
		In,
		Out,
		InOut
	};

	Easer(Function* f, Type t = In);
	~Easer();

	void setFunction(Function* func);
	void setType(Type t);

	void start(float duration, float startVal = 0, float endVal = 1);
	void reset(bool reverse = false);

	void update(float dt);
	bool end() const;

	float operator*() const;

private:
	Function* mFunc;
	Type mType;
	float mDuration, mCurrent, mStart, mEnd;
};

#define FUNC(NAME, IN, OUT) struct NAME : public Easer::Function { \
	inline float In(float t) const { IN; } \
	inline float Out(float t) const { OUT; } \
}

namespace Easers
{
	FUNC(Linear, return t, return t);
	FUNC(Quadratic, return t * t, return -(t * (t - 2)));
	FUNC(Cubic, return t * t * t, return (t-1) * (t-1) * (t-1) + 1);
	FUNC(Quartic, return t * t * t * t, return (t-1) * (t-1) * (t-1) * (1-(t-1)) + 1);
	FUNC(Quintic, return t * t * t * t * t, return (t-1) * (t-1) * (t-1) * (t-1) * (t-1));

	FUNC(Sine, return std::sin((t-1) * M_PI) + 1, return std::sin(t * M_PI_2));
	FUNC(Circular, return 1 - std::sqrt(1 - (t * t)), return sqrt((2 - t) * t));
	FUNC(Exponential, return t == 0 ? 0 : std::pow(2, 10 * (t - 1)), return t == 1 ? 1 : 1 - std::pow(2, -10 * t));
	FUNC(Elastic, return std::sin(13 * M_PI_2 * t) * std::pow(2, 10 * (t - 1)), return std::sin(-13 * M_PI_2 * (t + 1)) * std::pow(2, -10 * t) + 1);
	FUNC(Back, return t * t * t - t * std::sin(t * M_PI), float f = t-1; return 1 - (f * f * f - f * sin(M_PI * f)));
	FUNC(Bounce, return 1 - Out(1 - t), \
		if (t < 4 / 11.0) return (121.0 * t * t) / 16.0; \
		else if (t < 8 / 11.0) return (363.0/40.0 * t * t) - (99/10.0 * t) + 17.0/5.0; \
		else if (t < 9 / 10.0) return (4356.0/361.0 * t * t) - (35442.0/1805.0 * t) + 16061.0/1805.0; \
		else return (54.0 / 5.0 * t * t) - (513.0/25.0 * t) + 268.0/25.0; \
	);
}

