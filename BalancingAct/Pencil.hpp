#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <math.h>
#include <cmath>
#include <algorithm>

//Pencil.cpp
/// Class to deal with physics of a uniform rod not dissimilar from a pencil ///
//Algorithms ty https://www.myphysicslab.com/pendulum/moveable-pendulum/moveable-pendulum-en.html

class Pencil
{
public:
	Pencil(const double& mass, const double& length, const double& theta, const sf::Vector2f& anchorpos);

	void update(const double& dt);			//update physics
	void draw(sf::RenderWindow& window);	//draw to screen

	void updateAnchor(const sf::Vector2f& acc);
	bool balancing();

	std::vector<double> getState();	//returns alpha,omega,theta

	double evalQ();					//returns value approximating how good it is right now

	void reset();

private:
	double scale;		//pixels per meter
	double inertiaCOM; //moment of inertia rotating around COM
	double inertiaEND; //moment of inertia rotating around one end

	sf::Vector2f COM; //current position of COM

	double theta;	//angle
	double omega;	//angular velocity
	double alpha;	//angular acceleration

	sf::Vector2f acceleration;
	sf::Vector2f velocity;
	sf::Vector2f position;

	double length;
	double mass;

	sf::RectangleShape rect;
	sf::CircleShape anchorvis;
	sf::CircleShape massCircle;

	std::vector<double> torques;	//torques to be applied to object in the upcoming frame

	double gravity;

	


};