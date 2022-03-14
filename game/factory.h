#ifndef FACTORY_H
#define FACTORY_H

class Factory
{
public:
	enum ENTITY {
		GUI = 1,
		MAP,
		PLAYER
	};

	Factory();
	static AbstractEntity* getInstance(ENTITY entityID);
};

#endif