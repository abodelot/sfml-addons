#include "BitmapFont/BitmapFont.hpp"
#include "BitmapFont/BitmapText.hpp"

int main()
{
	sf::RenderWindow app(sf::VideoMode(480, 320), "SFML window");

	// Load the bitmap font
	BitmapFont font;
	font.loadFromFile("resources/font.png");

	// Default text
	BitmapText text("Hello world!", font);
	text.setPosition(20, 50);

	// Text with a color
	BitmapText text2("Bitmap text written in green", font);
	text2.setColor(sf::Color::Green);
	text2.setPosition(20, 100);

	// Text scalled
	BitmapText text3("Bitmap text scalled x2", font);
	text3.setScale(2, 2);
	text3.setPosition(20, 150);

	while (app.isOpen())
	{
		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				app.close();
		}
		app.clear(sf::Color(0x20, 0x7d, 0xe5)); // Blue background
		app.draw(text);
		app.draw(text2);
		app.draw(text3);
		app.display();
	}
	return 0;
}




