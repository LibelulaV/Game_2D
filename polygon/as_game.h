#ifndef GAME_STATE_H

#define GAME_STATE_H

#include "app_state.h"

class AS_Game : public AppState
{
public:
	AS_Game();
	void Activate();
	void Deactivate();
	void Run();
	void Draw();
	void ProcessInput();
private: 
	bool m_processKey;
};

#endif
