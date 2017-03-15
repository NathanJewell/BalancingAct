#pragma once

#include <SFML\Graphics.hpp>
#include <math.h>

//Pencil.cpp
/// Class to deal with physics of a uniform rod not dissimilar from a pencil ///

class Pencil
{
public:
	Pencil(const double& mass, const double& length, const double& theta, const sf::Vector2f& anchorpos);

	void update(const double& dt);			//update physics
	void draw(sf::RenderWindow& window);	//draw to screen

	void applyTorque(const double& force, const double& dist);	//apply a torque to the object at the specified distance from COM
	void findNaturalTorque();									//Calculate torque simply from the weight of the object

private:
	double inertiaCOM; //moment of inertia rotating around COM
	double inertiaEND; //moment of inertia rotating around one end

	sf::Vector2f COM; //current position of COM

	double theta;	//angle
	double omega;	//angular velocity
	double alpha;	//angular acceleration

	double length;
	double mass;

	sf::Vector2f anchor;
	sf::RectangleShape rect;
	sf::CircleShape anchorvis;

	std::vector<double> torques;	//torques to be applied to object in the upcoming frame


};