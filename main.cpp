#include "main.h"

void manageFps(sf::Text &text, sf::Clock &clock, int &tempo) {
	float currentTime = clock.restart().asSeconds();
	unsigned int fps = (unsigned int)(1.f / currentTime);

	if (tempo == 50) {
		text.setString(to_string(fps));
		tempo = 0;
	}
	tempo++;
}


int main(int argc, char *argv[])
{
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Super Kebla Bros");
	Game *game = Game::getInstance();

	int tempo = 50;

	window.setFramerateLimit(60);

	sf::Font font;
	if (!font.loadFromFile("graphics/font/ka1.ttf"))
		cout << "erreur load font : ka1.ttf" << endl;

	sf::Text text;
	text.setFont(font);
	text.setPosition((SCREEN_WIDTH - 50), 5);
	text.setCharacterSize(24);
	text.setColor(sf::Color::Red);
	window.setVerticalSyncEnabled(true);

	sf::Clock clock;
	while (window.isOpen())
	{
		game->manageInput(window);
    
		window.clear();

		game->Update(window);
		game->Draw(window);

		manageFps(text, clock, tempo);
		window.draw(text);

		window.display();
	}
	return 0;
}