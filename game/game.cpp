#include "game.h"

using namespace std;
using namespace sf;

Game* Game::gameInstance;

Game::Game(): state(MENU), nbLevels(2), currentLvl(1), MaxUserLvl(1)
{
	m_gui = GUI::getInstance();
	m_map = Map::getInstance();
	m_input = Input::getInstance();
	m_player = new Player();

	m_gui->setState(0);
	m_gui->setGame(nbLevels, currentLvl, MaxUserLvl, state);

	m_player->initialize(*m_map, *m_input, true);
	m_map->setPlayer(m_player);
	m_map->init();

	soundSys.attach(Ambiance::getInstance());
	soundSys.attach(Animation::getInstance());
}

void Game::Draw(RenderWindow &window)
{
	m_map->drawBackground(window);

	if (state == INGAME) {
		m_map->drawBackground(window);
		m_map->Draw(window);
		m_player->Draw(window);
	}
	m_gui->Draw(window);
}

void Game::Update(sf::RenderWindow & window)
{
	currentLvl = m_map->getLevel();
	if (currentLvl > MaxUserLvl)
		MaxUserLvl = currentLvl;
	m_gui->updateGame(nbLevels, currentLvl, MaxUserLvl, state);

	m_player->Update(window);

	m_gui->Update(window);
	m_map->Update(window);

	soundSys.setSomeSound(m_player->getEtat());
}

void Game::manageInput(sf::RenderWindow & window)
{
	if (state != PAUSE)
		m_input->gestionInputs(window);
}

void Game::setCurrentLvl(int nb, bool selectMap) {
	if (nb > MaxUserLvl)
		this->MaxUserLvl = nb;
	this->currentLvl = nb;

	if (selectMap) {
		cout << "setCurrentLvl change map" << endl;
		m_map->setLevel(this->currentLvl);
		m_map->reset();
	}
}