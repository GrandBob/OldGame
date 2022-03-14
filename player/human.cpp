#include "humain.h"
#include "../map/map.h"

using namespace std;
using namespace sf;

Humain::Humain()
{
	if (!m_texture.loadFromFile("graphics/me.png"))
		cout << "Erreur durant le chargement du spriteheet graphics/me.png." << endl;
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
}

void Humain::mapCollision(Map &map)
{
	int i;

	onGround = 0;

	if (h > TILE_SIZE)
		i = TILE_SIZE;
	else
		i = h;
	horizontalCheckTiles(map, i);

	if (w > TILE_SIZE)
		i = TILE_SIZE;
	else
		i = w;
	verticalCheckTiles(map, i);

	x += static_cast<int>(dirX);
	y += static_cast<int>(dirY);

	if (x < 0)
		x = 0;
	else if (x + w >= map.getMaxX())
		finishLvl(map);
	if (y > map.getMaxY())
		life = 0;
}

void Humain::horizontalCheckTiles(Map &map, int i)
{
	int x1, x2, y1, y2;

	while (i != h)
	{
		x1 = (x + static_cast<int>(dirX)) / TILE_SIZE;
		x2 = (x + static_cast<int>(dirX) + w - 1) / TILE_SIZE;
		y1 = (y) / TILE_SIZE;
		y2 = (y + i - 1) / TILE_SIZE;

		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			if (dirX > 0)
			{
				if (map.getTile(y1, x2) < BLANK_TILE || map.getTile(y2, x2) < BLANK_TILE)
				{
					x = x2 * TILE_SIZE;
					x -= w + 1;
					dirX = 0;
				}
			}
			else if (dirX < 0)
			{
				if (map.getTile(y1, x1) < BLANK_TILE || map.getTile(y2, x1) < BLANK_TILE)
				{
					x = (x1 + 1) * TILE_SIZE;
					dirX = 0;
				}
			}
		}

		i += TILE_SIZE;
		if (i > h)
			i = h;
	}
}

void Humain::verticalCheckTiles(Map &map, int i)
{
	int x1, x2, y1, y2;

	while (i != w)
	{
		x1 = (x) / TILE_SIZE;
		x2 = (x + i) / TILE_SIZE;

		y1 = (y + static_cast<int>(dirY)) / TILE_SIZE;
		y2 = (y + static_cast<int>(dirY) + h) / TILE_SIZE;

		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			if (dirY > 0)
			{
				if (map.getTile(y2, x1) < TILE_TRAVERSABLE || map.getTile(y2, x2) < TILE_TRAVERSABLE)
				{
					y = y2 * TILE_SIZE;
					y -= h;
					dirY = 0;
					onGround = 1;
				}
			}
			else if (dirY < 0)
			{
				if (map.getTile(y1, x1) < BLANK_TILE || map.getTile(y1, x2) < BLANK_TILE)
				{
					y = (y1 + 1) * TILE_SIZE;
					dirY = 0;
				}
			}
		}

		i += TILE_SIZE;
		if (i > w)
			i = w;
	}
}

void Humain::finishLvl(Map &map)
{
	x = map.getMaxX() - w - 1;
}