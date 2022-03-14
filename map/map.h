#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "../abstractentity.h"
#include "../def.h"
#include "../game/chrono.h"

class Player;
class Monster;
class Plateforme;


class Map : public AbstractEntity
{
public:
	static Map *getInstance() {
		if (instance == nullptr)
			instance = new Map();
		return instance;
	};

	int getStartX(void) const { return startX; };
	int getStartY(void) const { return startY; };
	int getMaxX(void) const { return maxX; };
	int getMaxY(void) const { return maxY; };
	int getTile(int y, int x) const { return tile[y][x]; };
	int getLevel(void) const { return level; };
	int getNombrePlateformes(void) const { return nombrePlateformes; };
	int getNombreMonstres(void) const { return nombreMonstres; };

	void setLevel(int valeur) { level = valeur; };
	void setStartX(int valeur) { startX = valeur; };
	void setStartY(int valeur) { startY = valeur; };
	void setTile(int y, int x, int valeur) { tile[y][x] = valeur; };
	void setNombrePlateformes(int valeur) { nombrePlateformes = valeur; };
	void setPlayer(Player *player) { m_player = player; };
	void setNombreMonstres(int valeur) { nombreMonstres = valeur; };
  
	void drawBackground(sf::RenderWindow &window);
	void loadMap(std::string filename);
	void Draw(sf::RenderWindow &window);
	void Update(sf::RenderWindow &window);
	void changeLevel(void);
	void testDefilement(void);
	void init(void);
	void reset(void);
  
  
private:
	static Map *instance;
	Map();

	int startX, startY;
	int maxX, maxY;
	int tile[MAX_MAP_Y][MAX_MAP_X];
	int tile2[MAX_MAP_Y][MAX_MAP_X];
	int tile3[MAX_MAP_Y][MAX_MAP_X];
	int mapTimer;
	int level;
	int nombrePlateformes;
	int nombreMonstres;

	sf::Texture backgroundTexture;
	sf::Sprite background;
  
	sf::Texture tileSetTexture;
	sf::Sprite tileSet;
	
	sf::Font font;
	sf::Text textLevel;

	Chrono chronometre;
	sf::Clock clock;

	Player *m_player;
	Monster *m_monster[MONSTERS_MAX];
	Plateforme *m_plateforme[PLATEFORMS_MAX];

	void drawLayer(sf::RenderWindow &window, int layer);
	void sortFileToVector(std::vector< std::vector< int > > &mapArray, std::string filename);
	int customTiles(int mapY, int mapX, int tiles[MAX_MAP_Y][MAX_MAP_X]);
};

#endif
