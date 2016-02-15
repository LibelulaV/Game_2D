#include "app_state.h"
#include "globals.h"

#include <time.h>
#include <stdlib.h>

#include "../include/u-gine.h"

AppState * g_pCurrentState;
EAppState g_pWantedState;
int g_lastProcessedKey = -1; 

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);
	srand(time(NULL));

	g_pWantedState = AS_NULL;
	g_pCurrentState = NewAppState(AS_START_MENU);
	g_pCurrentState->Activate();

	while (!g_pCurrentState->WantsToQuit() && Screen::Instance().IsOpened()) {
		if (g_pWantedState != AS_NULL) {
			
			g_pCurrentState->Deactivate();
			delete g_pCurrentState; 
	
			g_pCurrentState = NewAppState(g_pWantedState);

			g_pCurrentState->Activate();

			g_pWantedState = AS_NULL; 
		}

		g_pCurrentState->ProcessInput();
		g_pCurrentState->Run();
		g_pCurrentState->Draw();

		Screen::Instance().Refresh();
		Renderer::Instance().Clear(0, 0, 0);
	}
	ResourceManager::Instance().FreeResources();
	return 0;
}