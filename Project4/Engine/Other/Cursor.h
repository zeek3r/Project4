#pragma once
#include <iostream>
#include <SDL.h>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Cursor {
private:
	GLuint vao, vbo;
public:
	Cursor() {
		GLfloat verts[24] = {
			0, 0, 0, 0,
			0, 64, 0, 1,
			64, 64, 1, 1,
			64, 64, 1, 1,
			64, 0, 1, 0,
			0, 0, 0, 0
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
	GLuint texture;
	void draw() {
		glBindVertexArray(vao);
		glBindTexture(GL_TEXTURE_2D, texture);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
};