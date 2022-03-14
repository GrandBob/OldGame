#include "gui.h"
#include "../game/game.h"
#include "../button/button.h"
#include <iostream>

using namespace std;
using namespace sf;

GUI* GUI::instance;

GUI::GUI(): goLevel(0)
{
	start = new MyButton(setTexture("normalstart.png", "hoverstart.png", "clickstart.png"));
	start->setPosition(sf::Vector2f(CENTER_SCREEN_X, 50));

	leave = new MyButton(setTexture("normalleave.png", "hoverleave.png", "clickleave.png"));
	leave->setPosition(sf::Vector2f(CENTER_SCREEN_X, 150));
/*
	resume = new MyButton(setTexture("normal.png", "hover.png", "click.png"));
	resume->setPosition(sf::Vector2f(CENTER_SCREEN_X, 50));

	restart = new MyButton(setTexture("normal.png", "hover.png", "click.png"));
	restart->setPosition(sf::Vector2f(CENTER_SCREEN_X, 150));

	home = new MyButton(setTexture("normal.png", "hover.png", "click.png"));
	home->setPosition(sf::Vector2f(50, 50));

	pause = new MyButton(setTexture("normal.png", "hover.png", "click.png"));
	pause->setPosition(sf::Vector2f(250, 50));

	cross = new MyButton(setTexture("normal.png", "hover.png", "click.png"));
	cross->setPosition(sf::Vector2f(450, 50));
*/
}

void GUI::setLevelsMenu() {
	bool disabled = false;
	MyButton *tmp = NULL;
	float y = 50;

	for (int i = 1; i <= this->nbLevels; i++) {
		std::stringstream normal;
		normal << "level" << i << "normal.png";
		std::stringstream hover;
		hover << "level" << i << "hover.png";
		std::stringstream click;
		click << "level" << i << "click.png";
		std::stringstream locked;
		locked << "";
		//locked << "level" << i << "locked.png";

		if (i > getMaxUserLvl())
			disabled = true;

		tmp = new MyButton(setTexture(normal.str(), hover.str(), click.str(), locked.str()), disabled);
		tmp->setPosition(sf::Vector2f(CENTER_SCREEN_X, y + ((i - 1) * 100)));

		levels.push_back(tmp);
	}
}

struct s_Texture GUI::setTexture(std::string normal, std::string hover, std::string clicked, std::string lock)
{
	struct s_Texture myTexture;
	Texture t_normal, t_hover, t_click, t_lock;
	string str;

	str = "graphics/button/" + normal;
	if (!t_normal.loadFromFile(str))
		cout << "normal damn" << endl;
	else {
		myTexture.normal = t_normal;

		str = "graphics/button/" + hover;
		if (hover != "" && !t_hover.loadFromFile(str))
			myTexture.hover = t_normal;
		else
			myTexture.hover = t_hover;
		str = "graphics/button/" + clicked;
		if (clicked != "" && !t_click.loadFromFile(str))
			myTexture.click = t_normal;
		else
			myTexture.click = t_click;
		str = "graphics/button/" + lock;
		if (lock!= "" && !t_lock.loadFromFile(str))
			myTexture.lock = t_normal;
		else
			myTexture.lock = t_lock;
	}

	return myTexture;
}

void GUI::Draw(RenderWindow & window)
{
	switch (state) {
		case MENU:
			drawMenu(window);
			break;
		/*case PAUSE:
			drawPause(window);
			break;
		case INGAME:
			drawInGame(window);*/
			break;
		case LEVELS:
			drawLevels(window);
			break;
	}
}

void GUI::Update(sf::RenderWindow & window)
{
	int i = 1;
	for (std::vector<MyButton *>::iterator it = levels.begin(); it != levels.end(); ++it) {
		if (i > this->getMaxUserLvl())
			(*it)->setDisabled(true);
		else
			(*it)->setDisabled(false);
		i++;
	}
	if (this->getState() < 0)
		window.close();
}

void GUI::drawMenu(RenderWindow & window)
{
	start->manageButton(window, &GUI::Start);
	leave->manageButton(window, &GUI::Leave);
}

void GUI::drawLevels(RenderWindow & window)
{
	int i = 1;
	for (std::vector<MyButton *>::iterator it = levels.begin(); it != levels.end(); ++it) {
		this->goLevel = i++;
		(*it)->manageButton(window, &GUI::Levels);
	}
}
/*
void GUI::drawPause(RenderWindow & window)
{
	leave->setPosition(sf::Vector2f(CENTER_SCREEN_X, 250));

	resume->manageButton(window, &GUI::Resume);
	restart->manageButton(window, &GUI::Restart);
	leave->manageButton(window, &GUI::Leave);
}

void GUI::drawInGame(RenderWindow & window)
{
	home->manageButton(window, &GUI::Home);
	cross->manageButton(window, &GUI::Resume);
	pause->manageButton(window, &GUI::Pause);
}
*/

void GUI::setGame(int nb, int current, int max, int state) {
	setState(state);
	setNbLevels(nb);
	setCurrentLvl(current);
	setMaxUserLvl(max);
	setLevelsMenu();
};

void GUI::updateGame(int nb, int current, int max, int state) {
	setState(state);
	setNbLevels(nb);
	setCurrentLvl(current);
	setMaxUserLvl(max);
};

/*
 *	Button Actions
 */
void GUI::Start(void)
{
	Game *tmp = Game::getInstance();
	tmp->setState(LEVELS);
}

void GUI::Leave(void)
{
	Game *tmp = Game::getInstance();
	tmp->setState(LEAVE);
}
/*
void GUI::Resume(void)
{
	Game *tmp = Game::getInstance();
	tmp->setState(INGAME);
}

void GUI::Restart(void)
{
	Game *tmp = Game::getInstance();
	tmp->setState(INGAME);
}
*/
void GUI::Levels(void)
{
	Game *tmp = Game::getInstance();
	GUI *tmp2 = GUI::getInstance();

	tmp->setCurrentLvl(tmp2->goLevel, true);
	tmp->setState(INGAME);
	cout << "Levels " << tmp->getCurrentLvl() << endl;
}
/*
void GUI::Pause(void)
{
	Game *tmp = Game::getInstance();
	tmp->setState(PAUSE);
}

void GUI::Home(void)
{
	Game *tmp = Game::getInstance();
	tmp->setState(MENU);
}
*/
