#ifndef PLATEFORME_H
#define PLATEFORME_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../def.h"

class Plateforme
{
	public:
		Plateforme();

		void initialize(int Ax, int Ay, int Atype);
		void Update(Player &player);
		void Draw(Map &map, sf::RenderWindow &window);
		void checkCollisions(Player &player);

	private:
		int x, y, h, w;
		int direction;

		sf::Texture Texture;
		sf::Sprite Sprite;

		int beginX, beginY;
		int type, player_on;
};
#endif
