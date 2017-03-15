#include "Pencil.hpp"

Pencil::Pencil(const double& m, const double& l, const double& t, const sf::Vector2f& anchorpos)
{
	length = l*1000;	//converting to 1 mm/px (1000mm in m)
	mass = m;
	theta = t;

	rect.setSize(sf::Vector2f(30, -length));
	rect.setPosition(anchorpos);
	rect.setFillColor(sf::Color::Red);
	rect.setOrigin(sf::Vector2f(15, 0));

	acceleration = sf::Vector2f(0, 0);
	velocity = sf::Vector2f(0, 0);
	position = rect.getOrigin() + rect.getPosition();

	anchorvis.setRadius(10);
	anchorvis.setOrigin(sf::Vector2f(anchorvis.getRadius(), anchorvis.getRadius()));
	anchorvis.setPosition(position);
	anchorvis.setFillColor(sf::Color::Cyan);
	gravity = 9.81 * 1000; //converting to mm/m
}

void Pencil::update(const double& dt)
{
	

	COM = sf::Vector2f(sin(theta)*length, cos(theta)*length);

	rect.setPosition(position);
	anchorvis.setPosition(rect.getOrigin() + rect.getPosition());

	
	//anchor movement
	sf::Vector2f g(0, gravity);
	sf::Vector2f A = acceleration - g;
	double B = atan(A.x / A.y);
	double magA = sqrt(A.x*A.x + A.y*A.y);
	double A1 = magA*cos(alpha - B);
	alpha = 0;
	alpha += -1 * A1 / length * dt;
	std::cout << "B: " << B << ", " << alpha << std::endl;
	alpha += (gravity / length)*sin(theta);

	omega += alpha*dt;
	theta += omega*dt;
	alpha = 0;

	rect.setRotation(theta * 180 / 3.14);
}

void Pencil::draw(sf::RenderWindow& window)
{
	window.draw(rect);
	window.draw(anchorvis);
}

void Pencil::updateAnchor(const sf::Vector2f& pos, const sf::Vector2f& vel, const sf::Vector2f& acc)
{
	position = pos;
	velocity = vel;
	acceleration = acc;
}

void Pencil::applyTorque(const double& force, const double& dist)
{

}

void Pencil::findNaturalTorque()
{

}