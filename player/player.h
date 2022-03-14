#ifndef PLAYER_H
#define PLAYER_H

#include "humain.h"
#include "../abstractentity.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../def.h"

class Map;
class Input;

class Player: public Humain, AbstractEntity
{
public:
	Player();

	void initialize(Map &map, Input &input, bool newLevel);
	void Draw(sf::RenderWindow &window);
	void Update(sf::RenderWindow &window);
	
	void killPlayer(void);
	void reset(void);
  
	int getEtat(void) const { return this->etat; };

private:
	void centerScrolling();
	void mapCollision(Map &map);
	void horizontalCheckTiles(Map &map, int i);
	void verticalCheckTiles(Map &map, int i);
	void finishLvl(Map &map);

	Input *m_input;
	Map *m_map;
};

#endif
