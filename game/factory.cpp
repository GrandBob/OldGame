#include "factory.h"

AbstractEntity* Factory::getInstance(ENTITY entityID)
{
	AbstractEntity* tmp = 0;

	switch (entityID) {
	case GUI:
		tmp = GUI::getInstance();
		break;
	case MAP:
		tmp = Map::getInstance();
		break;
	case PLAYER:
		tmp = Player::getInstance();
		break;
	default:
		tmp = NULL;
		break;
	}
	return tmp;
}

Factory::Factory() {

}