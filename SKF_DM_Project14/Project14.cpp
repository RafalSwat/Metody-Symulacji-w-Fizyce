#include <iostream>
#include <cmath>
#include "Project14.h"

bool Coordinates::operator==(Coordinates & p)
{
	return (x == p.x || y == p.y);
}
Coordinates Coordinates::operator+(Coordinates & p)
{
	return Coordinates(this->x + p.x, this->y + p.y);
}
Coordinates Coordinates::operator-(Coordinates & p)
{
	return Coordinates(this->x - p.x, this->y - p.y);
}
Coordinates Coordinates::operator*(double & p)
{
	return Coordinates(this->x * p, this->y * p);
}
Coordinates Coordinates::operator/(double & p)
{
	return Coordinates(this->x / p, this->y / p);
}
double Coordinates::operator*(Coordinates & p)
{
	return double(this->x * p.x + this->y * p.y);
}
