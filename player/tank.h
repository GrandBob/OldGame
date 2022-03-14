#ifndef TANK_H
#define TANK_H

#include "monster.h"

class Tank : public Monster
{
public:
	Tank();

	void initialize(int x1, int y1);
	void Draw(sf::RenderWindow &window, Map &map);
	int Update(Map &map, Player &player);
};

#endif // !TANK_H
