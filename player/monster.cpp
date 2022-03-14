#include "monster.h"
#include "player.h"
#include "../map/map.h"


using namespace std;
using namespace sf;

Monster::Monster()
{
	if (!m_texture.loadFromFile("graphics/monster/monster1.png")) {
		cout << "Erreur durant le chargement du spritesheet du monstre." << endl;
	}
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

void Monster::initialize(int x1, int y1)
{
	frameNumber = 4;
	frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
	frameMax = MAX_FRAME_MONSTER;
	direction = LEFT;
	x = x1;
	y = y1;
	w = MONSTER_WIDTH;
	h = MONSTER_HEIGTH;
	onGround = 0;
	etat = 0;
}


void Monster::Draw(RenderWindow &window, Map &map)
{
	if (frameTimer <= 0)
	{
		frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
		frameNumber++;
		if (frameNumber >= frameMax)
			frameNumber = 0;
	}
	else
		frameTimer--;

	m_sprite.setPosition(Vector2f(static_cast<float>(x) - map.getStartX(), static_cast<float>(y) - map.getStartY()));

	if (direction == RIGHT)
		m_sprite.setTextureRect(sf::IntRect((frameNumber + 1) * w, etat, -w, h));
	else
		m_sprite.setTextureRect(sf::IntRect(frameNumber * w, etat, w, h));
	window.draw(m_sprite);
}

int Monster::Update(Map &map, Player &player)
{
	if (life > 0)
	{
		dirX = 0;
		dirY += static_cast<float>(GRAVITY_SPEED);

		if (dirY >= MAX_FALL_SPEED)
			dirY = MAX_FALL_SPEED;

		if (x == saveX || checkFall(map) == 1)
		{
			if (direction == LEFT)
				direction = RIGHT;
			else
				direction = LEFT;
		}

		if (direction == LEFT)
			dirX -= 2;
		else
			dirX += 2;

		saveX = x;
		mapCollision(map);

		switch (hitBox(player))
		{
			case 1:
				player.killPlayer();
				break;
			case 2:
				life--;
				break;
			default:
				break;
		}
	}
	return life;
}

int Monster::hitBox(Player &player)
{
	if (player.getX() > 0 && player.getY() > 0) {
		if ((player.getX() >= x + w) || (player.getX() + player.getW() <= x) || (player.getY() >= y + h) || (player.getY() + player.getH() <= y))
			return 0;
		else if (player.getY() + player.getH() <= y + 10)
		{
			player.setDirY(-JUMP_HEIGHT);
			return 2;
		}
		else
			return 1;
	}
	return 0;
}

int Monster::checkFall(Map &map)
{
	int Fx, Fy;

	if (direction == LEFT)
	{
		Fx = (int)(x + dirX) / TILE_SIZE;
		Fy = (int)(y + h - 1) / TILE_SIZE;

		if (Fy < 0)
			Fy = 1;

		if (Fy > MAX_MAP_Y)
			Fy = MAX_MAP_Y;

		if (Fx < 0)
			Fx = 1;

		if (Fx > MAX_MAP_X)
			Fx = MAX_MAP_X;

		if (map.getTile(Fy + 1, Fx) > BLANK_TILE)
			return 1;
		else
			return 0;
	}
	else
	{
		Fx = (int)(x + w + dirX) / TILE_SIZE;
		Fy = (int)(y + h - 1) / TILE_SIZE;

		if (Fy <= 0)
			Fy = 1;

		if (Fy >= MAX_MAP_Y)
			Fy = MAX_MAP_Y - 1;

		if (Fx <= 0)
			Fx = 1;

		if (Fx >= MAX_MAP_X)
			Fx = MAX_MAP_X - 1;

		if (map.getTile(Fy + 1, Fx) > BLANK_TILE)
			return 1;
		else
			return 0;
	}
}