#pragma once
#include "entity.h"

class CAsteroid : public CEntity {
public:
	CAsteroid(double x, double y, int r, int g, int b, int a, double speedx, double speedy, double size, int timer);
	void Run();
	void Draw();	
	double GetTimeLeft() const;
	double GetSpeedX() const;
	double GetSpeedY() const;
private: 
	double m_speedx;
	double m_speedy;
	double m_size;
	double m_timer; 
};

