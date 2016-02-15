#ifndef MISSILE_H
#define MISSILE_H

#include "entity.h"

class CMissile :
	public CEntity
{
public:
	CMissile(double x, double y, double angle, double radius, double speed);
	void Run();
	void Draw();
private: 
	double m_angle;
	double m_radius;
	double m_speed;
};

#endif

