#ifndef BROWN_MOTION_H__
#define BROWN_MOTION_H__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

class Particle
{
private:
	double radius;
	double mass;
	double rx;
	double ry;
	double vx;
	double vy;
	const sf::Color &color;
	int collisionCount;

public:

	Particle()
		: radius(0.02), mass(0.01), rx(0), ry(0), vx(0.002), vy(0.002), color(sf::Color::Green), collisionCount(0) {}
	Particle(double r_x, double r_y, double v_x, double v_y)
		: radius(0.02), mass(0.1), rx(r_x), ry(r_y), vx(v_x), vy(v_y), color(sf::Color::Green), collisionCount(0) {}
	Particle(double r, double m, double r_x, double r_y, double v_x, double v_y, const sf::Color &Color)
		:radius(r), mass(m), rx(r_x), ry(r_y), vx(v_x), vy(v_y), color(Color), collisionCount(0) {}

	double collidesX() const;
	double collidesY() const;
	double collides(Particle const& b) const;
	double getX() { return rx; }
	double getY() { return ry; }

	void bounceX();
	void bounceY();
	void bounce(Particle& b);

	int getCollisionCount();

	void move(double dt);

	sf::Vector2f getPosition() const { return sf::Vector2f((float)rx, (float)ry); };
	float getRadius() const { return (float)radius; }

	sf::Color getColor() { return this->color; }


};

#endif // !BROWN_MOTION_H__
