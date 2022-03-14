#ifndef ABSTRACTENTITY_H
#define ABSTRACTENTITY_H

#include <SFML/Graphics.hpp>

#define MENU	0
#define PAUSE	1
#define INGAME	2
#define LEVELS	3
#define LEAVE	-1

class AbstractEntity
{
public:
	AbstractEntity() {};
	virtual void Draw(sf::RenderWindow &window) = 0;
	virtual void Update(sf::RenderWindow & window) = 0;
};
#endif
