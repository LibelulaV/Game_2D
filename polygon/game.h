#ifndef GAME_H
#define GAME_H

#include "../include/u-gine.h"

#include <list>
#include <stdlib.h>

#include "world.h"
#include "user_interface.h"

class Game {
public:
	static Game& Instance();
	void Initialize();
	void Run();
	void Draw();
	void ProcessInput();
	void SetGameOver();
	void SetYouWin();
	void SetLevelInfo(Array<String> params);
	void AddScoreAsteroidPoints();	
	void End();
	double GetScore() const;
	bool IsYouWin() const;
	bool IsGameOver() const; 
	bool IsEndGame() const;
protected: 
	Game();
	~Game();
private: 
	static Game *  m_game; 
	World * m_world;
	UInterface * m_ui;
	Font * m_font;
	bool m_gameOver;
	bool m_endGame;
	bool m_youWin;
	int m_asteroidsInitialNumber; 
	double m_asteroidsMinSpeed;
	double m_asteroidsMaxSpeed;
	double m_asteroidsSize; 
	int m_asteroidsTimeToDuplicate; 
	double m_missileRadius; 
	double m_missileSpeed;
	double m_polygonSpeed; 
	double m_polygonBase; 
	double m_polygonRotateSpeed; 
	String m_background; 
	double m_score;
	double m_timeBonus;
	double m_timer; 
	double m_winBonus; 
	double m_asteroidPoints; 
};

#endif
