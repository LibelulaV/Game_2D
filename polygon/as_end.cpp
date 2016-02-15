#include "as_end.h"
#include "game.h"

#define TOTAL_OPTIONS 2
#define PLAY_AGAIN_TEXT "PLAY AGAIN"
#define QUIT_GAME_TEXT "QUIT GAME"
#define WIN_MESSAGE "CONGRATULATIONS!!!!"
#define SCORE_MESSAGE "Final Score: "

AS_End::AS_End(EEndGame mode) : m_mode(mode) {
}

void AS_End::Activate() {
	if (m_mode) {
		if (m_mode == YOU_WIN)
			m_background = ResourceManager::Instance().LoadImage("polygon/you_win_bg.jpg");
		else if (m_mode == GAME_OVER)
			m_background = ResourceManager::Instance().LoadImage("polygon/game_over_bg.jpg");
	}
	m_font = ResourceManager::Instance().LoadFont("data/monospaced.png");
	m_processKey = false;
	m_option = 0;
}

void AS_End::Deactivate() {
}

void AS_End::Run() {
}

void AS_End::Draw() {
	int row_x;
	int row_y;
	Renderer::Instance().SetBlendMode(Renderer::SOLID);
	Renderer::Instance().SetColor(255, 255, 255, 255);
	Renderer::Instance().DrawImage(m_background, 0, 0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight());
	Renderer::Instance().SetBlendMode(Renderer::ALPHA);
	Renderer::Instance().DrawText(m_font, String(SCORE_MESSAGE) + String::FromInt(Game::Instance().GetScore()), Screen::Instance().GetWidth() / 2 - (m_font->GetTextWidth(String(SCORE_MESSAGE) + String::FromInt(Game::Instance().GetScore()))/2), Screen::Instance().GetHeight() / 3 - 3 * m_font->GetTextHeight(String(SCORE_MESSAGE)));
	row_y = 2 * Screen::Instance().GetHeight() / 3;
	if (m_mode == YOU_WIN)
		Renderer::Instance().DrawText(m_font, WIN_MESSAGE, Screen::Instance().GetWidth() / 2 - m_font->GetTextWidth(WIN_MESSAGE) / 2, row_y - 4 * m_font->GetTextHeight(WIN_MESSAGE));
	for (int i = 0; i < TOTAL_OPTIONS; i++) {
		row_x = Screen::Instance().GetWidth() / 2 - m_font->GetTextWidth(GetOptionText(i)) / 2;
		if (m_option == i)
			Renderer::Instance().SetColor(255, 0, 127, 255);
		else
			Renderer::Instance().SetColor(255, 255, 255, 255);
		Renderer::Instance().DrawText(m_font, GetOptionText(i), row_x, row_y + m_font->GetTextHeight(GetOptionText(i))*i);
		row_y += m_font->GetTextHeight(GetOptionText(i));
	}
}

void AS_End::ProcessInput() {
	if (m_processKey) {
		if (Screen::Instance().KeyPressed(GLFW_KEY_ENTER)) {
			SetLastProcessedkey(GLFW_KEY_ENTER);
			m_processKey = false;
			if (m_option) 
				this->SetQuit(true);
			else
				SetWantedState(EAppState::AS_START_MENU);
		}
		else if (Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
			SetLastProcessedkey(GLFW_KEY_ESC);
			m_processKey = false;
			this->SetQuit(true);
		}
		else if (Screen::Instance().KeyPressed(GLFW_KEY_UP)) {
			SetLastProcessedkey(GLFW_KEY_UP);
			m_processKey = false;
			if (!m_option)
				m_option = 1;
			else
				m_option--;
		}
		else if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN)) {
			SetLastProcessedkey(GLFW_KEY_DOWN);
			m_processKey = false;
			if (!m_option)
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

String AS_End::GetOptionText(int mode) {
	switch (mode) {
	case 0:
		return PLAY_AGAIN_TEXT;
		break;
	case 1:
		return QUIT_GAME_TEXT;
		break;
	default:
		return NULL;
		break;
	}
}
