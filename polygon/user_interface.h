#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "spaceship.h"
#include "world.h"
#include "entity.h"

class UInterface {
public:
	UInterface();
	~UInterface();
	void ProcessInput(); 
	void Init(World * world);
	void End();
private: 
	CSpaceship * m_polygon; 
	World * m_world; 
	double m_shootDelay; 
};

#endif

