#pragma once
#include <iostream>
#include <glm/glm.hpp>

class CollisionTile {
private:

public:
	glm::vec2 position = glm::vec2(0, 0);
	glm::vec2 size = glm::vec2(32, 32);
};