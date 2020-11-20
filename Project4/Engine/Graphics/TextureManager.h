#pragma once
#include <iostream>
#include <glew.h>
#include "../Other/Error.h"
#include <SDL.h>
#include <SDL_image.h>
#include <map>


class TextureManager {
private:
	std::map<const char*, GLuint> textures;
public:
	GLuint load_texture(const char* path) {
		if (textures.find(path) == textures.end()) {
			GLuint tex;
			SDL_Surface* surface = IMG_Load(path);
			if (!surface) error("Failed to load texture " + std::string(path));
			glGenTextures(1, &tex);
			glBindTexture(GL_TEXTURE_2D, tex);
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			textures[path] = tex;
		}
		return textures[path];
	}
};