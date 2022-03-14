#ifndef JUMPPER_H
#define JUMPPER_H

#include "monster.h"

class Jumpper: public Monster
{
public:
	Jumpper();

	void initialize(int x1, int y1);
	void Draw(sf::RenderWindow &window, Map &map);
	int Update(Map &map, Player &player);
};

#endif // !JUMPPER_H
