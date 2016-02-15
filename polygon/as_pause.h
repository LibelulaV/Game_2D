#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "../include/u-gine.h"
#include "app_state.h"

class AS_Pause :
	public AppState
{
public:
	AS_Pause();
	void Activate();
	void Deactivate();
	void Run();
	void Draw();
	void ProcessInput();
private:
	Font * m_font;
	String m_text;
	int m_x;
	int m_y;
	bool m_processKey;
};

#endif
