#pragma once

#include <string>
#include <vector>

#include <glm/vec3.hpp>

#include "Vertex.h"

class Map
{
	public:
		Map();
		~Map();

		void readMap(const std::string& filePath);

		std::vector<Vertex> makeVertices();
		std::vector<unsigned int> makeIndices();

		unsigned int getWidth() const;
		unsigned int getHeight() const;

		float getMinValue() const;
		float getMaxValue() const;

	private:
		void checkLineIsNumeric(const std::string& line, int lineNumber);
		
		unsigned int width_;
		unsigned int height_;

		float minValue_;
		float maxValue_;

		std::vector<float> mapData_;
};