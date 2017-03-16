#include "Pencil.hpp"

Pencil::Pencil(const double& m, const double& l, const double& t, const sf::Vector2f& anchorpos)
{
	scale = 200;
	length = l*scale;	//converting to 1 mm/px (1000mm in m)
	mass = m;
	theta = t;

	rect.setSize(sf::Vector2f(16, -length));
	rect.setPosition(anchorpos);
	rect.setFillColor(sf::Color::Red);
	rect.setOrigin(sf::Vector2f(8, 0));

	acceleration = sf::Vector2f(0, 0);
	velocity = sf::Vector2f(0, 0);
	position = rect.getOrigin() + rect.getPosition();

	massCircle.setRadius(20);
	massCircle.setOrigin(massCircle.getRadius(), massCircle.getRadius());
	massCircle.setFillColor(sf::Color::Magenta);

	anchorvis.setRadius(10);
	anchorvis.setOrigin(sf::Vector2f(anchorvis.getRadius(), anchorvis.getRadius()));
	anchorvis.setPosition(position);
	anchorvis.setFillColor(sf::Color::Cyan);
	gravity = 9.81 * scale; //converting to mm/m
}

void Pencil::update(const double& dt)
{
	velocity.x += -1 * velocity.x/32;
	velocity.y += -1 * velocity.y/32;
	velocity += acceleration;
	position += velocity;
	COM = sf::Vector2f(sin(theta)*length, cos(theta)*length);

	rect.setPosition(position);
	anchorvis.setPosition(rect.getPosition() - rect.getOrigin());
	
	//anchor movement
	alpha += -1 * cos(theta) / length * acceleration.x * scale;	//x movement of anchor
	alpha += -1 * sin(theta) / length * acceleration.y * scale;	//ym moevemnt of anchor
	alpha += gravity / length * sin(theta);			//gravity's effect on pendulum
	alpha += -1 * 1000 / (mass * length * length) * omega;

	//std::cout << "acc: " << acceleration.x << ", " << acceleration.y << std::endl;
	omega += alpha*dt;


	theta += omega*dt;
	if (theta > 2 * 3.1415)
	{
		theta -= 2 * 3.1415;
	}

	alpha = 0;

	rect.setRotation(theta * 180 / 3.1415);
	massCircle.setPosition(position + sf::Vector2f(cos(theta - 3.1415/2)*length, sin(theta - 3.1415/2)*length));
}

void Pencil::draw(sf::RenderWindow& window)
{
	window.draw(rect);
	window.draw(anchorvis);
	window.draw(massCircle);
}

bool Pencil::balancing()
{
	if (theta < 0+3.1415/2 || theta > 3.1415+3.1415/2)
	{
		return true;
	}
	return false;
}

void Pencil::updateAnchor(const sf::Vector2f& acc)
{
	acceleration = acc;
}

void Pencil::applyTorque(const double& force, const double& dist)
{

}

void Pencil::findNaturalTorque()
{

}