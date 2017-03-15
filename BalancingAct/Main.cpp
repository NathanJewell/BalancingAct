
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Pencil.hpp"

sf::Vector2f divide(const sf::Vector2f& vec, const double& scalar)
{
	return sf::Vector2f(vec.x / scalar, vec.y / scalar);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "LAPIZ");
	window.setFramerateLimit(144);
	Pencil p = Pencil(10, .6, 0, sf::Vector2f(200, 200));
	double dt = 0;	//frametime in seconds
	double lastframe = 0;
	sf::Vector2f mousePosition(0, 0);
	sf::Vector2f mouseVelocity(0, 0);
	sf::Vector2f mouseAcceleration(0, 0);

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

		sf::Vector2f tmpPosition = (sf::Vector2f)sf::Mouse::getPosition(window);
		sf::Vector2f tmpVelocity = (mousePosition - tmpPosition);
		mouseAcceleration = divide((tmpVelocity - mouseVelocity), dt);
		mouseVelocity = divide(tmpVelocity, dt);
		mousePosition = tmpPosition;

		//std::cout << mouseVelocity.x << ", " << mouseVelocity.y << std::endl;
		window.clear();
		p.updateAnchor(mousePosition, mouseVelocity, mousePosition);
		p.update(dt);
		p.draw(window);
		window.display();
	}

	return 0;
}