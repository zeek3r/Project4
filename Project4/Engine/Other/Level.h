#pragma once
#include "Tile.h"
#include <vector>
#include <fstream>
#include <sstream>
#include "../Graphics/TextureManager.h"

class Level {
private:
public:
	std::vector<Tile*> tiles;
	void load(const char* path, TextureManager* t) {
		std::ifstream file(path);
		std::string line;
		while (std::getline(file, line)) {
			std::stringstream stream(line);
			glm::vec2 pos, uv, size;
			std::string texture;
			stream >> pos.x >> pos.y >> uv.x >> uv.y >> size.x >> size.y >> texture;
			tiles.push_back(new Tile(pos, glm::vec2(32, 32), uv, size));
			tiles.back()->texture = t->load_texture(texture.c_str());
		}
		file.close();
	}
	void save(const char* path) {
		std::ofstream file(path);
		for (int i = 0; i < tiles.size(); i++) {
			file << tiles[i]->position.x << " " << tiles[i]->position.y << " " << tiles[i]->uv.x << " " << tiles[i]->uv.y << " " <<tiles[i]->uvSize.x << " "<< tiles[i]->uvSize.y << " " << tiles[i]->texturePath << std::endl;
		}
		file.close();
	}
};