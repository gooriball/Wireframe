#pragma once

#include <memory>

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
		void render();

		bool running_;

		std::unique_ptr<Window> window_;
		std::unique_ptr<Shader> shader_;
		std::unique_ptr<Map> map_;
		std::unique_ptr<Mesh> mesh_;
		std::unique_ptr<Camera> camera_;
};