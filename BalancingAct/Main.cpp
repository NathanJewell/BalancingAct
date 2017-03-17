
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Pencil.hpp"

sf::Vector2f divide(const sf::Vector2f& vec, const double& scalar)
{
	return sf::Vector2f(vec.x / scalar, vec.y / scalar);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1900, 1000), "LAPIZ");
	window.setFramerateLimit(144);
	
	Pencil p = Pencil(10, .2, 3.1415/32, sf::Vector2f(600, 300));
	double dt = 0;	//frametime in seconds
	double lastframe = 0;
	//sf::Vector2f position(800, 500);
	//sf::Vector2f velocity(0, 0);
	sf::Vector2f acceleration(0, 0);
	double speed = 100;
	double t = 0;	//balancing time
	//sf::Mouse::setPosition((sf::Vector2i)mousePosition);
	sf::Clock clock;
	while (window.isOpen())
	{
		dt = clock.getElapsedTime().asSeconds() - lastframe;
		lastframe = clock.getElapsedTime().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			acceleration.x += -1*speed*dt;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			acceleration.x += speed*dt;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			acceleration.y += -1 * speed*dt;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			acceleration.y += speed*dt;
		}
		if (p.balancing())
		{
			t += dt;
		}
		else
		{
			t = 0;
		}
		//std::cout << "High Score:" << t << std::endl;

		/*sf::Vector2f tmpPosition = (sf::Vector2f)sf::Mouse::getPosition(window);
		std::cout << "position " << mousePosition.x << ", " << mousePosition.y << std::endl;
		std::cout << "velocity " << mouseVelocity.x << ", " << mouseVelocity.y << std::endl;
		std::cout << "acceleration " << mouseAcceleration.x << ", " << mouseAcceleration.y << std::endl;
		sf::Vector2f tmpVelocity = (mousePosition - tmpPosition);
		mouseAcceleration = divide((tmpVelocity - mouseVelocity), 1);
		mouseVelocity = divide(tmpVelocity, 1);
		mousePosition = tmpPosition;
		*/
		//std::cout << mouseVelocity.x << ", " << mouseVelocity.y << std::endl;
		window.clear();
		p.updateAnchor(acceleration);
		p.update(dt);
		p.draw(window);
		window.display();

		acceleration = sf::Vector2f(0, 0);
	}

	return 0;
}