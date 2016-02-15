#include "as_menu.h"
#include "app_state.h"
#include "as_game.h"
#include "../include/u-gine.h"
#include "globals.h"

#define TOTAL_OPTIONS		4
#define EASY_MODE_TEXT		"EASY"
#define MEDIUM_MODE_TEXT	"MEDIUM"
#define HARD_MODE_TEXT		"HARD"
#define QUIT_GAME_TEXT		"QUIT"
#define GAME_TITLE			"POLYGON I"	
#define TITLE_MEASSURES		20

AS_Menu::AS_Menu() {
}

void AS_Menu::Activate() {
	Game::Instance().End();
	m_font = ResourceManager::Instance().LoadFont("data/monospaced.png");
	m_background = ResourceManager::Instance().LoadImage("polygon/start_menu_bg.jpg");
	m_processKey = false; 
	m_option = 0; 
}

void AS_Menu::Deactivate() {
}

void AS_Menu::Run() {
}

void AS_Menu::Draw() {
	int row_x;
	int row_y = Screen::Instance().GetHeight() / 2 - 4 * m_font->GetTextHeight(GetModeText(0));
	Renderer::Instance().SetBlendMode(Renderer::SOLID);
	Renderer::Instance().SetColor(180, 150, 150, 255); 
	Renderer::Instance().DrawImage(m_background, 0, 0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight());
	DrawTitle();
	Renderer::Instance().SetBlendMode(Renderer::ALPHA);
	for (int i = 0; i < TOTAL_OPTIONS; i++) {
		row_x = Screen::Instance().GetWidth() / 2 - m_font->GetTextWidth(GetModeText(i)) / 2;
		if (m_option == i)
			Renderer::Instance().SetColor(255, 0, 127, 255);
		else 
			Renderer::Instance().SetColor(255, 255, 255, 255);
		Renderer::Instance().DrawText(m_font, GetModeText(i), row_x, row_y + m_font->GetTextHeight(GetModeText(i))*i);
		row_y += m_font->GetTextHeight(GetModeText(i));
	}
}

void AS_Menu::ProcessInput() {
	if (m_processKey) {
		if (Screen::Instance().KeyPressed(GLFW_KEY_ENTER)) {
			SetLastProcessedkey(GLFW_KEY_ENTER);
			m_processKey = false;
			if (m_option != 3) {
				switch (m_option) {
				case 0:
					SetWantedState(EAppState::AS_LOAD_EASY);
					break;
				case 2: 
					SetWantedState(EAppState::AS_LOAD_HARD);
					break; 
				case 1: 
				default:
					SetWantedState(EAppState::AS_LOAD_MEDIUM);
					break;
				}
			}
			else 
				this->SetQuit(true);
		}		
		else if (Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
			SetLastProcessedkey(GLFW_KEY_ESC);
			m_processKey = false;
			this->SetQuit(true); 
		}
		else if (Screen::Instance().KeyPressed(GLFW_KEY_UP)) {
			SetLastProcessedkey(GLFW_KEY_UP);
			m_processKey = false;
			if (m_option > 0)
				m_option--;
			else 
				m_option = 3; 
		}
		else if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN)) {
			SetLastProcessedkey(GLFW_KEY_DOWN);
			m_processKey = false;
			if (m_option < 3)
				m_option++;
			else
				m_option = 0;
		}
	}
	else {
		if (Screen::Instance().KeyReleased(GetLastProcessedkey()))
			m_processKey = true; 
	}
}

String AS_Menu::GetModeText(int mode) {
	switch (mode) {
	case 0:
		return EASY_MODE_TEXT;
		break;
	case 1:
		return MEDIUM_MODE_TEXT;
		break;
	case 2:
		return HARD_MODE_TEXT;
		break;
	case 3:
		return QUIT_GAME_TEXT;
		break;
	default:
		return NULL;
		break;
	}
}

void AS_Menu::DrawTitle() {
	int row_x = Screen::Instance().GetWidth() / 2 - (m_font->GetTextWidth(GAME_TITLE ) + TITLE_MEASSURES * String(GAME_TITLE).Length()) / 2;
	int row_y = Screen::Instance().GetHeight() / 4;
	Renderer::Instance().SetBlendMode(Renderer::ALPHA);
	Renderer::Instance().SetColor(48, 228, 241, 255);
	Renderer::Instance().DrawTexWithMeassures(m_font, GAME_TITLE, row_x, row_y, TITLE_MEASSURES, TITLE_MEASSURES);
}
