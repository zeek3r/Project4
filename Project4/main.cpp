#include <iostream>
#include "Engine/Graphics/Graphics.h"
#include "Engine/Graphics/TextureManager.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Other/Tile.h"
#include "Engine/Other/Level.h"
#include "Engine/Other/Camera.h"
#include "Engine/Other/Time.h"
#include "Engine/Other/Cursor.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"

Camera camera;
Display display;
Shader shader;
InputManager input;
TextureManager texManager;
Time t;
Level level;
float dt = 0.0f;
GLuint currentTexture;
std::string currentTextureName = "Sprites/db1_blue.png";
Tile* previewTile;
Cursor* cursor;
void place_tile() {
	glm::vec2 mousePos = glm::vec2(input.mouseX, input.mouseY + 960) + camera.position;
	int x = mousePos.x - ((int)mousePos.x % 32);
	int y = mousePos.y - ((int)mousePos.y % 32);
	bool clear = true;
	for (int i = 0; i < level.tiles.size(); i++) {
		if (level.tiles[i]->position.x == x && level.tiles[i]->position.y == y) {
			clear = false;
		}
	}
	if (clear) {
		level.tiles.push_back(new Tile(glm::vec2(x, y), glm::vec2(32, 32)));
		level.tiles.back()->texture = currentTexture;
		level.tiles.back()->texturePath = currentTextureName.c_str();
		std::cout << "Tile placed at " << x << " - " << y << std::endl;
	}
}
void destroy_tile() {
	glm::vec2 mousePos = glm::vec2(input.mouseX, input.mouseY + 960) + camera.position;
	int x = mousePos.x - ((int)mousePos.x % 32);
	int y = mousePos.y - ((int)mousePos.y % 32); 
	for (int i = 0; i < level.tiles.size(); i++) {
		if (level.tiles[i]->position.x == x && level.tiles[i]->position.y == y) {
			level.tiles[i] = level.tiles.back();
			level.tiles.pop_back();
		}
	}
}
void handle_input() {
	if (input.getKey(SDL_SCANCODE_A))
		camera.position.x -= dt;
	if (input.getKey(SDL_SCANCODE_D))
		camera.position.x += dt;
	if (input.getKey(SDL_SCANCODE_W))
		camera.position.y += dt;
	if (input.getKey(SDL_SCANCODE_S))
		camera.position.y -= dt;
	if (input.getMouseDown(SDL_BUTTON_LEFT) && !ImGui::GetIO().WantCaptureMouse) {
		place_tile();
	}
	if (input.getMouse(SDL_BUTTON_LEFT) && !ImGui::GetIO().WantCaptureMouse && input.getKey(SDL_SCANCODE_LSHIFT)) {
		place_tile();
	}
	if (input.getMouseDown(SDL_BUTTON_RIGHT) && !ImGui::GetIO().WantCaptureMouse) {
		destroy_tile();
	}
}
void draw_tile_menu() {
	{
		ImGui::SetNextWindowPos(ImVec2(880, 20));
		ImGui::SetNextWindowSize(ImVec2(400, 400));
		ImGui::Begin("Tile Menu");
		for (int i = 1; i < texManager.textures_tilemap.size() + 1; i++) {
			if (ImGui::ImageButton((ImTextureID)texManager.textures_tilemap[i-1], ImVec2(32, 32))) {
				currentTexture = texManager.textures_tilemap[i-1];
				previewTile->texture = currentTexture;
			}
			if (i % 8  != 0)
				ImGui::SameLine();
		}
		ImGui::End();
	}
}
void update() {

}
void draw_level() {
	for (int i = 0; i < level.tiles.size(); i++) {
		if (level.tiles[i]->position.x < camera.position.x + 1400 && level.tiles[i]->position.x > camera.position.x - 100 && level.tiles[i]->position.y < camera.position.y + 1100 && level.tiles[i]->position.y > camera.position.y - 100) {
			shader.set_uniform_vec2(-camera.position, "position");
			level.tiles[i]->draw();
		}
	}
}
void render() {
	display.clear_display();
	draw_level();
	draw_tile_menu();
	{
		ImGui::SetNextWindowPos(ImVec2(0, 20));
		ImGui::SetNextWindowSize(ImVec2(300, 200));
		ImGui::SetNextWindowCollapsed(false);
		ImGui::Begin("");
		ImGui::Text("FPS:%.1f", ImGui::GetIO().Framerate);
		if (ImGui::Button("Save Level")) level.save("lvl1.asd");
		if (ImGui::Button("Load Level")) level.load("lvl1.asd", &texManager);
		ImGui::End();
	}
	display.draw_gui();
	shader.set_uniform_vec2(glm::vec2(0, 0), "position");
	previewTile->draw();
	shader.set_uniform_vec2(glm::vec2(input.mouseX, input.mouseY + 960-64), "position");
	cursor->draw();
	display.present_display();
}
void init() {
	display.init_display(1280, 960, "asd");
	shader.load_shader("Shaders/shader1");
	shader.use_shader();
	shader.set_uniform_mat4(glm::ortho(0.0f, 1280.0f, 0.0f, 960.0f), "ortho");
	previewTile = new Tile(glm::vec2(10, 800), glm::vec2(32, 32));
	previewTile->texture = texManager.load_texture("Sprites/db1_blue.png");
	cursor = new Cursor;
	cursor->texture = texManager.load_texture("Sprites/cursor.png");
	texManager.generate_tile_map("Sprites/wood_tileset.png");
	currentTexture = texManager.textures_tilemap[0];
}
int main(int argc, char* argv[]) {
	init();
	while (!input.hasQuit) {
		dt = t.deltaTime();
		input.pollEvents();
		handle_input();
		update();
		render();
	}
	return 0;
}