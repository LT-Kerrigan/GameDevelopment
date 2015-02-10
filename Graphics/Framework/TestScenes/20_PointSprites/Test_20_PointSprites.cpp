/*******************************************************************************************
*	          .--.																		   *
*	::\`--._,'.::.`._.--'/::			@author Ana M. Mihut		@module Graphics       *
*	::::. `  __::__ ' .:::::   			@alias  LT-Kerrigan			@date 23.08.2014	   *
*	::::::-:.`'..`'.:-::::::			@link								               *
*	::::::::\ `--' /::::::::			@detail	Main	- testing point sprites		       *
*																						   *
********************************************************************************************/

#pragma comment(lib, "nclgl.lib")

#include "../../GraphicsFramework/window.h"
#include "Renderer.h"

int main()	{
	Window w("Test_20_PointSprites", 800, 600, false);

	if (!w.HasInitialised()) {
		return -1;
	}

	Renderer renderer(w);
	if (!renderer.HasInitialised()) {
		return -1;
	}

	while (w.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)){
		renderer.RenderScene();
	}

	return 0;
}