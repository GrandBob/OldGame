#ifndef MONSTERFACTORY_H
#define MONSTERFACTORY_H

#include "monster.h"

class MonsterFactory
{
public:
	MonsterFactory();
	static Monster* getInstance(int MonsterID);

private:

};

#endif // !MONSTERFACTORY_H