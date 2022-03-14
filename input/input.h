#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>

class Input
{
  struct Button { bool left, right, up, down, jump, attack, enter; };
  
public:
	static Input *getInstance() {
		if (instance == nullptr)
			instance = new Input();
		return instance;
	};
	Button getButton(void) const { return button; };
	void setButton(int bouton, bool etat);
	void gestionInputs(sf::RenderWindow &window);
	void getInput(sf::RenderWindow &window);

private:  
	static Input *instance;
	Input();
	void onKey(sf::RenderWindow &window, sf::Keyboard::Key &key, bool isPressed);

	sf::Event event;
	Button button;

	enum{ up, down, right, left, attack, jump, enter };
};
#endif
