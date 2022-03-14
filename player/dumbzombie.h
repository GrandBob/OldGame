#ifndef DUMBZOMBIE_H
#define DUMBZOMBIE_H

#include <iostream>
#include "monster.h"

class DumbZombie : public Monster
{
public:
	DumbZombie();
};

DumbZombie::DumbZombie()
{
	if (!m_texture.loadFromFile("graphics/monster1.png"))
		std::cout << "Erreur durant le chargement du spritesheet du monstre." << std::endl;
	else
		m_sprite.setTexture(m_texture);

	life = 1;
	dirX = dirY = 0;
	x = y = h = w = 0;
	checkpointActif = respawnX = respawnY = 0;
	frameNumber = frameTimer = frameMax = 0;
	etat = direction = 0;
	onGround = false;
	dirX = dirY = 0;
	saveX = saveY = 0;
	jumping = false;
	monsterSpeed = 1;
}

#endif
