#include "jumpper.h"
#include "player.h"
#include "../map/map.h"

using namespace std;
using namespace sf;

Jumpper::Jumpper()
{
	if (!m_texture.loadFromFile("graphics/monster/monster_jump.png")) {
		cout << "Erreur durant le chargement du spritesheet du monstre." << endl;
		exit(EXIT_FAILURE);
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

void Jumpper::initialize(int x1, int y1)
{
	frameNumber = 0;
	frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
	frameMax = MAX_FRAME_MONSTER_JUMP;
	direction = LEFT;
	x = x1;
	y = y1;
	w = MONSTER_JUMP_WIDTH;
	h = MONSTER_JUMP_HEIGTH;
	onGround = 0;
	etat = 0;
}

int Jumpper::Update(Map & map, Player & player)
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

		
		if ((rand() % 60 + 1) == 1) {
			if (onGround == true) {
				dirY = -JUMP_HEIGHT;
				onGround = false;
			}
		}

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


void Jumpper::Draw(RenderWindow &window, Map &map)
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
		m_sprite.setTextureRect(sf::IntRect((frameNumber + 1) * w, etat * h, -w, h));
	else
		m_sprite.setTextureRect(sf::IntRect(frameNumber * w, etat * h, w, h));
	window.draw(m_sprite);
}