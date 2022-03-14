#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../structure/s_texture.h"
#include "../def.h"

class GUI;

class MyButton
{
public:
	MyButton();
	MyButton(struct s_Texture textures, bool disabled = false);
	void manageButton(sf::RenderWindow &window, void(GUI::*ptr)(void) = nullptr);
	
	void setDisabled(bool etat);
	bool isDisabled(void);
	
	void setActive(bool etat);
	bool isActive(void);
	
	void setPosition(sf::Vector2f);
	sf::Vector2f getPosition(void);

private:
	GUI *link;

	bool active;
	bool disabled;

	sf::FloatRect buttonSize;
	sf::Vector2f buttonPosition;

	sf::Texture buttonWaitState;
	sf::Texture buttonHoverState;
	sf::Texture buttonClickState;
	sf::Texture buttonLockState;

	sf::Sprite buttonSprite;

	void Draw(sf::RenderWindow &window);
	void Update(sf::RenderWindow &window) {};
	void onClick(sf::RenderWindow &window, void(GUI::*ptr)(void) = nullptr);
	bool mouseOver(sf::Vector2i localPosition, sf::Vector2u windowSize);
};
#endif 