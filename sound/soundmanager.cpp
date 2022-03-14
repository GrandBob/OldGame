#include "soundmanager.h"

using namespace std;
using namespace sf;

/*----------------------- Ambiance ---------------------------*/
Ambiance* Ambiance::instance;

void Ambiance::play(int etat)
{
	if (etat <= 0) {
		if (music.getPlayingOffset().asSeconds() == 0 || isPlaying == false) {
			stringstream musicstr;
			musicstr << "music/ambiance" << currentMusic << ".ogg";
			cout << "Lauch " << musicstr.str() << endl;
			if (!music.openFromFile(musicstr.str()))
				cout << "erreur load font : " << musicstr.str().c_str() << endl;
			else {
				music.play();
				isPlaying = true;
				currentMusic++;
				if (currentMusic > 4)
					currentMusic = 1;
			}
		}
	}
}

/*----------------------- Animation ---------------------------*/
Animation* Animation::instance;

void Animation::play(int etat)
{
	if ((!isPlaying || (sound.getPlayingOffset().asSeconds() == 0)) && oldEtat != etat) {
		oldEtat = etat;
		isPlaying = true;
		switch (etat) {
		case JUMP:
			sound.setBuffer(jumpBuffer);
			sound.play();
			break;
		case BOUNCE:
			sound.setBuffer(bounceBuffer);
			sound.play();
			break;
		default:
			break;
		}
	}
}

Animation::Animation()
{
	if (!jumpBuffer.loadFromFile("music/jump_effect.wav")) {
		cout << "Erreur music/jump_effect.wav" << endl;
	}

	if (!bounceBuffer.loadFromFile("music/bounce.wav")) {
		cout << "Erreur music/bounce.wav" << endl;
	}
}