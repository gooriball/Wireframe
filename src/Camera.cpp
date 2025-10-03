#include "Camera.h"

Camera::Camera() :
model_{1.0f},
view_{1.0f},
projection_{1.0f},
viewCenter_{glm::vec3{0.0f}},
projectionType_{"Isometric"},
scale_{1.0f},
base_{1.1f},
zoomInOut_{0},
fovDegree_{45.0f},
baseFovDegree_{45.0f}
{}

Camera::~Camera() {}

void Camera::update()
{
	updateZoom();
	updateModel();
	updateView();
	updateProjection();
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

void Camera::updateZoom()
{
	if (projectionType_ == "Isometric")
	{
		if (zoomInOut_ > 0) { scale_ = glm::min(scale_ * base_, 100.0f); }
		else if (zoomInOut_ < 0) { scale_ = glm::max(scale_ / base_, 0.01f); }
	}
	else if (projectionType_ == "Perspective")
	{
		if (zoomInOut_ > 0) { fovDegree_ = glm::max(fovDegree_ / base_, 1.0f); }
		else if (zoomInOut_ < 0) { fovDegree_ = glm::min(fovDegree_ * base_, 179.0f); }
	}
}

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
	glm::vec3 dir{glm::normalize(glm::vec3{1.0f, -1.0f, -1.0f})};
	dist_ = largestDim_;
	glm::vec3 eye{viewCenter_ - dir * dist_};
	glm::vec3 up{glm::vec3{0.0f, 1.0f, 0.0f}};
	view_ = glm::lookAt(eye, viewCenter_, up);
}

void Camera::updateProjection()
{
	if (projectionType_ == "Isometric")
	{
		viewSize_ = largestDim_ / scale_;
		projection_ = glm::ortho(-viewSize_ * aspectRatio_, viewSize_ * aspectRatio_,
			-viewSize_, viewSize_, dist_ * 0.5f, dist_ * 2.0f);
	}
	else if (projectionType_ == "Perspective")
	{
		fovy_ = glm::radians(fovDegree_);
		projection_ = glm::perspective(fovy_, aspectRatio_, dist_ * 0.5f, dist_ * 2.0f);
	}
}

void Camera::setViewCenter(const glm::vec3& viewCenter) { viewCenter_ = viewCenter; }
void Camera::setProjectionType(const std::string& projectionType) { projectionType_ = projectionType; }
void Camera::setZoomInOut(int zoomInOut) { zoomInOut_ = zoomInOut; }

float Camera::getScale() const
{
	if (projectionType_ == "Isometric") { return (scale_); }
	else if (projectionType_ == "Perspective")
	{
		float base = glm::tan(glm::radians(baseFovDegree_) / 2.0f);
		float now = glm::tan(glm::radians(fovDegree_) / 2.0f);
		return (base / now);
	}
	else { return (1.0f); }
}

glm::vec3 Camera::getViewCenter() const { return (viewCenter_); }
float Camera::getfovDegree() const { return (fovDegree_); }

glm::mat4 Camera::getModel() const { return (model_); }
glm::mat4 Camera::getView() const { return (view_); }
glm::mat4 Camera::getProjection() const { return (projection_); }