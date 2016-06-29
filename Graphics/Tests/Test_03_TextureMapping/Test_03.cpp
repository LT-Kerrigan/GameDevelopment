#pragma comment(lib, "nclgl_core.lib")

#include "nclgl_core/Window.h"
#include "Renderer.h"

int main()	{
	Window w("Test_03_TextureMapping", 800, 600, false);

	if (!w.HasInitialised()) {
		return -1;
	}

	Renderer renderer(w);
	if (!renderer.HasInitialised()) {
		return -1;
	}

	float rotate = 0.0f;

	while (w.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)){

		if (Window::GetKeyboard()->KeyDown(KEYBOARD_LEFT)) {
			--rotate;
			renderer.UpdateTextureMatrix(rotate);
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_RIGHT)) {
			++rotate;
			renderer.UpdateTextureMatrix(rotate);
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_1)) {
			renderer.ToggleFiltering();
		}

		if (Window::GetKeyboard()->KeyDown(KEYBOARD_2)) {
			renderer.ToggleRepeating();
		}
		//renderer.UpdateScene(w.GetTimer()->GetTimedMS());
		renderer.RenderScene();
	}
	return 0;
}