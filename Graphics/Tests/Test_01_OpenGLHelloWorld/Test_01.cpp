#pragma comment(lib, "nclgl_core")

#include "nclgl_core/Window.h"
#include "Renderer.h"

int main()	{
	Window w("Test_01_HelloWorldOpenGL", 800, 600, false);

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