#include "Pencil.hpp"

Pencil::Pencil(const double& m, const double& l, const double& t, const sf::Vector2f& anchorpos)
{
	length = l*1000;	//converting to 1 mm/px (1000mm in m)
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
	gravity = 9.81 * 1000; //converting to mm/m
}

void Pencil::update(const double& dt)
{
	

	COM = sf::Vector2f(sin(theta)*length, cos(theta)*length);

	rect.setPosition(position);
	anchorvis.setPosition(rect.getPosition() - rect.getOrigin());
	
	//anchor movement
	//std::cout << "accel" << acceleration.x << ", " << acceleration.y << std::endl;

	alpha += cos(theta) / length * acceleration.x * 10000;	//x movement of anchor
	alpha += -1 * sin(theta) / length * acceleration.y * 10000;	//ym moevemnt of anchor
	//alpha += gravity / length * sin(theta);			//gravity's effect on pendulum
	alpha += -1 * 1000000 / (mass * length * length) * omega;

	omega += alpha*dt;
	
	if (omega > 6.28 || omega < -6.28)
	{
		omega = -1 * signbit(omega) * 6.28;
	}
	theta += omega*dt;
	alpha = 0;
	if (theta > 2 * 3.1415)
	{
		theta -= 2 * 3.1415;
	}
	rect.setRotation(theta * 180 / 3.1415);
	massCircle.setPosition(position + sf::Vector2f(cos(theta - 3.1415/2)*length, sin(theta - 3.1415/2)*length));
}

void Pencil::draw(sf::RenderWindow& window)
{
	window.draw(rect);
	window.draw(anchorvis);
	window.draw(massCircle);
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