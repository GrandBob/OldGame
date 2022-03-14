#include "input.h"

using namespace std;
using namespace sf;

Input* Input::instance;

Input::Input()
{
	button.left = button.right = button.up = button.down = button.jump = button.attack = button.enter = false;
}

void Input::gestionInputs(RenderWindow &window)
{
	getInput(window);
}

void Input::setButton(int bouton, bool etat)
{
	switch (bouton)
	{
		case up:
			button.up = etat;
			break;
		case down:
			button.down = etat;
			break;
		case right:
			button.right = etat;
			break;
		case left:
			button.left = etat;
			break;
		case attack:
			button.attack = etat;
			break;
		case jump:
			button.jump = etat;
			break;
		case enter:
			button.enter = etat;
			break;
	}
}

void Input::onKey(RenderWindow &window, Keyboard::Key &key, bool isPressed) {
	switch (key)
	{
		case Keyboard::Escape:
			window.close();
			break;
		case Keyboard::Space:
			button.jump = isPressed;
			break;
		case Keyboard::Left:
			button.left = isPressed;
			break;
		case Keyboard::Right:
			button.right = isPressed;
			break;
		case Keyboard::Down:
			button.down = isPressed;
			break;
		case Keyboard::Up:
			button.up = isPressed;
			break;
	}
}

void Input::getInput(RenderWindow &window)
{
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				onKey(window, event.key.code, true);
				break;
			case Event::KeyReleased:
				onKey(window, event.key.code, false);
				break;
		}
	}
}