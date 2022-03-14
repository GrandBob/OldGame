#include "player.h"
#include "../map/map.h"
#include "../input/input.h"

using namespace std;
using namespace sf;

Player::Player()
{
	if (!m_texture.loadFromFile("graphics/kebla.png")) {
		cout << "Erreur durant le chargement du spritesheet graphics/kebla.png." << endl;
		exit(EXIT_FAILURE);
	}
	else
		m_sprite.setTexture(m_texture);
  
	life = 1;
	dirX = dirY = 0;
	x = y = h = w = 0;
	checkpointActif = false;
	respawnX = respawnY = 0;
	frameNumber = frameTimer = frameMax = 0;
	etat = direction = 0;
	onGround = false;
	dirX = dirY = 0;
	saveX = saveY = 0;
	jumping = false;
}

void Player::initialize(Map &map, Input &input, bool newLevel)
{
	m_map = &map;
	m_input = &input;
	
	direction = RIGHT;
	etat = IDLE;
  
	frameNumber = 0;
	frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
	frameMax = 8;

	x = y = 0;

	w = PLAYER_WIDTH;
	h = PLAYER_HEIGTH;
  
	life = 1;
	onGround = false;

	m_map->setNombrePlateformes(0);
	m_map->init();
}

void Player::Draw(RenderWindow &window) {
	if (frameTimer <= 0) {
		frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
		frameNumber++;

		if (frameNumber >= frameMax)
			frameNumber = 0;
	}
	else {
		frameTimer--;
	}

	m_sprite.setPosition(Vector2f(static_cast<float>(x) - m_map->getStartX(), static_cast<float>(y) - m_map->getStartY()));

	if ((direction == LEFT && etat == WALK) || (etat != WALK && direction == RIGHT))
		m_sprite.setTextureRect(sf::IntRect((frameNumber + 1) * w, etat * h, -w, h));
	else
		m_sprite.setTextureRect(sf::IntRect(frameNumber * w, etat * h, w, h));
	window.draw(m_sprite);
}

void Player::Update(sf::RenderWindow & window)
{
	if (life > 0)
	{
		dirX = 0;
		dirY += static_cast<float>(GRAVITY_SPEED);
		if (dirY >= MAX_FALL_SPEED)
			dirY = MAX_FALL_SPEED;

		//Run left
		if (m_input->getButton().left == true) {
			dirX -= PLAYER_SPEED;
			direction = LEFT;
      
			if (etat != WALK && onGround == true)
				etat = WALK;
		}
		// Run Right
		else if (m_input->getButton().right == true) {
			dirX += PLAYER_SPEED;
			direction = RIGHT;

			if (etat != WALK && onGround == true)
				etat = WALK;
		}
		// Wait state
		else if (m_input->getButton().right == false && m_input->getButton().left == false && onGround == true) {
			if (etat != IDLE)
				etat = IDLE;
		}
    
		// Jump
		if (m_input->getButton().jump == true)
		{
			if (onGround == true) {
				dirY = -JUMP_HEIGHT;
				onGround = false;
				jumping = true;
			}
			m_input->setButton(jump, false);
		}

		if (onGround == true)
			jumping = true;
    
		if (onGround == false) {
			if (jumping == true) {
				if (etat != JUMP) {
					etat = JUMP;
				}
			}
		}
		mapCollision(*m_map);
		centerScrolling();
    }
	else
		killPlayer();
}

void Player::reset()
{
	initialize(*m_map, *m_input, false);
}

void Player::centerScrolling()
{
	int cxperso = x + w / 2;
	int cyperso = y + h / 2;
	int xlimmin = m_map->getStartX() + LIMITE_X;
	int xlimmax = xlimmin + LIMITE_W;
	int ylimmin = m_map->getStartY() + LIMITE_Y;
	int ylimmax = ylimmin + LIMITE_H;
  
	if (cxperso < m_map->getStartX())
		m_map->setStartX(m_map->getStartX() - 30);
	else if (cxperso < xlimmin)
		m_map->setStartX(m_map->getStartX() - 4);
  
	if (cxperso > m_map->getStartX() + SCREEN_WIDTH)
		m_map->setStartX(m_map->getStartX() + 30);
	else if (cxperso > xlimmax)
		m_map->setStartX(m_map->getStartX() + 4);

	if (m_map->getStartX() < 0)
		m_map->setStartX(0);
	else if (m_map->getStartX() + SCREEN_WIDTH >= m_map->getMaxX())
		m_map->setStartX(m_map->getMaxX() - SCREEN_WIDTH);

	if (cyperso < ylimmin)
		m_map->setStartY(m_map->getStartY() - 4);
  
	if (cyperso > ylimmax) {
		if (dirY >= MAX_FALL_SPEED - 2)
			m_map->setStartY(m_map->getStartY() + MAX_FALL_SPEED + 1);
		else
			m_map->setStartY(m_map->getStartY() + 4);
	}

	if (m_map->getStartY() < 0)
		m_map->setStartY(0);
	else if (m_map->getStartY() + SCREEN_HEIGHT >= m_map->getMaxY())
		m_map->setStartY(m_map->getMaxY() - SCREEN_HEIGHT);
}

void Player::horizontalCheckTiles(Map &map, int i)
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

void Player::verticalCheckTiles(Map &map, int i)
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
				if ((map.getTile(y2, x1) == TILE_PIKES) || (map.getTile(y2, x2) == TILE_PIKES)) // Pics
				{
					dirY = -JUMP_HEIGHT;

					if (life > 0)
						life = 0;
				}
				else if ((map.getTile(y2, x1) == TILE_RESSORT) || (map.getTile(y2, x2) == TILE_RESSORT)) // Trampoline
				{
					etat = BOUNCE;
					dirY = -15;
					onGround = 1;
				}
				else if (map.getTile(y2, x1) < BLANK_TILE || map.getTile(y2, x2) < BLANK_TILE)
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

void Player::finishLvl(Map &map)
{
	map.setLevel(map.getLevel() + 1);
	if (map.getLevel() > LEVEL_MAX)
		map.setLevel(1);
	map.reset();
}


void Player::mapCollision(Map &map)
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

	x += (int)(dirX);
	y += (int)(dirY);

	if (x < 0)
		x = 0;
	else if (x + w >= map.getMaxX())
		finishLvl(map);
	if (y > map.getMaxY())
		life = 0;
}

void Player::killPlayer()
{
	life = 0;
	m_map->reset();
}
