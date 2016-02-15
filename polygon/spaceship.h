#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "entity.h"

class CSpaceship : public CEntity {
public:
	CSpaceship(double x, double y, double width, double height, double angle, double rotateSpeed, double speed);
	void SetAngle(double angle);
	double GetAngle() const;
	double GetHeight() const;
	double GetWidth() const;
	double GetRotateSpeed() const;
	double GetSpeed() const;
	void Run(); 
	void Draw(); 
private: 
	double m_angle;
	double m_height;
	double m_width;
	double m_rotateSpeed;
	double m_speed;
};

#endif

