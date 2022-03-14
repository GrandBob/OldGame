//
//  map.cpp
// 
//
//  Created by Nicolas DESVILETTES on 29/03/2016.
//  Copyright © 2016 Nicolas DESVILETTES. All rights reserved.
//

#include "map.h"
#include "plateforme.h"
#include "../player/monster.h"
#include "../player/monsterfactory.h"
#include "../player/player.h"
#include <windows.h>
#include <string>
#include <iostream>

using namespace std;
using namespace sf;

Map* Map::instance;

Map::Map()
{
	if (!backgroundTexture.loadFromFile("graphics/background.png")) {
		cout << "Erreur durant le chargement de l'image de background." << endl;
	}
	else
		background.setTexture(backgroundTexture);
  
	if (!tileSetTexture.loadFromFile("graphics/tiles.png")) {
		cout << "Erreur durant le chargement de l'image du tileset." << endl;
	}
	else
		tileSet.setTexture(tileSetTexture);

	if (!font.loadFromFile("graphics/font/DIMITRI.TTF"))
		cout << "erreur load font : DIMITRI.TTF" << endl;

	mapTimer = TIME_BETWEEN_2_FRAMES * 3;
	level = 1;
	startX = startY = 0;

	chronometre.start();

	for (int i = 0; i < PLATEFORMS_MAX; i++)
		m_plateforme[i] = nullptr;
	for (int i = 0; i < MONSTERS_MAX; i++)
		m_monster[i] = nullptr;
}

void Map::init() {
	stringstream ss;

	ss << "Level " << getLevel();

	textLevel.setFont(font);
	textLevel.setString(ss.str());
	textLevel.setCharacterSize(50);
	textLevel.setColor(sf::Color::Black);
	textLevel.setPosition(sf::Vector2f(CENTER_SCREEN_X, 0));

	chronometre.restart();

	for (int i = 0; i < PLATEFORMS_MAX; i++)
		m_plateforme[i] = new Plateforme;
	for (int i = 0; i < MONSTERS_MAX; i++)
		m_monster[i] = MonsterFactory::getInstance((rand() % 3));
}

void Map::reset() {
	for (int i = 0; i < PLATEFORMS_MAX; i++)
		m_plateforme[i] = NULL;
	for (int i = 0; i < MONSTERS_MAX; i++)
		m_monster[i] = NULL;

	mapTimer = TIME_BETWEEN_2_FRAMES * 3;
	startX = startY = 0;

	changeLevel();
	m_player->reset();
	init();
}

void Map::changeLevel(void)
{
	string filename;
	filename = "map" + to_string(level) + ".txt";
	loadMap(filename);
}

void Map::drawBackground(RenderWindow &window)
{
	window.draw(background);
}

void Map::loadMap(string filename)
{
	int fx;
	int fy;
	vector<vector< int > > mapArray;

	maxX = maxY = 0;
	sortFileToVector(mapArray, filename);

	for (fy = 0; fy < MAX_MAP_Y; fy++)
	{
		for (fx = 0; fx < MAX_MAP_X; fx++)
		{
			tile[fy][fx] = mapArray[fy][fx];

			if (tile[fy][fx] > 0)
			{
				if (fx > maxX)
					maxX = fx;
				if (fy > maxY)
					maxY = fy;
			}
		}
	}

	for (fy = 0; fy < MAX_MAP_Y; fy++)
	{
		for (fx = 0; fx < MAX_MAP_X; fx++)
			tile2[fy][fx] = mapArray[fy + MAX_MAP_Y][fx];
	}
  
	for (fy = 0; fy < MAX_MAP_Y; fy++)
	{
		for (fx = 0; fx < MAX_MAP_X; fx++)
			tile3[fy][fx] = mapArray[fy + MAX_MAP_Y * 2][fx];
	}

	maxX = (maxX + 1) * TILE_SIZE;
	maxY = (maxY + 1) * TILE_SIZE;
}

void Map::sortFileToVector(vector< vector< int > > &mapArray, string filename)
{
	fstream mapFile;
	string buffer, tmp;
	stringstream str;
	vector<int> ligne;

	mapFile.open(filename, fstream::in);
	if (!mapFile.is_open()) {
		cout << "Erreur de chargement du fichier " << filename << "." << endl;;
		exit(EXIT_FAILURE);
	}

	while (!mapFile.eof())
	{
		getline(mapFile, buffer);
		if (!buffer.size())
			continue;

		str.clear();
		str.str(buffer);
		ligne.clear();

		while (getline(str, tmp, ' '))
			ligne.push_back(atoi(tmp.c_str()));
		if (ligne.size())
			mapArray.push_back(ligne);
	}
	mapFile.close();
}

void Map::Draw(RenderWindow &window)
{
	if (mapTimer <= 0)
		mapTimer = TIME_BETWEEN_2_FRAMES * 3;
	else
		mapTimer--;

	drawLayer(window, 2);
	drawLayer(window, 1);

	for (int i = 0; i < getNombrePlateformes(); i++) {
		m_plateforme[i]->Draw(*this, window);
	}

	for (int i = 0; i < getNombreMonstres(); i++) {
		if (m_monster[i] != nullptr) {
			m_monster[i]->Draw(window, *this);
		}
	}

	drawLayer(window, 3);
	chronometre.draw(window);

	window.draw(textLevel);
}

void Map::Update(sf::RenderWindow & window)
{
	for (int i = 0; i < getNombreMonstres(); i++)
	{
		if (m_monster[i] != nullptr && m_monster[i]->Update(*this, *m_player) == 0)
			m_monster[i] = nullptr;
	}

	for (int i = 0; i < getNombrePlateformes(); i++)
	{
		m_plateforme[i]->Update(*m_player);
		m_plateforme[i]->checkCollisions(*m_player);
	}

}


void Map::drawLayer(sf::RenderWindow & window, int layer) {
	int mapX, mapY, xsource, ysource, a;
	float x, y, x1, x2, y1, y2;

	x1 = (float)(startX % TILE_SIZE) * -1;
	x2 = SCREEN_WIDTH + (x1 == 0 ? 0 : (TILE_SIZE + x1));

	y1 = (float)(startY % TILE_SIZE) * -1;
	y2 = SCREEN_HEIGHT + (y1 == 0 ? 0 : (TILE_SIZE + y1));

	mapY = startY / TILE_SIZE;
	for (y = y1; y < y2; y += TILE_SIZE) {
		mapX = startX / TILE_SIZE;

		for (x = x1; x < x2; x += TILE_SIZE) {
			if (layer == 1)
				a = customTiles(mapY, mapX, tile);
			else if (layer == 2)
				a = customTiles(mapY, mapX, tile2);
			else
				a = customTiles(mapY, mapX, tile3);

			ysource = (a / 8 * TILE_SIZE);
			xsource = (a % 8 * TILE_SIZE) - 32;

			tileSet.setPosition(Vector2f(x, y));
			tileSet.setTextureRect(sf::IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
			window.draw(tileSet);
			mapX++;
		}
		mapY++;
	}
}

int Map::customTiles(int mapY, int mapX, int tiles[MAX_MAP_Y][MAX_MAP_X])
{
	if (tiles[mapY][mapX] != 0)
	{
		if (tile[mapY][mapX] == TILE_MONSTRE)
		{
			if (nombreMonstres < MONSTERS_MAX)
			{
				m_monster[nombreMonstres]->initialize(mapX * TILE_SIZE, mapY * TILE_SIZE);
				nombreMonstres++;
			}
			tiles[mapY][mapX] = TILE_TRAVERSABLE;
		}
		else if (tiles[mapY][mapX] == TILE_PLATEFORM || tiles[mapY][mapX] == TILE_PLATEFORM_UP)
		{
			if (nombrePlateformes < PLATEFORMS_MAX) {
				m_plateforme[nombrePlateformes]->initialize(mapX * TILE_SIZE, mapY * TILE_SIZE, tiles[mapY][mapX] - TILE_PLATEFORM + 1);
				nombrePlateformes++;
			}
			tiles[mapY][mapX] = TILE_TRAVERSABLE;
		}
	}
	return tiles[mapY][mapX];
}

void Map::testDefilement(void)
{
	if (startX < maxX - SCREEN_WIDTH - 10)
		startX += 10;
}
