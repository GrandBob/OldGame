#ifndef GAME_H
#define GAME_H

#include "../abstractentity.h"
#include "../input/input.h"
#include "../map/map.h"
#include "../map/plateforme.h"
#include "../gui/gui.h"
#include "../player/player.h"
#include "../sound/soundmanager.h"

class Game : public AbstractEntity
{

public:
	static Game *getInstance() {
		if (gameInstance == nullptr)
			gameInstance = new Game();
		return gameInstance;
	};

	int getCurrLvl() { return this->currentLvl; };
	int getMaxLvl() { return this->MaxUserLvl; };
	int getNbLevels(void) { return this->nbLevels; };
	int getCurrentLvl(void) { return this->currentLvl; };
	int getState(void) { return this->state; };
	int getMaxUserLvl(void) { return this->MaxUserLvl; };

	void setNbLevels(int nb) { this->nbLevels = nb; };
	void setCurrentLvl(int nb, bool selectMap = false);
	void setState(int state) { this->state = state; };
	void setMaxUserLvl(int nb) { this->MaxUserLvl = nb; };

	void Draw(sf::RenderWindow &window);
	void Update(sf::RenderWindow & window);
	void manageInput(sf::RenderWindow &window);

protected:
	int state;
	int nbLevels;
	int currentLvl;
	int MaxUserLvl;

private:
	static Game *gameInstance;
	Game();

	GUI *m_gui;
	Map *m_map;
	Player *m_player;
	Input *m_input;

	SoundSystem soundSys;
};

#endif 