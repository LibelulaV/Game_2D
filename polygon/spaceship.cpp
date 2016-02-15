#include "spaceship.h"
#include "entity.h"
#include "../include/u-gine.h"

CSpaceship::CSpaceship(double x, double y, double width, double height, double angle, double rotateSpeed, double speed) : CEntity(ET_SPACESHIP, x, y, 255, 255, 255, 255) {
	m_height = height;
	m_width = width;
	m_angle = angle;
	m_rotateSpeed = rotateSpeed;
	m_speed = speed;
}

void CSpaceship::SetAngle(double angle) {
	m_angle = angle;
}

double CSpaceship::GetAngle() const {
	return m_angle;
}

double CSpaceship::GetHeight() const {
	return m_height;
}
double CSpaceship::GetWidth() const {
	return m_width;
}

double CSpaceship::GetRotateSpeed() const {
	return m_rotateSpeed;
}

double CSpaceship::GetSpeed() const {
	return m_speed;
}

void CSpaceship::Run() {
}

void CSpaceship::Draw() {
	Renderer::Instance().PushMatrix();
	Renderer::Instance().TranslateMatrix(this->GetX(), this->GetY(), 0);
	Renderer::Instance().RotateMatrix(m_angle, 0, 0, -1);
	Renderer::Instance().SetColor(this->GetR(), this->GetG(), this->GetB(), this->GetA());
	Renderer::Instance().DrawTriangle(-m_width / 2, -m_height / 2, m_width, m_height);
	Renderer::Instance().PopMatrix();
}
