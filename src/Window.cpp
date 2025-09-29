#include "Window.h"

#include <iostream>

Window::Window() :
window_{nullptr},
glContext_{nullptr}
{
	init();
}

Window::~Window()
{
	if (glContext_)
	{
		SDL_GL_DeleteContext(glContext_);
	}
	if (window_)
	{
		SDL_DestroyWindow(window_);
	}
	SDL_Quit();
}

void Window::init()
{
	initSDL();
	createWindow();
	createGLContext();
	initGLAD();
}

void Window::swapWindow()
{
	SDL_GL_SwapWindow(window_);
}

void Window::getDrawableSize(int& width, int& height)
{
	SDL_GL_GetDrawableSize(window_, &width, &height);
}

void Window::setViewportToWindowSize()
{
	int width;
	int height;
	SDL_GL_GetDrawableSize(window_, &width, &height);
	glViewport(0, 0, width, height);
	width_ = width;
	height_ = height;
}

void Window::initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::runtime_error(std::string("SDL could not initialize!\nSDL_Error: ") +
								SDL_GetError() + "\n");
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void Window::createWindow()
{
	window_ = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								WINDOW_WIDTH, WINDOW_HEIGHT,
								SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	if (window_ == nullptr)
	{
		SDL_Quit();

		throw std::runtime_error(std::string("Window could not be created!\nSDL_Error: ") +
								SDL_GetError() + "\n");
	}
}

void Window::createGLContext()
{
	glContext_ = SDL_GL_CreateContext(window_);
	if (glContext_ == nullptr)
	{
		SDL_DestroyWindow(window_);
		SDL_Quit();

		throw std::runtime_error(std::string("Failed to create OpenGL context!\nSDL_Error: ") +
								SDL_GetError() + "\n");
	}

	SDL_GL_SetSwapInterval(1);
}

void Window::initGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		SDL_GL_DeleteContext(glContext_);
		SDL_DestroyWindow(window_);
		SDL_Quit();

		throw std::runtime_error("Failed to initialize GLAD!");
	}
}

unsigned int Window::getWidth() const { return (width_); }
unsigned int Window::getHeight() const { return (height_); }

SDL_Window* Window::getSDLWindow() const { return (window_); }
SDL_GLContext Window::getGLContext() const { return (glContext_); }