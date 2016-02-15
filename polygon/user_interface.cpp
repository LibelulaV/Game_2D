#include "user_interface.h"
#include "game.h"

#define		GLFW_KEY_W			87
#define 	GLFW_KEY_S			83
#define 	GLFW_KEY_A			65
#define 	GLFW_KEY_D			68
#define 	GLFW_KEY_SPACE		32

#define		SHOOT_DELAY			0.4

UInterface::UInterface() : m_polygon(NULL){
}

UInterface::~UInterface() {
}

void UInterface::ProcessInput() {
	// Rotation
	if (Screen::Instance().KeyPressed(GLFW_KEY_LEFT))
		m_polygon->SetAngle(m_polygon->GetAngle() +  Screen::Instance().ElapsedTime() * m_polygon->GetRotateSpeed());
	else if (Screen::Instance().KeyPressed(GLFW_KEY_RIGHT))
 		m_polygon->SetAngle(m_polygon->GetAngle() - Screen::Instance().ElapsedTime() * m_polygon->GetRotateSpeed());
	// Movement
	if (Screen::Instance().KeyPressed(GLFW_KEY_W))
		m_polygon->SetY(m_polygon->GetY() - Screen::Instance().ElapsedTime() * m_polygon->GetSpeed());
	else if (Screen::Instance().KeyPressed(GLFW_KEY_S))
		m_polygon->SetY(m_polygon->GetY() + Screen::Instance().ElapsedTime() * m_polygon->GetSpeed());
	else if (Screen::Instance().KeyPressed(GLFW_KEY_A))
		m_polygon->SetX(m_polygon->GetX() - Screen::Instance().ElapsedTime() * m_polygon->GetSpeed());
	else if (Screen::Instance().KeyPressed(GLFW_KEY_D))
		m_polygon->SetX(m_polygon->GetX() + Screen::Instance().ElapsedTime() * m_polygon->GetSpeed());
	// Missiles
	if (Screen::Instance().KeyPressed(GLFW_KEY_SPACE)) {
		if (m_shootDelay <= 0) {
			m_world->ShootMissile();
			m_shootDelay = SHOOT_DELAY;
		}
		else
			m_shootDelay -= Screen::Instance().ElapsedTime(); 
	}
	else if (Screen::Instance().KeyReleased(GLFW_KEY_SPACE)) {
		m_shootDelay = 0;
	}
}

void UInterface::Init(World * world) {
	m_world = world; 
	m_polygon = world->GetSpaceship(); 
	m_shootDelay = 0; 
}

void UInterface::End() {
}
