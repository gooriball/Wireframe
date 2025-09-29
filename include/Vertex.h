#pragma once

#include <glm/vec3.hpp>

struct Vertex
{
	glm::vec3 position_;
	glm::vec3 color_;

	Vertex(const glm::vec3& position, const glm::vec3& color) :
	position_{position},
	color_{color}
	{}
};