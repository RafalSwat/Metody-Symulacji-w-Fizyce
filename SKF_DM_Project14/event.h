#ifndef EVENT_H__
#define EVENT_H__

#include "brown_motion.h"

class Event
{
public:
	enum class TYPE
	{
		COLLISION,
		AXIS_X,
		AXIS_Y,
		NONE,
	};

private:
	TYPE type;
	double time;
	Particle* a;
	Particle* b;
	
	bool valid;

public:
	Event() : type(TYPE::NONE), time(0), valid(false), a(nullptr), b(nullptr) {}
	Event(TYPE type, double time, Particle* a, Particle* b) : type(type), time(time), valid(true), a(a), b(b) {}

	void invalidate() { valid = false; }
	bool getValid() const { return valid; }

	double getTime() const { return time; }
	void updateTime(double dt) { time += dt; }

	Particle* getA() const { return a; }
	Particle* getB() const { return b; }

	bool containParticle(Particle* particle) const { return (a == particle || b == particle); }

	void execute()
	{
		switch (type)
		{
		case Event::TYPE::COLLISION:
			a->bounce(*b);
			break;
		case Event::TYPE::AXIS_X:
			a->bounceX();
			break;
		case Event::TYPE::AXIS_Y:
			a->bounceY();
			break;
		default:
			break;
		}
	}
};

#endif


