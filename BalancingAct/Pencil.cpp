#include "Pencil.hpp"

Pencil::Pencil(const double& m, const double& l, const double& t, const sf::Vector2f& anchorpos)
{
	length = l;
	mass = m;
	theta = t;
	anchor = anchorpos;
	rect.setSize(sf::Vector2f(30, -length*1000));	//length is in meters so this converts to one pixel per mm
	rect.setPosition(anchor);
	rect.setFillColor(sf::Color::Red);
	rect.setOrigin(sf::Vector2f(15, 0));

	anchorvis.setRadius(10);
	anchorvis.setOrigin(sf::Vector2f(anchorvis.getRadius(), anchorvis.getRadius()));
	anchorvis.setPosition(rect.getOrigin()+rect.getPosition());
	anchorvis.setFillColor(sf::Color::Cyan);
}

void Pencil::update(const double& dt)
{
	alpha += (9.8/length/2)*sin(theta);
	omega += alpha*dt;
	theta += omega*dt*.9;
	alpha = 0;

	rect.setRotation(theta * 180/3.14);

	COM = sf::Vector2f(sin(theta)*length, cos(theta)*length);
}

void Pencil::draw(sf::RenderWindow& window)
{
	window.draw(rect);
	window.draw(anchorvis);
}

void Pencil::applyTorque(const double& force, const double& dist)
{

}

void Pencil::findNaturalTorque()
{

}