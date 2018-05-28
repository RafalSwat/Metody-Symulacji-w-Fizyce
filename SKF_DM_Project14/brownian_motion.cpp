#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "brown_motion.h"

double Particle::collidesX() const
{
	double dt = -1.;
	if (vx > 0.0)
	{
		dt = (1. - radius - rx) / vx;
	}
	else if (vx < 0.0)
	{
		dt = (radius - rx) / vx;
	}

	return dt;
}

double Particle::collidesY() const
{
	double dt = -1.;
	if (vy > 0.0)
	{
		dt = (1. - radius - ry) / vy;
	}
	else if (vy < 0.0)
	{
		dt = (radius - ry) / vy;
	}

	return dt;
}

double Particle::collides(Particle const& b) const
{
	double const drx = b.rx - rx;
	double const dry = b.ry - ry;

	double const dvx = b.vx - vx;
	double const dvy = b.vy - vy;

	double const dvdr = (dvx * drx + dvy * dry);
	if (dvdr >= 0) return -1.;

	double const dvdv = (dvx*dvx + dvy*dvy);
	double const drdr = (drx*drx + dry*dry);
	double const r = (radius + b.radius);

	double const d = dvdr*dvdr - (dvdv*(drdr - r*r));
	if (d < 0) return -1.;

	double const dt = -((dvdr + std::sqrt(d)) / dvdv);
	return dt;
}


void Particle::bounceX()
{
	vx = -vx;
}

void Particle::bounceY()
{
	vy = -vy;
}

void Particle::bounce(Particle& b)
{
	double const drx = b.rx - rx;
	double const dry = b.ry - ry;

	double const dvx = b.vx - vx;
	double const dvy = b.vy - vy;

	double const dvdr = (dvx * drx + dvy * dry);
	double const r = (radius + b.radius);

	double const J = (2.*mass*b.mass*dvdr) / (r*(mass + b.mass));
	double const Jx = (J*drx) / r;
	double const Jy = (J*dry) / r;

	vx = vx + Jx / mass;
	vy = vy + Jy / mass;

	b.vx = b.vx - Jx / b.mass;
	b.vy = b.vy - Jy / b.mass;

	collisionCount++;
	b.collisionCount++;
}

int Particle::getCollisionCount()
{
	return collisionCount;
}

void Particle::move(double dt)
{
	rx = rx + dt*vx;
	ry = ry + dt*vy;
}
