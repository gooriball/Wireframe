#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <string>

class Camera
{
	public:
		Camera();
		~Camera();

		void update();
		void setMapInfo(unsigned int width, unsigned int height, float minValue, float maxValue);
		void setWindowSize(int width, int height);

		void setViewCenter(const glm::vec3& viewCenter);
		void setProjectionType(const std::string& projectionType);
		void setZoomInOut(int zoomInOut);

		float getScale() const;
		float getfovDegree() const;
		glm::vec3 getViewCenter() const;

		glm::mat4 getModel() const;
		glm::mat4 getView() const;
		glm::mat4 getProjection() const;

	private:
		void updateZoom();
		void updateModel();
		void updateView();
		void updateProjection();
		
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
		float scale_;
		float base_;
		int zoomInOut_;
		float fovy_;
		float fovDegree_;
		float baseFovDegree_;

		int windowWidth_;
		int windowHeight_;
		float aspectRatio_;

		glm::mat4 model_;
		glm::mat4 view_;
		glm::mat4 projection_;

		glm::vec3 viewCenter_;
		std::string projectionType_;
};