#include<iostream>
#include <random>
#include <cmath>
#include <fstream>

struct Position
{
	double x;
	double y;

	Position() : x(0), y(0) {}
	Position(double xx, double yy) : x(xx), y(yy) {}

	bool operator==(Position& p)
	{
		return (x == p.x || y == p.y);
	}
};
struct Velocity
{
	double vx;
	double vy;

	Velocity() : vx(0), vy(0) {}
	Velocity(double vxx, double vyy) : vx(vxx), vy(vyy) {}

	bool operator==(Velocity& v)
	{
		return (vx == v.vx && vy == v.vy);
	}
};
struct Box
{
	Position left_down;
	Position right_up;

	Box() : left_down(0,0), right_up(100,100) {}
	Box(Position l_d, Position r_u) : left_down(l_d), right_up(r_u) {}
};
class Disk
{
private:
	double mass;
	double diameter;
	double radius;
	Position position;
	Velocity velocity;

public:
	Disk() : mass(1), diameter(1), radius(1), position(0,0), velocity(0,0) {}
	Disk(double m, double d, double r, Position p, Velocity v) : mass(m), diameter(d), radius(r), velocity(v) {}

};

int main()
{

	system("pause");
	return 0;
}
