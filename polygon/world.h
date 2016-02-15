#ifndef WORLD_H
#define WORLD_H

#include "../include/u-gine.h"

#include <list>
#include <stdlib.h>
#include "entity.h"
#include "spaceship.h"

class World {
public:
	World(); 
	~World(); 
	void Run();
	void CheckCollition(CEntity * ent1, CEntity * ent2);
	void Draw();
	void End();
	void Init(int asteroidsInitialNumber, double asteroidsMinSpeed, double asteroidsMaxSpeed, double asteroidsSize, double asteroidsTimeToDuplicate, double missileRadius, double missileSpeed, double polygonSpeed, double polygonBase, double polygonRotateSpeed, String background);
	void ShootMissile();
	CSpaceship* GetSpaceship() const;
private: 
	std::list<CEntity *> m_entities;
	CSpaceship * m_polygon; 
	double m_asteroidsTimeToDuplicate;
	double m_asteroidsNumber;
	double m_asteroidsSize;
	double m_missileRadius;
	double m_missileSpeed;
	Image * m_background;
}; 

#endif

