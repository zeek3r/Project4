#include <iostream>
#include "Engine/Graphics/Graphics.h"
#include "Engine/Graphics/TextureManager.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Other/Tile.h"
#include "Engine/Other/Level.h"
#include "Engine/Other/Time.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"


Display display;
InputManager input;
Time t;
float dt = 0.0f;
void update(float dt) {

}
int main(int argc, char* argv[]) {
	display.init_display(1280, 960, "asd");
	while (!input.hasQuit) {
		input.pollEvents();
		update(t.deltaTime());
		display.clear_display();
		{
			ImGui::Begin("Stats");

			ImGui::End();
		}
		display.draw_gui();
		display.present_display();
	}
	return 0;
}