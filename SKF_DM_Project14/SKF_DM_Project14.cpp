// SKF_DM_project_14.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <list>
#include <array>
#include "brown_motion.h"
#include "event.h"

std::mt19937 generator(123);
std::uniform_real_distribution<double> dis(0.0, 1.0);

int static const SIZE = 600;
int static const N = 20;

void DrawParticle(Particle const& p, sf::CircleShape & shape, sf::RenderWindow & window)
{
	auto const pos = p.getPosition();
	auto const radius = SIZE * p.getRadius();
	shape.setPosition(pos.x * SIZE - radius, pos.y * SIZE - radius);
	shape.setRadius(SIZE * p.getRadius());
	//shape.setFillColor(p.getColor);
	window.draw(shape);
}

void DrawParticles(std::array<Particle*, N> & particles, sf::CircleShape & shape, sf::RenderWindow & window)
{
	window.clear();
	for (auto & elem : particles)
	{
		DrawParticle(*elem, shape, window);
	}
	window.display();
}

void InsertEvent(Event const& event, std::list<Event>& events)
{
	for (auto eventIt = events.begin(); eventIt != events.end(); eventIt++)
	{
		if (eventIt->getTime() > event.getTime())
		{
			events.insert(eventIt, event);
			return;
		}
	}
	events.push_back(event);
}

void InvalidateRelatedEvents(Event const& executedEvent, std::list<Event> & events)
{
	std::list<Event>::iterator eventIt = events.begin();
	while (eventIt != events.end())
	{
		if (eventIt->containParticle(executedEvent.getA()) || eventIt->containParticle(executedEvent.getB()))
		{
			eventIt = events.erase(eventIt);
		}
		else
		{
			eventIt++;
		}
	}
}

void CheckParticles(Particle* a, Particle* b, std::list<Event>& events)
{
	auto const adtX = a->collidesX();
	auto const adtY = a->collidesY();

	auto const bdtX = b->collidesX();
	auto const bdtY = b->collidesY();

	auto const dtCollide = a->collides(*b);

	if (dtCollide > 0.
		&& dtCollide < adtX
		&& dtCollide < adtY
		&& dtCollide < bdtX
		&& dtCollide < bdtY)
	{
		Event newEvent(Event::TYPE::COLLISION, dtCollide, a, b);
		InsertEvent(newEvent, events);
	}
	else
	{
		auto const aEventType = (adtX < adtY ? Event::TYPE::AXIS_X : Event::TYPE::AXIS_Y);
		Event const aNewEvent(aEventType, adtX < adtY ? adtX : adtY, a, nullptr);
		InsertEvent(aNewEvent, events);

		auto const bEventType = (bdtX < bdtY ? Event::TYPE::AXIS_X : Event::TYPE::AXIS_Y);
		Event const bNewEvent(bEventType, bdtX < bdtY ? bdtX : bdtY, b, nullptr);
		InsertEvent(bNewEvent, events);
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(SIZE, SIZE), "SFML works!");
	sf::CircleShape shape((float)SIZE);
	//shape.setFillColor(sf::Color::Green);
	
	std::array<Particle*, N> particles;
	Particle a(0.1, 0.5, 0.2, 0.2, 0.2, -0.2, sf::Color::Red);
	particles[0] = &a;

	for (size_t i = 1; i < N; ++i)
	{
		double Xrand = dis(generator);
		double Yrand = dis(generator);
		double x = Xrand;
		double y = Yrand;
		particles[i] = new Particle(x, y);
	}


	std::list<Event> events;

	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = i + 1; j < N; ++j)
		{
			auto a = particles[i];
			auto b = particles[j];

			CheckParticles(a, b, events);
		}
	}

	double const basicDt = 0.01;
	double dt = basicDt;
	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		Event executedEvent;
		if (!events.empty())
		{
			if (events.front().getTime() < dt)
			{
				executedEvent = events.front();
				dt = executedEvent.getTime();
			}
			
			for (auto & elem : particles)
			{
				elem->move(dt);
			}
			for (auto & elem : events)
			{
				elem.updateTime(-dt);
			}

			if (executedEvent.getValid())
			{
				executedEvent.execute();
				events.pop_front();

				InvalidateRelatedEvents(executedEvent, events);

				auto a = executedEvent.getA();
				auto b = executedEvent.getB();
				for (auto particle : particles)
				{
					if (a != nullptr && a != particle)
					{
						CheckParticles(a, particle, events);
					}

					if (b != nullptr && b != particle)
					{
						CheckParticles(b, particle, events);
					}
				}
			}
		}
		
		DrawParticles(particles, shape, window);
		dt = basicDt;
	}
	return 0;
}
