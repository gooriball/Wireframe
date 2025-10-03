#pragma once

#include <memory>
#include <vector>
#include <string>

#include <glm/vec3.hpp>
#include <SDL.h>

class Window;
class Shader;
class Map;
class Mesh;
class Camera;

class App
{
	public:
		App();
		~App();

		void run();

	private:	
		void init();
		void handleEvents();
		void processInput();
		void update();
		void render();
		void readMapList();
		void setProjectionList();

		bool running_;

		std::unique_ptr<Window> window_;
		std::unique_ptr<Shader> shader_;
		std::unique_ptr<Map> map_;
		std::unique_ptr<Mesh> mesh_;
		std::unique_ptr<Camera> camera_;

		std::vector<std::string> mapList_;
		std::vector<const char*> mapListImgui_;
		int currentMapIndex_;
		glm::vec3 backgroundColor_;
		glm::vec3 lowColor_;
		glm::vec3 highColor_;

		std::vector<std::string> projectionList_;
		std::vector<const char*> projectionListImgui_;
		int currentProjectionIndex_;

		float cameraSpeed_;
		glm::vec3 movement_;
		bool hasMoved_;
		int mouseWheelSteps_;

		Uint64 lastCounter_;
		Uint64 countsPerSecond_;
};