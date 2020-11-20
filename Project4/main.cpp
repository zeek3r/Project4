#include <iostream>
#include "Engine/Graphics/Graphics.h"
#include "Engine/Graphics/TextureManager.h"
#include "Engine/Input/InputManager.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"


Display display;
InputManager input;
int main(int argc, char* argv[]) {
	display.init_display(1280, 960, "asd");
	while (!input.hasQuit) {
		input.pollEvents();
		display.clear_display();
		display.draw_gui();
		display.present_display();
	}
	return 0;
}