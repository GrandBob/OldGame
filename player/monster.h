#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../player/humain.h"
#include "../def.h"

class Map;
class Player;

class Monster : public Humain
{

public:
	Monster();

	virtual void initialize(int x1, int y1);
	virtual void Draw(sf::RenderWindow &window, Map &map);
	virtual int Update(Map &map, Player &player);

protected:
	int hitBox(Player &player);
	int checkFall(Map &map);
};

#endif
