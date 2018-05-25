#ifndef BROWN_MOTION_H__
#define BROWN_MOTION_H__

#include <SFML/Graphics.hpp>
#include <iostream>

class Particle
{
private:
	double radius;
	double mass;
	double rx;
	double ry;
	double vx;
	double vy;

	int collisionCount;

public:
	Particle() : radius(1), mass(1), rx(0), ry(0), vx(0), vy(0), collisionCount(0) {}
	Particle(double r, double m, double r_x, double r_y, double v_x, double v_y) 
		:radius(r), mass(m), rx(r_x), ry(r_y), vx(v_x), vy(v_y), collisionCount(0) {}

	double collidesX() const;
	double collidesY() const;
	double collides(Particle const& b) const;

	void bounceX();
	void bounceY();
	void bounce(Particle& b);

	int getCollisionCount();

	void move(double dt);

	sf::Vector2f getPosition() const { return sf::Vector2f((float)rx, (float)ry); };
	float getRadius() const { return (float)radius; }


};

#endif // !BROWN_MOTION_H__

