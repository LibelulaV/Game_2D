#include "as_pause.h"
#include "../include/u-gine.h"
#include "globals.h"

#define		PAUSE_MESSAGE	"Press ENTER to continue"

AS_Pause::AS_Pause() {
}

void AS_Pause::Activate() {
	m_font = ResourceManager::Instance().LoadFont("data/monospaced.png");
	m_text = String(PAUSE_MESSAGE);
	m_x = Screen::Instance().GetWidth() / 2 - m_font->GetTextWidth(m_text) / 2;
	m_y = Screen::Instance().GetHeight() / 2 - m_font->GetTextHeight(m_text) / 2;
	m_processKey = false;
}

void AS_Pause::Deactivate() {
}

void AS_Pause::Run() {
}

void AS_Pause::Draw() {
	Game::Instance().Draw(); 
	Renderer::Instance().SetBlendMode(Renderer::ALPHA);
	Renderer::Instance().SetColor(255, 0, 127, 255);
	Renderer::Instance().DrawText(m_font, m_text, m_x, m_y);
}

void AS_Pause::ProcessInput() {
	if (m_processKey) {
		if (Screen::Instance().KeyPressed(GLFW_KEY_ENTER)) {
			SetWantedState(EAppState::AS_PLAYING);
			SetLastProcessedkey(GLFW_KEY_ENTER);
		}
		else if (Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
			SetLastProcessedkey(GLFW_KEY_ESC);
			this->SetQuit(true);
		}
	}
	else {
		if (Screen::Instance().KeyReleased(GetLastProcessedkey()))
			m_processKey = true;
	}
}
