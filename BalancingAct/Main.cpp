
#include <SFML/Graphics.hpp>
#include "Pencil.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "LAPIZ");
	//window.setFramerateLimit(144);
	Pencil p = Pencil(10, .2, 3.14/16, sf::Vector2f(200, 200));
	double dt = 0;	//frametime in seconds
	double lastframe = 0;
	sf::Clock clock;
	while (window.isOpen())
	{
		dt = clock.getElapsedTime().asSeconds() - lastframe;
		lastframe = clock.getElapsedTime().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		p.update(dt);
		p.draw(window);
		window.display();
	}

	return 0;
}