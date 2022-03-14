#ifndef GUI_H
#define GUI_H

#include <vector>
#include "../abstractentity.h"
#include "../button/button.h"
#include "../structure/s_texture.h"

class MyButton;

class GUI : public AbstractEntity
{
public:
	//Constructeur
	static GUI *getInstance() {
		if (instance == nullptr)
			instance = new GUI();
		return instance;
	};

	int getState(void) { return this->state; };
	int getLevel(void) { return this->goLevel; };
	int getNbLevels(void) { return this->nbLevels; };
	int getCurrentLvl(void) { return this->currentLvl; };
	int getMaxUserLvl(void) { return this->MaxUserLvl; };

	void setState(int state) { this->state = state; };
	void setLevel(int level) { this->goLevel = level; };
	void setNbLevels(int nb) { this->nbLevels = nb; };
	void setMaxUserLvl(int nb) { this->MaxUserLvl = nb; };
	void setCurrentLvl(int nb) {
		if (nb > MaxUserLvl)
			this->MaxUserLvl = nb;
		this->currentLvl = nb;
	};

	void Draw(sf::RenderWindow &window);
	void Update(sf::RenderWindow & window);
	void setGame(int nb, int current, int max, int state);
	void updateGame(int nb, int current, int max, int state);
private:
	static GUI *instance;
	GUI();

	int state;
	int goLevel;
	int nbLevels;
	int currentLvl;
	int MaxUserLvl;

	MyButton *start;
	//MyButton *resume;
	//MyButton *restart;
	//MyButton *home;
	//MyButton *pause;
	MyButton *leave;
	MyButton *cross;
	std::vector<MyButton *> levels;

	void setLevelsMenu(void);
	void drawMenu(sf::RenderWindow & window);
	//void drawPause(sf::RenderWindow & window);
	//void drawInGame(sf::RenderWindow & window);
	void drawLevels(sf::RenderWindow & window);
	struct s_Texture setTexture(std::string normal, std::string hover = "", std::string clicked = "", std::string lock = "");

protected:
	void Start(void);
	void Leave(void);
	//void Resume(void);
	//void Restart(void);
	void Levels(void);
	//void Home(void);
	//void Pause(void);
};
#endif
