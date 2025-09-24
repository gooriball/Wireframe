#pragma once

#include <glad/glad.h>
#include <vector>

#include "Vertex.h"

class Mesh
{
	public:
		Mesh(const std::vector<Vertex>&& vertices, const std::vector<unsigned int>&& indices);
		~Mesh();

		void bind();
		void unbind();

		void draw();
		
	private:
		unsigned int vao_;
		unsigned int vbo_;
		unsigned int ebo_;

		std::vector<Vertex> vertices_;
		std::vector<unsigned int> indices_;
};