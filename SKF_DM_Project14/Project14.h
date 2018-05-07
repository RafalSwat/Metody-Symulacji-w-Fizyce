  #include<iostream>
#include <random>
#include <cmath>

class Coordinates
{
private:
	double x;
	double y;
public:
	Coordinates() : x(0), y(0) {}
	Coordinates(double xx, double yy) : x(xx), y(yy) {}

	bool operator==(Coordinates & p);
	Coordinates operator+(Coordinates & p);
	Coordinates operator-(Coordinates & p);
	Coordinates operator*(double & p);
	Coordinates operator/(double & p);
	double operator*(Coordinates & p);
};

class Box
{
private:
	Coordinates left_down;
	Coordinates right_up;
public:
	Box() : left_down(0, 0), right_up(100, 100) {}
	Box(Coordinates l_d, Coordinates r_u) : left_down(l_d), right_up(r_u) {}
};
class Particle
{
private:
	double mass;
	double diameter;
	double radius;
	Coordinates position;
	Coordinates velocity;

public:
	Particle(): mass(1),  diameter(1), radius(1), position(0, 0), velocity(0, 0) {}
	Particle(double m, double d, double r, Coordinates p, Coordinates v) : mass(m), diameter(d), radius(r), velocity(v) {}

	double collidesX();
	double collidesY();
	double collides(Particle b);
	void bounceX();
	void bounceY();
	void bounce(Particle b);
	int getCollisionCount();

};
