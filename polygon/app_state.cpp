#include "app_state.h"
#include "globals.h"
#include "as_game.h"
#include "as_menu.h"
#include "as_pause.h"
#include "as_load.h"
#include "as_end.h"

AppState::AppState() {
	quit = false; 
}

AppState * NewAppState(EAppState type) {
	switch (type) {
	case AS_START_MENU:
		return new AS_Menu(); 
		break;
	case AS_PLAYING:
		return new AS_Game(); 
		break;
	case AS_PAUSE:
		return new AS_Pause();
		break;
	case AS_LOAD_EASY:
		return new AS_Load(EASY_MODE);
		break;
	case AS_LOAD_MEDIUM:
		return new AS_Load(MEDIUM_MODE);
		break;
	case AS_LOAD_HARD:
		return new AS_Load(HARD_MODE);
		break;
	case AS_END_YOU_WIN:
		return new AS_End(YOU_WIN);
		break;
	case AS_END_GAME_OVER:
		return new AS_End(GAME_OVER);
		break;
	case AS_NULL:
	default:
		return nullptr; 
		break; 
	}
}

void AppState::Activate() {
}

void AppState::Deactivate() {
}

void AppState::Run() {
}

void AppState::Draw() {
}

void AppState::ProcessInput() {
}

bool AppState::WantsToQuit() {
	return quit;
}

void AppState::SetQuit(bool state) {
	quit = state; 
}

void SetWantedState(EAppState type) {
	g_pWantedState = type; 
}

int GetLastProcessedkey() {
	return g_lastProcessedKey; 
}

void SetLastProcessedkey(int key) {
	g_lastProcessedKey = key;
}