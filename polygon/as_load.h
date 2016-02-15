#ifndef LOAD_STATE_H
#define LOAD_STATE_H

#include "app_state.h"
#include "../include/u-gine.h"

enum EMode {
	NULL_MODE,
	EASY_MODE, 
	MEDIUM_MODE,
	HARD_MODE
};

class AS_Load : public AppState {
public:
	AS_Load(EMode mode);
	void Activate();
	void Deactivate();
	void Run();
	void Draw();
	void ProcessInput();
private:
	EMode m_mode; 
	String m_name;
};

#endif

