#ifndef S_TEXTURE_H
#define S_TEXTURE_H

#include "../abstractentity.h"

struct s_Texture {
	sf::Texture normal;
	sf::Texture hover;
	sf::Texture click;
	sf::Texture lock;
};

#endif