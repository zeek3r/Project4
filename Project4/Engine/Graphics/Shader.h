#pragma once
#include <glew.h>
#include <iostream>
#include <string>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader {
private:
	std::string get_shader_source(std::string path) {
		std::ifstream file(path);
		if (file.fail()) {
			std::cout << "Could not open file " << path << std::endl;
			return " ";
		}
		std::string temp;
		std::string source;
		while (std::getline(file, temp)) {
			source += temp + "\n";
		}
		return source;
	}
	GLuint vertex, fragment, program;
public:
	void load_shader(std::string path) {
		program = glCreateProgram();
		vertex = glCreateShader(GL_VERTEX_SHADER);
		fragment = glCreateShader(GL_FRAGMENT_SHADER);

		std::string s = get_shader_source(path + ".vert");
		const GLchar* c = s.c_str();
		glShaderSource(vertex, 1, &c, 0);
		s = get_shader_source(path + ".frag");
		c = s.c_str();
		glShaderSource(fragment, 1, &c, 0);
		glCompileShader(vertex);
		GLint success = 0;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			char msg[512];
			glGetShaderInfoLog(vertex, 512, 0, msg);
			std::cout << "Failed to compile vertex shader: " << msg << std::endl;
		}
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			char msg[512];
			glGetShaderInfoLog(fragment, 512, 0, msg);
			std::cout << "Failed to compile fragment shader: " << msg << std::endl;
		}
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);
		glLinkProgram(program);
	}
	void use_shader() {
		glUseProgram(program);
	}
	void set_uniform_mat4(glm::mat4 mat, const char* name) {
		GLuint loc = glGetUniformLocation(program, name);
		glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
	}
	void set_uniform_vec3(glm::vec3 vec, const char* name) {
		GLuint loc = glGetUniformLocation(program, name);
		glUniform3f(loc, vec.x, vec.y, vec.z);
	}
	void set_uniform_vec2(glm::vec2 vec, const char* name) {
		GLuint loc = glGetUniformLocation(program, name);
		glUniform2f(loc, vec.x, vec.y);
	}
	void set_uniform_float(float f, const char* name) {
		GLuint loc = glGetUniformLocation(program, name);
		glUniform1f(loc, f);
	}
};