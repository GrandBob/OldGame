#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "../def.h"
#include <sstream>
#include <SFML/Audio.hpp>
#include <iostream>

class SoundManager
{
public:
	virtual void play(int etat) = 0;
};


class SoundSystem
{
private:
	std::vector < SoundManager * > listeners;
public:
	void attach(SoundManager *al)
	{
		listeners.push_back(al);
	}
	void setSomeSound(int etat)
	{
		for (int i = 0; i < listeners.size(); i++)
			listeners[i]->play(etat);
	}
};

/*----------------------- Ambiance ---------------------------*/

class Ambiance: public SoundManager
{
public:
	static Ambiance *getInstance() {
		if (instance == nullptr)
			instance = new Ambiance();
		return instance;
	};

	void play(int etat);

private:
	Ambiance() {};
	static Ambiance *instance;

	bool isPlaying = false;
	int currentMusic = 1;
	sf::Music music;
};

/*----------------------- Animation ---------------------------*/

class Animation: public SoundManager
{
public:
	static Animation *getInstance() {
		if (instance == nullptr)
			instance = new Animation();
		return instance;
	};

	void play(int etat);

private:
	Animation();
	static Animation *instance;

	bool isPlaying = false;
	int oldEtat = -1;

	sf::SoundBuffer jumpBuffer;
	sf::SoundBuffer bounceBuffer;
	sf::Sound sound;
};
#endif // !SOUNDMANAGER_H