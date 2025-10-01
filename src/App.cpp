#include "App.h"

#include "Window.h"
#include "Shader.h"
#include "Map.h"
#include "Mesh.h"
#include "Camera.h"
#include "Projection.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include <filesystem>

App::App() :
running_{true},
currentMapIndex_(7),
highColor_{0.0f, 1.0f, 0.0f},
lowColor_{0.54f, 0.27f, 0.07f},
currentProjectionIndex_{0}
{
	init();
}
App::~App()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void App::run()
{
	while (running_)
	{
		handleEvents();
		processInput();
		render();
	}
}

void App::init()
{
	window_ = std::make_unique<Window>();
	window_->setViewportToWindowSize();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window_->getSDLWindow(), window_->getGLContext());
	ImGui_ImplOpenGL3_Init("#version 330 core");
	ImGuiIO& io = ImGui::GetIO();
	io.FontGlobalScale = 1.2f;
	ImGui::GetStyle().ScaleAllSizes(1.2f);
	
	readMapList();
	setProjectionList();

	map_ = std::make_unique<Map>();
	std::string mapPath{"maps/" + mapList_[currentMapIndex_]};
	map_->readMap(mapPath);

	mesh_ = std::make_unique<Mesh>(map_->makeVertices(), map_->makeIndices());

	std::string vertexPath{"shaders/basic.vert"};
	std::string fragmentPath{"shaders/basic.frag"};
	shader_ = std::make_unique<Shader>(vertexPath, fragmentPath);
	shader_->use();

	camera_ = std::make_unique<Camera>();
	camera_->setMapInfo(map_->getWidth(), map_->getHeight(),
						map_->getMinValue(), map_->getMaxValue());
	camera_->setWindowSize(window_->getWidth(), window_->getHeight());
}

void App::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
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
					camera_->setWindowSize(window_->getWidth(), window_->getHeight());
				}
				break ;
		}
	}
}

void App::processInput()
{

}

void App::render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	camera_->update(projectionList_[currentProjectionIndex_]);

	shader_->use();
	shader_->setMat4("model", camera_->getModel());
	shader_->setMat4("view", camera_->getView());
	shader_->setMat4("projection", camera_->getProjection());
	shader_->setVec3("highColor", highColor_);
	shader_->setVec3("lowColor", lowColor_);
	mesh_->draw();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Settings");

	ImGui::Text("Map List");
	ImGui::SameLine();
	if (ImGui::Combo("##Map List", &currentMapIndex_, mapListImgui_.data(), mapListImgui_.size()))
	{
		map_->readMap("maps/" + mapList_[currentMapIndex_]);
		mesh_ = std::make_unique<Mesh>(map_->makeVertices(), map_->makeIndices());
		camera_->setMapInfo(map_->getWidth(), map_->getHeight(),
							map_->getMinValue(), map_->getMaxValue());
	}
	ImGui::Dummy(ImVec2(0, 10));
	
	ImGui::Text("High Color");
	ImGui::SameLine();
	if (ImGui::ColorEdit3("##High Color", (float*)&highColor_))
	{
		shader_->setVec3("highColor", highColor_);
	}
	ImGui::Dummy(ImVec2(0, 10));
	
	ImGui::Text("Low Color");
	ImGui::SameLine();
	if (ImGui::ColorEdit3("##Low Color", (float*)&lowColor_))
	{
		shader_->setVec3("lowColor", lowColor_);
	}
	ImGui::Dummy(ImVec2(0, 10));

	ImGui::Text("Projection");
	ImGui::SameLine();
	ImGui::Combo("##Projection", &currentProjectionIndex_, projectionListImgui_.data(), projectionListImgui_.size());

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	window_->swapWindow();
}

void App::readMapList()
{
	std::string mapDirectory{"maps"};
	for (const auto& map : std::filesystem::directory_iterator(mapDirectory))
	{
		if (map.is_regular_file())
		{
			std::string filename{map.path().filename().string()};
			mapList_.push_back(filename);
		}
	}

	for (const auto& map : mapList_)
	{
		mapListImgui_.push_back(map.c_str());
	}
}

void App::setProjectionList()
{
	std::vector<std::string> projectionList{"Isometric", "Perspective"};

	for (const auto& projection : projectionList)
	{
		projectionList_.push_back(projection);
	}

	for (const auto& projection : projectionList_)
	{
		projectionListImgui_.push_back(projection.c_str());
	}
}