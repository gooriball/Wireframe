#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <string>

#include "Projection.h"

class Camera
{
	public:
		Camera();
		~Camera();

		void update(const std::string& projection);
		void setMapInfo(unsigned int width, unsigned int height, float minValue, float maxValue);
		void setWindowSize(int width, int height);

		glm::mat4 getModel() const;
		glm::mat4 getView() const;
		glm::mat4 getProjection() const;

	private:
		void updateModel();
		void updateView();
		void updateProjection(const std::string& projection);
		
		unsigned int mapWidth_;
		unsigned int mapHeight_;
		float mapMinValue_;
		float mapMaxValue_;
		float heightCenter_;
		float heightSpan_;
		float diagonal_;
		float largestDim_;
		float dist_;
		float viewSize_;
		float fovy_;

		int windowWidth_;
		int windowHeight_;
		float aspectRatio_;

		glm::mat4 model_;
		glm::mat4 view_;
		glm::mat4 projection_;
};