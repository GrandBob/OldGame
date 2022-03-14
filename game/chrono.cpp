#include "chrono.h"

using namespace std;
using namespace sf;

Chrono::Chrono(): separateur(':')
{
	if (!chronoFont.loadFromFile("graphics/font/digital-7.ttf"))
		cout << "erreur load font : digital-7.ttf" << endl;

	chronoText.setFont(chronoFont);
	chronoText.setPosition(10, 5);
	chronoText.setCharacterSize(28);
	chronoText.setColor(sf::Color::Blue);
}

void Chrono::start()
{
	chronometre = new Clock;
	chronometre->restart();
}

void Chrono::stop()
{
	delete chronometre;
}

void Chrono::restart()
{
	chronometre->restart();
}

void Chrono::draw(RenderWindow &window)
{
	stringstream ss;

	chronoTime = chronometre->getElapsedTime();

	int minute = (int)chronoTime.asSeconds() / 60 % 60;
	int seconde = (int)chronoTime.asSeconds() % 60;

	ss << minute << separateur;
	if (seconde < 10)
		ss << "0";
	ss << seconde;

	chronoText.setString(ss.str());
	window.draw(chronoText);
}