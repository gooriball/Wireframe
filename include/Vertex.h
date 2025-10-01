#pragma once

#include <glm/vec3.hpp>

struct Vertex
{
	glm::vec3 position_;
	float heightNormalized_;

	Vertex(const glm::vec3& position, float heightNormalized) :
	position_{position},
	heightNormalized_{heightNormalized}
	{}
};