#pragma once

class Easer
{
public:
	struct Function
	{
		virtual inline float In(float t) const = 0;
		virtual inline float Out(float t) const { return 1 - In(t); }
		inline float InOut(float t) const { return (t < 0.5 ? In(t) : Out(t)); }
	};

	template<typename T>
	Easer();
	~Easer();

	float operator*() const;

private:
	Function* mFunc;
};

#define FUNC(NAME, IN) struct NAME : public Easer::Function { \
	inline float In(float t) const { IN; } \
}
#define FUNC2(NAME, IN, OUT) struct NAME : public Easer::Function { \
	inline float In(float t) const { IN; } \
	inline float Out(float t) const { OUT; } \
}

namespace Easers
{
	FUNC(Linear, return t);
	FUNC(Quadratic, return t * t);
	FUNC(Cubic, return t * t * t);
	FUNC(Quintic, return t * t * t * t);

	//FUNC(Circular
	//FUNC(Ellipse
	//FUNC(Exponential
	//FUNC(Sin
	//FUNC2(Back
	//FUNC(Bounce
}

