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
		if (file.fail()) return;
		tiles.clear();
		std::string line;
		while (std::getline(file, line)) {
			std::stringstream stream(line);
			glm::vec2 pos;
			GLuint texture;
			stream >> pos.x >> pos.y >> texture;
			tiles.push_back(new Tile(pos, glm::vec2(32, 32)));
			tiles.back()->texture = texture;
		}
		file.close();
		std::cout << "Level " << path << " loaded. Tile count: " << tiles.size() << std::endl;
	}
	void save(const char* path) {
		std::ofstream file(path);
		for (int i = 0; i < tiles.size(); i++) {
			file << tiles[i]->position.x << " " << tiles[i]->position.y << " " << tiles[i]->texture << std::endl;
		}
		file.close();
		std::cout << "Level " << path << " saved.\n";
	}
};