#include "game.h"
#include "world.h"

#define		SCORE_MESSAGE		"Score: "
#define		SCORE_MARGIN		15

Game* Game::m_game = NULL;

Game::Game() : m_gameOver(false), m_youWin(false), m_endGame(false), m_world(NULL), m_ui(NULL){
}

Game::~Game() {
	delete m_world; 
	delete m_ui;
}

Game & Game::Instance() {
	if (!m_game)
		m_game = new Game();
	return *m_game;
}

void Game::Run() {
	m_world->Run();
	if(m_timer > 0)
		m_timer -= Screen::Instance().ElapsedTime();
}

void Game::Draw() {
	if(m_world)
		m_world->Draw();
	Renderer::Instance().SetColor(255, 255, 255, 255);
	Renderer::Instance().SetBlendMode(Renderer::ALPHA);
	Renderer::Instance().DrawText(m_font, String(SCORE_MESSAGE) + String::FromInt(m_score), SCORE_MARGIN, SCORE_MARGIN);
}

void Game::ProcessInput() {
	if(m_ui)
		m_ui->ProcessInput();
}

bool Game::IsGameOver() const {
	return m_gameOver;
}

void Game::SetGameOver() {
	m_gameOver = true;
	m_endGame = true; 
}

void Game::SetYouWin() {
	m_youWin = true;
	m_endGame = true;
	m_score += m_winBonus;
}

void Game::SetLevelInfo(Array<String> params) {
	m_asteroidsInitialNumber = params[0].ToInt();
	m_asteroidsMinSpeed = params[1].ToInt();
	m_asteroidsMaxSpeed = params[2].ToInt();
	m_asteroidsSize = params[3].ToInt();
	m_asteroidsTimeToDuplicate = params[4].ToInt();
	m_missileRadius = params[5].ToInt();
	m_missileSpeed = params[6].ToInt();
	m_polygonSpeed = params[7].ToInt();
	m_polygonBase = params[8].ToInt();
	m_polygonRotateSpeed = params[9].ToInt();
	m_asteroidPoints = params[10].ToInt();
	m_timeBonus = params[11].ToInt();
	m_winBonus = params[12].ToInt();
	m_timer = params[13].ToInt();
	m_background = params[14];
}

void Game::Initialize() {
	if (!m_world) {
		m_world = new World(); 
		m_world->Init(m_asteroidsInitialNumber, m_asteroidsMinSpeed, m_asteroidsMaxSpeed, m_asteroidsSize, m_asteroidsTimeToDuplicate, m_missileRadius, m_missileSpeed, m_polygonSpeed, m_polygonBase, m_polygonRotateSpeed, m_background);
	}	
	if (!m_ui) {
		m_ui = new UInterface(); 
		m_ui->Init(m_world);
	}
	m_font = ResourceManager::Instance().LoadFont("data/monospaced.png");
	m_gameOver = false;
	m_youWin = false; 
	m_score = 0;
}

void Game::End() {
	if (m_world) {
		m_world->End(); 
		m_world = NULL; 
	}
	if (m_ui) {
		m_ui->End(); 
		m_ui = NULL;
	}	
}

double Game::GetScore() const {
	return m_score;
}

bool Game::IsYouWin() const {
	 return m_youWin; 
}

void Game::AddScoreAsteroidPoints() {
	if (m_timer > 0)
		m_score += m_asteroidPoints + m_timeBonus;
	else
		m_score += m_asteroidPoints;
}

bool Game::IsEndGame() const {
	return m_endGame;
}