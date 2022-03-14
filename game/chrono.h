#ifndef CHRONO_H
#define CHRONO_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <sstream>

#include "../def.h"

class Chrono
{
public:
	Chrono();

	void start();
	void stop();
	void restart();
	void draw(sf::RenderWindow &window);

private:
	char separateur;

	sf::Clock *chronometre;
	sf::Time chronoTime;

	sf::Font chronoFont;
	sf::Text chronoText;
	sf::FloatRect backgroundRect;
	sf::RectangleShape background;
};

#endif
