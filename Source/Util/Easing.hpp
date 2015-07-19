#pragma once

class Easer
{
public:
	struct Function
	{
		virtual float In(float t) const = 0;
		virtual inline float Out(float t) const { return 1 - In(t); }
		inline float InOut(float t) const { return (t < 0.5 ? In(t) : Out(t)); }
	};

	enum Type
	{
		In,
		Out,
		InOut
	};

	template<typename T>
	Easer(Type t);
	~Easer();

	void start(float duration);
	void reset();

	void update(float dt);
	bool end() const;

	float operator*() const;

private:
	Function* mFunc;
	Type mType;
	float mDuration, mCurrent;
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

