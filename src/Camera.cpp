#include "Camera.h"


Camera::Camera() :
model_{1.0f},
view_{1.0f},
projection_{1.0f}
{}

Camera::~Camera() {}

void Camera::update(const std::string& projection)
{
	updateModel();
	updateView();
	updateProjection(projection);
}

void Camera::setMapInfo(unsigned int width, unsigned int height, float minValue, float maxValue)
{
	mapWidth_ = width;
	mapHeight_ = height;
	mapMinValue_ = minValue;
	mapMaxValue_ = maxValue;
	heightCenter_ = (mapMinValue_ + mapMaxValue_) * 0.5f;
	heightSpan_ = mapMaxValue_ - mapMinValue_;
	diagonal_ = std::sqrt(mapWidth_ * mapWidth_ + mapHeight_ * mapHeight_);
	largestDim_ = std::max(diagonal_, heightSpan_);
}

void Camera::setWindowSize(int width, int height)
{
	windowWidth_ = width;
	windowHeight_ = height;
	aspectRatio_ = (windowHeight_ != 0) ? static_cast<float>(windowWidth_) / windowHeight_ : 1.0f;
}

glm::mat4 Camera::getModel() const { return (model_); }

glm::mat4 Camera::getView() const { return (view_); }

glm::mat4 Camera::getProjection() const { return (projection_); }

void Camera::updateModel()
{
	model_ = glm::mat4(1.0f);
	model_ = glm::translate(model_, glm::vec3(-((mapWidth_ - 1) * 0.5f),
							-heightCenter_, -((mapHeight_ - 1) * 0.5f)));
	model_ = glm::rotate(model_, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model_ = glm::scale(model_, glm::vec3(1.0f));
}

void Camera::updateView()
{
	glm::vec3 center{glm::vec3(0.0f)};
	glm::vec3 dir{glm::normalize(glm::vec3{1.0f, -1.0f, -1.0f})};
	dist_ = largestDim_;
	glm::vec3 eye{center - dir * dist_};
	glm::vec3 up{glm::vec3{0.0f, 1.0f, 0.0f}};
	view_ = glm::lookAt(eye, center, up);
}

void Camera::updateProjection(const std::string& projection)
{
	if (projection == "Isometric")
	{
		viewSize_ = largestDim_ * 0.5f;
		projection_ = glm::ortho(-viewSize_ * aspectRatio_, viewSize_ * aspectRatio_,
							-viewSize_, viewSize_, dist_ * 0.5f, dist_ * 2.0f);
	}
	else if (projection == "Perspective")
	{
		fovy_ = glm::radians(45.0f);
		projection_ = glm::perspective(fovy_, aspectRatio_, dist_ * 0.5f, dist_ * 2.0f);
	}
}