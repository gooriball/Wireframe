#include "App.h"

#include "Window.h"
#include "Shader.h"
#include "Map.h"
#include "Mesh.h"
#include "Camera.h"
#include "Projection.h"

App::App() :
running_{true}
{
	init();
}
App::~App() {}

void App::run()
{
	camera_->setMapInfo(map_->getWidth(), map_->getHeight(),
						map_->getMinValue(), map_->getMaxValue());
	camera_->setWindowSize(window_->getWidth(), window_->getHeight());
	camera_->update(Projection::Isometric);
	
	while (running_)
	{
		handleEvents();
		render();
	}
}

void App::init()
{
	window_ = std::make_unique<Window>();
	window_->setViewportToWindowSize();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	map_ = std::make_unique<Map>();
	std::string mapPath{"maps/test2.txt"};
	glm::vec3 colorLow{0.54f, 0.27f, 0.07f};
	glm::vec3 colorHigh{0.0f, 1.0f, 0.0f};
	map_->readMap(mapPath, colorLow, colorHigh);

	mesh_ = std::make_unique<Mesh>(map_->makeVertices(), map_->makeIndices());

	std::string vertexPath{"shaders/basic.vert"};
	std::string fragmentPath{"shaders/basic.frag"};
	shader_ = std::make_unique<Shader>(vertexPath, fragmentPath);
	shader_->use();

	camera_ = std::make_unique<Camera>();
}

void App::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				running_ = false;
				break;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					running_ = false;
				}
				break;
			
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
					event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					window_->setViewportToWindowSize();
				}
				break ;
		}
	}
}

void App::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	shader_->use();
	shader_->setMat4("model", camera_->getModel());
	shader_->setMat4("view", camera_->getView());
	shader_->setMat4("projection", camera_->getProjection());
	mesh_->draw();
	window_->swapWindow();
}