#include "button.h"

using namespace std;
using namespace sf;

// Constructeur
MyButton::MyButton(): active(false), disabled(false) {

}

MyButton::MyButton(struct s_Texture textures, bool disabled): active(false)
{
	setDisabled(disabled);

	buttonWaitState = textures.normal;
	buttonHoverState = textures.hover;
	buttonClickState = textures.click;
	buttonLockState = textures.lock;

	buttonSprite.setTexture(buttonWaitState);
	buttonSize = buttonSprite.getGlobalBounds();
	buttonPosition = buttonSprite.getPosition();
}

void MyButton::setActive(bool etat)
{
	active = etat;
}

bool MyButton::isActive(void)
{
	return active;
}

void MyButton::setPosition(sf::Vector2f offset)
{
	buttonSprite.setPosition(offset);
	buttonPosition = buttonSprite.getPosition();
}

sf::Vector2f MyButton::getPosition(void)
{
	return buttonPosition;
}

void MyButton::setDisabled(bool etat)
{
	disabled = etat;
}

bool MyButton::isDisabled(void)
{
	return disabled;
}

void MyButton::Draw(RenderWindow &window)
{
	window.draw(buttonSprite);
}

void MyButton::manageButton(RenderWindow &window, void (GUI::*action)(void))
{
	if (disabled)
		buttonSprite.setTexture(buttonClickState);
	else 
	{
		buttonSprite.setTexture(buttonWaitState);
		if (mouseOver(Mouse::getPosition(window), window.getSize()))
		{
			buttonSprite.setTexture(buttonHoverState);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				buttonSprite.setTexture(buttonClickState);
				onClick(window, action);
			}
		}
	}
	this->Draw(window);
}

bool MyButton::mouseOver(sf::Vector2i localPosition, sf::Vector2u windowSize)
{
	float ratioX, ratioY;

	ratioX = (float)windowSize.x / (float)SCREEN_WIDTH;
	ratioY = (float)windowSize.y / (float)SCREEN_HEIGHT;

	if ((buttonPosition.x * ratioX) <= localPosition.x && ((buttonPosition.x + buttonSize.width) * ratioX) >= localPosition.x)
	{
		if ((buttonPosition.y * ratioY) <= localPosition.y && ((buttonPosition.y + buttonSize.height) * ratioY) >= localPosition.y)
			return true;
	}
	return false;
}

void MyButton::onClick(RenderWindow &window, void (GUI::*ptr)(void))
{
	if (ptr != nullptr)
		(link->*ptr)();
	sleep(seconds(0.1f));
}
