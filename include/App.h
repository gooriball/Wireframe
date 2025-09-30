#pragma once

#include <memory>
#include <vector>
#include <string>

#include <glm/vec3.hpp>

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
		void render();
		void readMapList();

		bool running_;

		std::unique_ptr<Window> window_;
		std::unique_ptr<Shader> shader_;
		std::unique_ptr<Map> map_;
		std::unique_ptr<Mesh> mesh_;
		std::unique_ptr<Camera> camera_;

		std::vector<std::string> mapList_;
		std::vector<const char*> mapListImgui_;
		int currentMapIndex_;
		glm::vec3 lowColor_;
		glm::vec3 highColor_;
};