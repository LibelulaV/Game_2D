#include "world.h"
#include "entity.h"
#include "missile.h"
#include "asteroid.h"
#include "spaceship.h"
#include "game.h"

#include <math.h>

#define		ASTEROIDS_FREE_SPACE	200

World::World() {
}

World::~World() {
}

void World::Run() {
	// RUN 
	for (std::list<CEntity*>::iterator it = m_entities.begin(); it != m_entities.end(); it++) {
		(*it)->Run(); 
		if ((*it)->GetType() == ET_ASTEROID) {
			if (static_cast<CAsteroid *>(*it)->GetTimeLeft() <= 0) {
				CAsteroid * ast1 = new CAsteroid((*it)->GetX(), (*it)->GetY(), rand() % 255, rand() % 255, rand() % 255, 255, static_cast<CAsteroid *>(*it)->GetSpeedX() * -1, static_cast<CAsteroid *>(*it)->GetSpeedY() * -1, m_asteroidsSize, m_asteroidsTimeToDuplicate);
				CAsteroid * ast2 = new CAsteroid((*it)->GetX(), (*it)->GetY(), rand() % 255, rand() % 255, rand() % 255, 255, static_cast<CAsteroid *>(*it)->GetSpeedX(), static_cast<CAsteroid *>(*it)->GetSpeedY() * -1, m_asteroidsSize, m_asteroidsTimeToDuplicate);
				m_entities.push_back(ast1); 
				m_entities.push_back(ast2);
				m_asteroidsNumber += 2;
				(*it)->SetDestroy(true);
			}
		}
	}
	// COLLITIONS
	// nave - pantalla
	if ((m_polygon->GetY() - m_polygon->GetHeight() / 2 <= 0 || m_polygon->GetY() + m_polygon->GetHeight() / 2 >= Screen::Instance().GetHeight()) ||
		(m_polygon->GetX() - m_polygon->GetWidth() / 2 <= 0 || m_polygon->GetX() + m_polygon->GetWidth() / 2 >= Screen::Instance().GetWidth()))
		Game::Instance().SetGameOver(); 	
	else {
		// entidad - entidad
		for (std::list<CEntity*>::iterator it1 = m_entities.begin(); it1 != m_entities.end(); it1++) {
			CEntity * entity1 = (*it1); 
			std::list<CEntity*>::iterator next = it1; 
			next++; 
			for (std::list<CEntity*>::iterator it2 = next; it2 != m_entities.end(); it2++) {
				CEntity * entity2 = (*it2);
				//CheckCollition(entity1, entity2);
			}
		}
		// ERASE
		std::list<CEntity*>::iterator it = m_entities.begin();
		while (it != m_entities.end()) {
			if ((*it)->ToDestroy()) {
				if ((*it)->GetType() == ET_ASTEROID)
					m_asteroidsNumber--;
				delete (*it);
				it = m_entities.erase(it);
			}
			else
				it++;
		}
		// Check you win
		if (m_asteroidsNumber <= 0) {
			Game::Instance().SetYouWin();
		}
	}
}

void World::CheckCollition(CEntity * ent1, CEntity * ent2) {
	double asteroidCenterX;
	double asteroidCenterY;
	double asteroidRadius; 
	if (ent1->GetType() == ET_ASTEROID) {
		asteroidCenterX = ent1->GetX() + m_asteroidsSize / 2;
		asteroidCenterY = ent1->GetY() + m_asteroidsSize / 2;
		asteroidRadius = Distance(asteroidCenterX, asteroidCenterY, ent1->GetX(), ent1->GetY());
		if (ent2->GetType() == ET_SPACESHIP) {
			if (asteroidRadius + m_polygon->GetWidth() >= Distance(asteroidCenterX, asteroidCenterY, m_polygon->GetX(), m_polygon->GetY()))
				Game::Instance().SetGameOver();
		}
		else if (ent2->GetType() == ET_MISSILE) {
			if (asteroidRadius + m_missileRadius >= Distance(asteroidCenterX, asteroidCenterY, ent2->GetX(), ent2->GetY()) && !ent1->ToDestroy() && !ent2->ToDestroy()) {
				ent1->SetDestroy(true); 
				ent2->SetDestroy(true); 
				Game::Instance().AddScoreAsteroidPoints();
			}
		}
	}
	else if (ent2->GetType() == ET_ASTEROID) {
		asteroidCenterX = ent2->GetX() + m_asteroidsSize / 2;
		asteroidCenterY = ent2->GetY() + m_asteroidsSize / 2;
		asteroidRadius = Distance(asteroidCenterX, asteroidCenterY, ent2->GetX(), ent2->GetY());
		if (ent1->GetType() == ET_SPACESHIP) {
			if (asteroidRadius + m_polygon->GetWidth() >= Distance(asteroidCenterX, asteroidCenterY, m_polygon->GetX(), m_polygon->GetY()) && !ent1->ToDestroy() && !ent2->ToDestroy())
				Game::Instance().SetGameOver();
		}
		else if (ent1->GetType() == ET_MISSILE) {
			if (asteroidRadius + m_missileRadius >= Distance(asteroidCenterX, asteroidCenterY, ent1->GetX(), ent1->GetY())) {
				ent1->SetDestroy(true);
				ent2->SetDestroy(true);
				Game::Instance().AddScoreAsteroidPoints();
			}
		}
	}
}

void World::Draw() {
	Renderer::Instance().SetBlendMode(Renderer::SOLID);
	Renderer::Instance().SetColor(150, 150, 150,  255); 
	Renderer::Instance().DrawImage(m_background, 0, 0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight()); 
	for (std::list<CEntity*>::iterator it = m_entities.begin(); it != m_entities.end(); it++)
		(*it)->Draw();
}

void World::End() { 
	std::list<CEntity*>::iterator it = m_entities.begin();
	while (it != m_entities.end()) {
		delete (*it);
		it = m_entities.erase(it);
	}
	m_entities.clear(); 
}

void World::Init(int asteroidsInitialNumber, double asteroidsMinSpeed, double asteroidsMaxSpeed, double asteroidsSize, double asteroidsTimeToDuplicate, double missileRadius, double missileSpeed, double polygonSpeed, double polygonBase, double polygonRotateSpeed, String background) {
	m_asteroidsNumber = asteroidsInitialNumber;
	m_asteroidsSize = asteroidsSize;
	m_asteroidsTimeToDuplicate = asteroidsTimeToDuplicate;
	m_missileRadius = missileRadius;
	m_missileSpeed = missileSpeed; 
	m_background = ResourceManager::Instance().LoadImage(background);

	m_polygon = new CSpaceship(Screen::Instance().GetWidth()/2, Screen::Instance().GetHeight() / 2, polygonBase, polygonBase, 0, polygonRotateSpeed, polygonSpeed);
	m_entities.push_back(m_polygon);

	for (int i = 0; i < asteroidsInitialNumber; i++) {
		double coordX = Screen::Instance().GetWidth() / 2;
		double coordY = Screen::Instance().GetHeight() / 2;
		while (coordX < Screen::Instance().GetWidth()/2 + ASTEROIDS_FREE_SPACE && coordX > Screen::Instance().GetWidth() / 2 - ASTEROIDS_FREE_SPACE)
			coordX = (double)(rand() % (int)(Screen::Instance().GetWidth() - (int)(asteroidsSize)));
		while (coordY < Screen::Instance().GetHeight() / 2 + ASTEROIDS_FREE_SPACE && coordY > Screen::Instance().GetHeight() / 2 - ASTEROIDS_FREE_SPACE)
			coordY = (double)(rand() % (int)(Screen::Instance().GetHeight() - (int)(asteroidsSize))); 
		CAsteroid * asteroid = new CAsteroid(coordX, coordY, rand() % 255, rand() % 255, rand() % 255, 255, (double)(rand() % (int)(asteroidsMaxSpeed - asteroidsMinSpeed) + asteroidsMinSpeed), (double)(rand() % (int)(asteroidsMaxSpeed - asteroidsMinSpeed) + asteroidsMinSpeed), asteroidsSize, asteroidsTimeToDuplicate);
		m_entities.push_back(asteroid);
	}
}

void World::ShootMissile() {
	CMissile * missile = new CMissile(m_polygon->GetX(), m_polygon->GetY(), m_polygon->GetAngle(), m_missileRadius, 100);
    m_entities.push_back(missile);

}

CSpaceship* World::GetSpaceship() const {
	return m_polygon;
}