#include "asteroid.h"
#include "entity.h"
#include "game.h"

CAsteroid::CAsteroid(double x, double y, int r, int g, int b, int a, double speedx, double speedy, double size, int timer) : CEntity(ET_ASTEROID, x, y, r, g, b, a) {
	m_speedx = speedx; 
	m_speedy = speedy; 
	m_size = size; 
	m_timer = timer;
}

void CAsteroid::Run() {
	double x = this->GetX();
	double y = this->GetY();

	x += m_speedx * Screen::Instance().ElapsedTime();
	y += m_speedy * Screen::Instance().ElapsedTime();

	if (x <= 0) {
		m_speedx *= -1;
		x = 0; 
	}
	else if (x + m_size >= Screen::Instance().GetWidth()) {
		m_speedx *= -1;
		x = Screen::Instance().GetWidth() - m_size;
	}

	if (y <= 0) {
		m_speedy *= -1;
		y = 0;
	}
	else if (y + m_size >= Screen::Instance().GetHeight()) {
		m_speedy *= -1;
		y = Screen::Instance().GetHeight() - m_size;
	}
	SetPosition(x, y);
	m_timer -= Screen::Instance().ElapsedTime();
}

double CAsteroid::GetTimeLeft() const {
	return m_timer; 
}

double CAsteroid::GetSpeedX() const {
	return m_speedx;
}

double CAsteroid::GetSpeedY() const {
	return m_speedy;
}

void CAsteroid::Draw() {
	Renderer::Instance().SetBlendMode(Renderer::SOLID);
	Renderer::Instance().SetColor(this->GetR(), this->GetG(), this->GetB(), this->GetA());
	Renderer::Instance().DrawRect(this->GetX(), this->GetY(), m_size, m_size);
}


