#ifndef END_STATE_H
#define END_STATE_H

#include "app_state.h"
#include "../include/u-gine.h"

enum EEndGame {
	NULL_END,
	YOU_WIN,
	GAME_OVER
};

class AS_End : public AppState {
public:
	AS_End(EEndGame mode);
	void Activate();
	void Deactivate();
	void Run();
	void Draw();
	void ProcessInput();
	String GetOptionText(int mode);
private:
	EEndGame m_mode;
	Font * m_font;
	Image * m_background;
	int m_option;
	bool m_processKey;
};

#endif
