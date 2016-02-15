#include "as_load.h"
#include "app_state.h"
#include "../include/u-gine.h"
#include "globals.h"

#define EXPECTED_PARAMS_SIZE 15

AS_Load::AS_Load(EMode mode) : m_mode(mode), m_name("") {
}

void AS_Load::Activate() {
	switch (m_mode) {
	case EASY_MODE:
		m_name = String("polygon/easy_mode.txt");
		break;
	case MEDIUM_MODE:
		m_name = String("polygon/medium_mode.txt");
		break;
	case HARD_MODE:
		m_name = String("polygon/hard_mode.txt");
		break;
	case NULL_MODE:
	default:
		break;
	}
}

void AS_Load::Deactivate() {
}

void AS_Load::Run() {
	String fileContent = String::Read(m_name);
	Array<String> params = fileContent.Split("\n");
	if (params.Size() == EXPECTED_PARAMS_SIZE) {
		Game::Instance().SetLevelInfo(params);
		SetWantedState(AS_PLAYING);
	}
	else 
		SetWantedState(AS_START_MENU);
}

void AS_Load::Draw() {
}

void AS_Load::ProcessInput() {
}
