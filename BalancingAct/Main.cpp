
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Pencil.hpp"
#include "NN.hpp"

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

	sf::Vector2f acceleration(0, 0);
	double speed = 100;
	double t = 0;	//balancing time

	Net net(3, 1, SIGMOID, SIGMOIDD, SQUAREDERR);
	net.makeHiddenLayer(3);
	net.initialize();

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
		

		net.setInput(p.getState);						//give network the pencil state
		net.feedForward();								//calculate new values
		std::vector<double> output = net.getOutput();	//calculate new acceleration

		window.clear();

		p.updateAnchor(sf::Vector2f((output[0]-.5)*speed, dt));	//pretending like the movement is just like the mouse
		p.update(dt);

		net.backPropogate(p.evalQ());	//evaluate new state and adjust weights

		p.draw(window);
		window.display();

		acceleration = sf::Vector2f(0, 0);
	}

	return 0;
}