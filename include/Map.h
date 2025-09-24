#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "Vertex.h"

class Map
{
	public:
		Map();

		void readMap(const std::string& filePath);

		std::vector<Vertex> makeVertices();
		std::vector<unsigned int> makeIndices();

	private:
		void checkLineIsNumeric(const std::string& line, int lineNumber);
		
		unsigned int width_;
		unsigned int height_;

		std::vector<float> mapData_;
};