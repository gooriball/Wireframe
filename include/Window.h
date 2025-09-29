#pragma once

#include <glad/glad.h>
#include <SDL.h>

#include <string>

class Window
{
	public:
		Window();
		~Window();

		void swapWindow();
		void getDrawableSize(int& width, int& height);
		void setViewportToWindowSize();

		unsigned int getWidth() const;
		unsigned int getHeight() const;

		SDL_Window* getSDLWindow() const;
		SDL_GLContext getGLContext() const;
		
	private:
		void init();
		void initSDL();
		void createWindow();
		void createGLContext();
		void initGLAD();

		unsigned int width_;
		unsigned int height_;

		SDL_Window* window_;
		SDL_GLContext glContext_;
};