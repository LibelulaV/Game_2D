#ifndef APP_STATE_H
#define APP_STATE_H

enum EAppState {
	AS_NULL,
	AS_START_MENU,
	AS_PLAYING,
	AS_PAUSE,
	AS_LOAD_EASY,
	AS_LOAD_MEDIUM, 
	AS_LOAD_HARD, 
	AS_END_YOU_WIN, 
	AS_END_GAME_OVER
};

class AppState {
public:
	AppState();
	virtual ~AppState() {}
	virtual void Activate();
	virtual void Deactivate();
	virtual void Run(); 
	virtual void Draw();
	virtual void ProcessInput();
	virtual bool WantsToQuit();
	void SetQuit(bool state);
private:
	bool quit;
};

AppState * NewAppState(EAppState type);

void SetWantedState(EAppState type);
int GetLastProcessedkey(); 
void SetLastProcessedkey(int key);

#endif