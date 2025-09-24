#include <glad/glad.h>
#include <SDL.h>
#include <iostream>
#include <string>

#include <vector>
#include <fstream>
#include <sstream>

#include "Shader.h"
#include "Vertex.h"
#include "Map.h"
#include "Mesh.h"

std::vector<Vertex> readMap(const std::string& filePath);

int main(int ac, char* av[])
{
	SDL_Window* window = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize!\n";
		std::cout << "SDL_Error:" << SDL_GetError() << "\n";

		return (1);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								WINDOW_WIDTH, WINDOW_HEIGHT,
								SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	if (window == nullptr)
	{
		std::cout << "Window could not be created!\n";
		std::cout << "SDL_Error: " << SDL_GetError() << "\n";

		SDL_Quit();

		return (1);
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr)
	{
		std::cout << "Failed to create OpenGL context!\n";
		std::cout << "SDL_Error: " << SDL_GetError() << "\n";

		SDL_DestroyWindow(window);
		SDL_Quit();

		return (1);
	}

	SDL_GL_SetSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cout << "Failed to initialize GLAD!\n";

		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(window);
		SDL_Quit();

		return (1);
	}

	Map map;
	try
	{
		map.readMap("maps/plat");
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';

		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(window);
		SDL_Quit();

		return (1);
	}
	
	Mesh mesh{map.makeVertices(), map.makeIndices()};

	int width;
	int height;
	SDL_GL_GetDrawableSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//glPointSize(1.0f);

	try
	{
		Shader shader{"shaders/basic.vert", "shaders/basic.frag"};
		shader.use();
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(window);
		SDL_Quit();

		return (1);
	}

	SDL_Event event;
	bool running = true;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}

			if (event.type == SDL_WINDOWEVENT &&
				(event.window.event == SDL_WINDOWEVENT_RESIZED ||
				event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED))
			{
				int newWidth;
				int newHeight;
				SDL_GL_GetDrawableSize(window, &newWidth, &newHeight);
				glViewport(0, 0, newWidth, newHeight);
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);

		mesh.draw();

		SDL_GL_SwapWindow(window);
	}
	
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return (0);
}

void checkLineIsNumeric(const std::string& line, int lineNumber)
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

std::vector<Vertex> readMap(const std::string& filePath)
{
	std::ifstream file{filePath};
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file: " + filePath);
	}
	
	std::vector<Vertex> vertices;
	std::string line;
	int lineNumber = 1;

	if (!std::getline(file, line))
	{
		throw std::runtime_error("The file is empty!");
	}
	checkLineIsNumeric(line, lineNumber++);
	
	int x = 0;
	int y = 0;
	int firstLineCount = 0;
	float data;
	std::istringstream ss{line};
	while (ss >> data)
	{
		++firstLineCount;
		vertices.emplace_back(static_cast<float>(x++),
								static_cast<float>(y),
								data);
	}
	++y;

	while (std::getline(file, line))
	{
		checkLineIsNumeric(line, lineNumber++);

		x = 0;
		int count = 0;
		float data;
		std::istringstream ss{line};
		while (ss >> data)
		{
			++count;
			vertices.emplace_back(static_cast<float>(x++),
									static_cast<float>(y),
									data);
		}
		if (firstLineCount != count)
		{
			throw std::runtime_error("The file has to be a rectangle matrix! (line " + std::to_string(lineNumber - 1) + ")");
		}
		++y;
	}

	return (vertices);
}