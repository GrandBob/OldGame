#ifndef RUNNER_H
#define RUNNER_H

#include "monster.h"

class Map;
class Player;

class Runner : public Monster
{
public:
	Runner();

	void initialize(int x1, int y1);
	void Draw(sf::RenderWindow &window, Map &map);
	int Update(Map &map, Player &player);
};

#endif // !RUNNER_H
