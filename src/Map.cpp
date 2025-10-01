#include "Map.h"

#include <fstream>
#include <sstream>
#include <algorithm>

Map::Map() :
width_{0},
height_{0}
{}

Map::~Map() {}

void Map::readMap(const std::string& filePath)
{
	mapData_.clear();
	
	std::ifstream file{filePath};
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file: " + filePath);
	}
	
	std::string line;
	int lineNumber = 1;

	if (!std::getline(file, line))
	{
		throw std::runtime_error("The file is empty!");
	}
	checkLineIsNumeric(line, lineNumber++);

	int firstLineCount = 0;
	int height = 0;
	float data;
	std::istringstream ss{line};
	while (ss >> data)
	{
		++firstLineCount;
		mapData_.emplace_back(data);
	}
	width_ = firstLineCount;
	++height;

	while (std::getline(file, line))
	{
		checkLineIsNumeric(line, lineNumber);

		int count = 0;
		float data;
		std::istringstream ss{line};
		while (ss >> data)
		{
			++count;
			mapData_.emplace_back(data);
		}
		if (firstLineCount != count)
		{
			throw std::runtime_error("The file has to be a rectangle matrix! (line " + std::to_string(lineNumber) + ")");
		}
		++height;
		++lineNumber;
	}
	height_ = height;

	auto[min, max] = std::minmax_element(mapData_.begin(), mapData_.end());
	minValue_ = *min;
	maxValue_ = *max;
}

void Map::checkLineIsNumeric(const std::string& line, int lineNumber)
{
	if (line.find_first_not_of(" \t\r") == std::string::npos)
	{
		throw std::runtime_error("Empty/blank line at line " + std::to_string(lineNumber));
	}

	std::istringstream iss{line};
	float data;
	while (iss >> data) {}

	if (iss.fail() && !iss.eof())
	{
		throw std::runtime_error("Non-numeric token at line " + std::to_string(lineNumber));
	}
}

std::vector<Vertex> Map::makeVertices()
{
	std::vector<Vertex> vertices;
	vertices.reserve(width_ * height_);

	for (unsigned int y = 0; y < height_; ++y)
	{
		for (unsigned int x = 0; x < width_; ++x)
		{
			float height{mapData_[y * width_ + x]};
			float heightNormalized{(height - minValue_) / (maxValue_ - minValue_)}; 
			vertices.emplace_back(glm::vec3{x, height, y}, heightNormalized);
		}
	}

	return (vertices);
}

std::vector<unsigned int> Map::makeIndices()
{
	std::vector<unsigned int> indices;

	for (unsigned int y = 0; y < height_; ++y)
	{
		for (unsigned int x = 0; x < width_; ++x)
		{
			unsigned int center = y * width_ + x;
			
			if (x < width_ - 1)
			{
				unsigned int right = center + 1;
				indices.push_back(center);
				indices.push_back(right);
			}

			if (y < height_ - 1)
			{
				unsigned int bottom = (y + 1) * width_ + x;
				indices.push_back(center);
				indices.push_back(bottom);
			}
		}
	}

	return (indices);
}

unsigned int Map::getWidth() const { return (width_); }
unsigned int Map::getHeight() const { return (height_); }

float Map::getMinValue() const { return (minValue_);}
float Map::getMaxValue() const { return (maxValue_);}