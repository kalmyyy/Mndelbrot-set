#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "ComplexPlane.h"
#include <sstream>
#include <vector>


using namespace sf;
using namespace std;


int main()
{
	int hawk = VideoMode::getDesktopMode().width /2;
	int tuah = VideoMode::getDesktopMode().height /2;
	VideoMode sigma(hawk, tuah);
	RenderWindow window(sigma, "Mand set", Style::Default);
	ComplexPlane kaiCenat(hawk, tuah);
	Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		return -1;
	}
	Text text;
	text.setFont(font);
	text.setString("Hello Baby gronk");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	window.draw(text);

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{


			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{

					kaiCenat.zoomIn();
					kaiCenat.setCenter(Vector2i(event.mouseButton.x, event.mouseButton.y));
				}
				if (event.mouseButton.button == Mouse::Right)
				{
					kaiCenat.zoomOut();
					kaiCenat.setCenter(Vector2i(event.mouseButton.x, event.mouseButton.y));
				}
			}
			if (event.type == Event::MouseMoved)
			{

				kaiCenat.setMouseLocation(Vector2i(event.mouseButton.x, event.mouseButton.y));

			}

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}

			kaiCenat.updateRender();
			kaiCenat.loadText(text);

			window.clear();


			kaiCenat.draw(window,RenderStates());
			
			window.draw(text);
			window.display();
		}
	}
}