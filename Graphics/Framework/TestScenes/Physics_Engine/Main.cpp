/******************************************************************************
- 'Quit' function, which will destroy everything, and will halt and post a quit message 
- The Window class now also brings the console window into focus ini ts destructor
- each class initialised in the main file to have a number of 'error strings' to output in this function in
order to quickly track down what has gone wrong 

Window is a single class, instantiated and destroyed via static functions. 
*/

#include "../../nclgl/Window.h"
#include "TestEngine.h"

#pragma comment(lib, "nclgl.lib")

int Quit(bool pause = false, const string &reason = "") {
	PhysicsEngine::Destroy();
	Window::Destroy();
	Renderer::Destroy();

	if (pause) {
		std::cout << reason << std::endl;
		system("PAUSE");
	}

	return 0;
}

int main() {
	if (!Window::Initialise("Game Technologies", 1280, 800, false)) {
		return Quit(true, "Window failed to initialise!");
	}

	if (!Renderer::Initialise()) {
		return Quit(true, "Renderer failed to initialise!");
	}

	PhysicsEngine::Initialise();

	TestEngine* game = new TestEngine();

	Window::GetWindow().LockMouseToWindow(true);
	Window::GetWindow().ShowOSPointer(false);

	while (Window::GetWindow().UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)){
		float msec = Window::GetWindow().GetTimer()->GetTimedMS();	//How many milliseconds since last update?

		game->UpdateCore(msec);	//Update our 'sybsystem' logic (renderer and physics!)
		game->UpdateGame(msec);	//Update our game logic
	}

	delete game;	//Done with our game now...bye bye!
	return Quit();
}

