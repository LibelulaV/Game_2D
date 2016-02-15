#ifndef START_MENU_STATE_H
#define START_MENU_STATE_H

#include "app_state.h"
#include "../include/u-gine.h"

class AS_Menu : public AppState {
public:
	AS_Menu();
	void Activate();
	void Deactivate();
	void Run();
	void Draw();
	void ProcessInput();
private: 
	String GetModeText(int mode);
	void DrawTitle();
	Font * m_font;
	Image * m_background;
	int m_option; 
	bool m_processKey;
};

#endif
