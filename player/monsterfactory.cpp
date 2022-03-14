#include "monsterfactory.h"
#include "jumpper.h"
#include "tank.h"
#include "runner.h"

MonsterFactory::MonsterFactory()
{

}

Monster * MonsterFactory::getInstance(int MonsterID)
{
	Monster* tmp = nullptr;

	switch (MonsterID) {
		case 0:
			tmp = new Jumpper();
			break;
		case 1:
			tmp = new Tank();
			break;
		case 2:
			tmp = new Runner();
			break;
		default:
			tmp = nullptr;
			break;
	}
	return tmp;
}
