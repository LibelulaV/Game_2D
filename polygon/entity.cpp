#include "entity.h"

CEntity::CEntity(EEntityType type, double x, double y, int r, int g, int b, int a) {
	m_type = type;
	m_x = x;
	m_y = y;
	m_r = r;
	m_g = g;
	m_b = b;
	m_a = a;
	m_destroy = false; 
}

CEntity::~CEntity() {
}

void CEntity::Run() {
}

void CEntity::Draw() {
}

void CEntity::SetX(double x) {
	m_x = x; 
}

void CEntity::SetY(double y) {
	m_y = y; 
}

void CEntity::SetPosition(double x, double y) {
	m_x = x; 
	m_y = y; 
}

double CEntity::GetX()  const {
	return m_x;
}

double CEntity::GetY() const {
	return m_y;
}

int CEntity::GetR() const {
	return m_r;
}

int CEntity::GetB() const {
	return m_b;
}

int CEntity::GetG() const {
	return m_g;
}

int CEntity::GetA() const {
	return m_a;
}

bool CEntity::ToDestroy() const {
	return m_destroy;
}

void CEntity::SetDestroy(bool state) {
	m_destroy = state; 
}

void CEntity::SetRGBA(int r, int g, int b, int a) {
	m_r = g;
	m_g = g;
	m_b = b;
	m_a = a;
}

EEntityType CEntity::GetType() const {
	return m_type;
}
