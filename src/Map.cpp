#include "Map.h"

Map::Map() :
width_{0},
height_{0}
{}

void Map::readMap(const std::string& filePath)
{
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
	float data;
	std::istringstream ss{line};
	while (ss >> data)
	{
		++firstLineCount;
		mapData_.emplace_back(data);
	}
	width_ = firstLineCount;
	++height_;

	while (std::getline(file, line))
	{
		checkLineIsNumeric(line, lineNumber++);

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
			throw std::runtime_error("The file has to be a rectangle matrix! (line " + std::to_string(lineNumber - 1) + ")");
		}
		++height_;
	}
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

	for (unsigned int y = 0; y < height_; ++y)
	{
		for (unsigned int x = 0; x < width_; ++x)
		{
			vertices.emplace_back(x, y, mapData_[y * width_ + x]);
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