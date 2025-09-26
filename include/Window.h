#pragma once

#include <glad/glad.h>
#include <SDL.h>

#include <iostream>
#include <string>

class Window
{
	public:
		Window();
		~Window();

		void swapWindow();
		void getDrawableSize(int& width, int& height);

		SDL_Window* getSDLWindow() const;
		SDL_GLContext getGLContext() const;
		
	private:
		void init();
		void initSDL();
		void createWindow();
		void createGLContext();
		void initGLAD();

		SDL_Window* window_;
		SDL_GLContext glContext_;
};