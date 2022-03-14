#include "../player/player.h"
#include "plateforme.h"
#include "map.h"

using namespace std;
using namespace sf;


Plateforme::Plateforme()
{
	if (!Texture.loadFromFile("graphics/plateforme.png")) {
		cout << "Erreur durant le chargement du sprite de la plateforme." << endl;
	}
	Sprite.setTexture(Texture);

	x = y = h = w = 0;
	beginX = beginY = type = 0;
	direction = 0;
}


void Plateforme::initialize(int Ax, int Ay, int Atype)
{
	x = beginX = Ax;
	y = beginY = Ay;

	w = 96;
	h = 24;

	type = Atype;

	if (type == 2)
		direction = UP;
	else
		direction = RIGHT;
}


void Plateforme::Update(Player &player)
{
	if (type == 2)
	{
		if (direction == UP)
		{
			y -= PLATEFORM_SPEED;
			if (player_on == 1)
				player.setY(player.getY() - PLATEFORM_SPEED);
		}
		else
		{
			y += PLATEFORM_SPEED;
			if (player_on == 1)
				player.setY(player.getY() + PLATEFORM_SPEED);
		}

		if (y > beginY + 5 * TILE_SIZE)
			direction = UP;

		if (y < beginY)
			direction = DOWN;
	}
	else
	{
		if (direction == RIGHT)
		{
			x += PLATEFORM_SPEED;
			if (player_on == 1)
				player.setX(player.getX() + PLATEFORM_SPEED);
		}
		else
		{
			x -= PLATEFORM_SPEED;
			if (player_on == 1)
				player.setX(player.getX() - PLATEFORM_SPEED);
		}
		if (x > beginX + 5 * TILE_SIZE)
			direction = LEFT;

		if (x < beginX)
			direction = RIGHT;
	}

}


void Plateforme::Draw(Map &map, RenderWindow &window)
{
	Sprite.setPosition(Vector2f(static_cast<float>(x) - map.getStartX(), static_cast<float>(y) - map.getStartY()));
	window.draw(Sprite);
}


void Plateforme::checkCollisions(Player &player)
{
	if (player.getX() + player.getW() >= x && player.getX() <= x + w && player.getY() + player.getH() >= y && player.getY() + player.getH() < y + 32) {
		player.setY(y - player.getH());
		player.setDirY(0);
		player.setOnGround(true);
		player_on = 1;
	}
	else
		player_on = 0;
}