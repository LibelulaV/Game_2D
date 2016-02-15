#include "missile.h"
#include "entity.h"
#include "game.h"


CMissile::CMissile(double x, double y, double angle, double radius, double speed) : CEntity(ET_MISSILE, x, y, 255, 255, 255, 255) {
	m_angle = angle; 
	m_radius = radius; 
	m_speed = speed; 
}

void CMissile::Run() {
	double x = this->GetX();
	double y = this->GetY(); 

	x += m_speed * Screen::Instance().ElapsedTime() * DegCos(m_angle);
	y += m_speed * Screen::Instance().ElapsedTime() * -DegSin(m_angle);

    if (x - m_radius <= 0 || x + m_radius >= Screen::Instance().GetWidth() || y - m_radius <= 0 || y + m_radius >= Screen::Instance().GetHeight()) 
		SetDestroy(true);
	else 
		SetPosition(x, y);
}

void CMissile::Draw() {
	Renderer::Instance().SetBlendMode(Renderer::SOLID);
    Renderer::Instance().SetColor(this->GetR(), this->GetG(), this->GetB(), this->GetA());
	Renderer::Instance().DrawEllipse(this->GetX(), this->GetY(), m_radius, m_radius);
}
