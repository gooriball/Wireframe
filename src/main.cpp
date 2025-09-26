#include <glad/glad.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "Vertex.h"
#include "Map.h"
#include "Mesh.h"
#include "Shader.h"

#include <iostream>
#include <string>

int main(int ac, char* av[])
{
	try
	{
		Window window;

		Map map;
		std::vector<std::string> maps{"42.txt", "france.txt", "japan.txt", "mars.txt", "plat.txt", "pyra.txt", "test.txt"};
		map.readMap("maps/" + maps[4]);

		Mesh mesh{map.makeVertices(), map.makeIndices()};

		int width;
		int height;
		window.getDrawableSize(width, height);
		glViewport(0, 0, width, height);
	
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		Shader shader{"shaders/basic.vert", "shaders/basic.frag"};
		shader.use();


		
		int mapWidth = map.getWidth();
		int mapHeight = map.getHeight();
		float mapMinValue = map.getMinValue();
		float mapMaxvalue = map.getMaxValue();
		float heightCenter = (mapMinValue + mapMaxvalue) / 2.0f;
		
		glm::mat4 model{glm::mat4(1.0f)};
		model = glm::translate(model, glm::vec3(-((mapWidth - 1) * 0.5f), -heightCenter, -((mapHeight - 1) * 0.5f)));
		model = glm::scale(model, glm::vec3(1.0f));
		
		float heightSpan = mapMaxvalue - mapMinValue;
		float diagonal = std::sqrt(mapWidth * mapWidth + mapHeight * mapHeight);
		float largestDim = std::max(diagonal, heightSpan);

		glm::vec3 center{glm::vec3(0.0f)};
		glm::vec3 dir{glm::normalize(glm::vec3(1.0f, -1.0f, -1.0f))};
		float dist = largestDim;
		glm::vec3 eye = center - dir * dist;
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 view = glm::lookAt(eye, center, up);
		
		float viewSize = largestDim / 2.0f;
		int windowWidth;
		int windowHeight;
		window.getDrawableSize(windowWidth, windowHeight);
		float aspectRatio = (windowHeight != 0) ? static_cast<float>(windowWidth) / windowHeight : 1.0f;

		glm::mat4 projection = glm::ortho(-viewSize * aspectRatio, viewSize * aspectRatio,
											-viewSize, viewSize, dist * 0.5f, dist * 2.0f);


		SDL_Event event;	
		bool running = true;
		while (running)
		{
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
					case SDL_QUIT:
						running = false;
						break;

					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_ESCAPE)
						{
							running = false;
						}
						break;
					
					case SDL_WINDOWEVENT:
						if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
							event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
						{
							int width;
							int height;
							window.getDrawableSize(width, height);
							glViewport(0, 0, width, height);
						}
						break ;
				}
			}
	
			glClear(GL_COLOR_BUFFER_BIT);

			shader.use();
			shader.setMat4("model", model);
			shader.setMat4("view", view);
			shader.setMat4("projection", projection);
	
			mesh.draw();
	
			window.swapWindow();
		}
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';

		return (1);
	}

	return (0);
}