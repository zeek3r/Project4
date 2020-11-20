#pragma once
#include <iostream>
#include <glew.h>
#include "../Other/Error.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <map>


class TextureManager {
private:
	std::map<const char*, GLuint> textures;
public:
	std::vector<GLuint> textures_tilemap;
	GLuint load_texture(const char* path) {
		if (textures.find(path) == textures.end()) {
			GLuint tex;
			SDL_Surface* surface = IMG_Load(path);
			if (!surface) error("Failed to load texture " + std::string(path));
			glGenTextures(1, &tex);
			glBindTexture(GL_TEXTURE_2D, tex);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			textures[path] = tex;
		}
		return textures[path];
	}
	void generate_tile_map(const char* tilemap) {
		SDL_Surface* map = IMG_Load(tilemap);
		if (!map) error("Failed to load texture " + std::string(tilemap));
		for (int i = 0; i < map->w / 32; i++) {
			for (int j = 0; j < map->h / 32; j++) {
				SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, 32, 32, 32, SDL_PIXELFORMAT_RGBA32);
				SDL_Rect r{ i * 32,j * 32,32,32 };
				SDL_BlitSurface(map, &r, surface, nullptr);
				GLuint tex;
				glGenTextures(1, &tex);
				glBindTexture(GL_TEXTURE_2D, tex);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				textures_tilemap.push_back(tex);
			}
		}
	}
};