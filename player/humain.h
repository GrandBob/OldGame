#ifndef HUMAIN_H
#define HUMAIN_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../def.h"

class Map;

class Humain
{

public:
	Humain();

	int getX(void) const { return this->x; };
	int getY(void) const { return this->y; };
	int getW(void) const { return this->w; };
	int getH(void) const { return this->h; };
	float getDirX(void) const { return this->dirX; };
	float getDirY(void) const { return this->dirY; };
	bool getOnGround(void) const { return this->onGround; };
	int getDirection(void) const { return this->direction; };

	void setX(int valeur) { this->x = valeur; };
	void setY(int valeur) { this->y = valeur; };
	void setW(int valeur) { this->w = valeur; };
	void setH(int valeur) { this->h = valeur; };
	void setDirX(float valeur) { this->dirX = valeur; };
	void setDirY(float valeur) { this->dirY = valeur; };
	void setOnGround(bool valeur) { this->onGround = valeur; };

protected:
	void mapCollision(Map &map);
	void horizontalCheckTiles(Map &map, int i);
	void verticalCheckTiles(Map &map, int i);
	void finishLvl(Map &map);

	int life;
	int x, y;
	int h, w;
	int checkpointActif;
	int respawnX, respawnY;
	int frameNumber, frameTimer, frameMax;
	int etat, direction;
	bool onGround;
	float dirX, dirY;
	int saveX, saveY;
	bool jumping;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

#endif
