#include "Mesh.h"
#include <cstddef>

Mesh::Mesh(std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices) :
vertices_{std::move(vertices)},
indices_{std::move(indices)}
{
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &ebo_);

	glBindVertexArray(vao_);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices_.size(), vertices_.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices_.size(), indices_.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, heightNormalized_));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &vbo_);
	glDeleteBuffers(1, &ebo_);
}

void Mesh::bind()
{
	glBindVertexArray(vao_);
}

void Mesh::unbind()
{
	glBindVertexArray(0);
}

void Mesh::draw()
{
	bind();
	glDrawElements(GL_LINES, indices_.size(), GL_UNSIGNED_INT, 0);
	unbind();
}