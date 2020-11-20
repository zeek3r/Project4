#pragma once
#include <iostream>
#include <SDL.h>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Tile {
private:
	GLuint vao, vbo;
public:
	Tile(glm::vec2 position, glm::vec2 size, glm::vec2 uv, glm::vec2 uvSize) {
		this->position = position;
		this->uv = uv;
		this->uvSize = uvSize;
		this->size = size;
		GLfloat verts[24] = {
			position.x, position.y, uv.x, uv.y,
			position.x, position.y + size.y, uv.x, uv.y + uvSize.y,
			position.x + size.x, position.y + size.y, uv.x + uvSize.x, uv.y + uvSize.y,
			position.x + size.x, position.y + size.y, uv.x + uvSize.x, uv.y + uvSize.y,
			position.x + size.x, position.y, uv.x + uvSize.x, uv.y,
			position.x, position.y, uv.x, uv.y
		};
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 24, verts, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void*)8);
		glEnableVertexAttribArray(1);
	}
	glm::vec2 uv, uvSize;
	glm::vec2 position;
	glm::vec2 size;
	std::string texturePath;
	GLuint texture;
	void draw() {
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	void update_position() {
		GLfloat verts[24] = {
			position.x, position.y, uv.x, uv.y,
			position.x, position.y + size.y, uv.x, uv.y + uvSize.y,
			position.x + size.x, position.y + size.y, uv.x + uvSize.x, uv.y + uvSize.y,
			position.x + size.x, position.y + size.y, uv.x + uvSize.x, uv.y + uvSize.y,
			position.x + size.x, position.y, uv.x + uvSize.x, uv.y,
			position.x, position.y, uv.x, uv.y
		};
		glBindVertexArray(vao);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 24, verts);
	}
};