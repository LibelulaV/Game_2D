#include "as_menu.h"
#include "app_state.h"
#include "as_game.h"
#include "../include/u-gine.h"
#include "globals.h"

AS_Game::AS_Game() {
}

void AS_Game::Activate() {
	Game::Instance().Initialize(); 
	m_processKey = false; 
}

void AS_Game::Deactivate() {
}

void AS_Game::Run() {
	Game::Instance().Run();

	if (Game::Instance().IsEndGame()){
		if (Game::Instance().IsGameOver())
			SetWantedState(EAppState::AS_END_GAME_OVER);
		else if (Game::Instance().IsYouWin())
			SetWantedState(EAppState::AS_END_YOU_WIN);
	}
}

void AS_Game::Draw() {
	Game::Instance().Draw();
}

void AS_Game::ProcessInput() {
	if (m_processKey) {
		if (Screen::Instance().KeyPressed(GLFW_KEY_ENTER)) {
			SetLastProcessedkey(GLFW_KEY_ENTER);
			m_processKey = false;
			SetWantedState(EAppState::AS_PAUSE);
		}
		else if (Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
			SetLastProcessedkey(GLFW_KEY_ESC);
			m_processKey = false;
			SetWantedState(EAppState::AS_START_MENU);
		}
		else 
			Game::Instance().ProcessInput(); 
	}
	else {
		if (Screen::Instance().KeyReleased(GetLastProcessedkey()))
			m_processKey = true;
	}
}
