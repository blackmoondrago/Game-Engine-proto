#include "Window.h"
#include "Debug.h"

Window::Window() : window(nullptr), width(0), height(0)
{
	//Same as above
	window = nullptr;
}

Window::~Window()
{
	OnDestroy();
}

bool Window::OnCreate(std::string name_, int width_, int height_)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//std::cout << "Failed to initialize SDL" << std::endl;
		Debug::FatalError("Failed to initialize SDL", "Window.cpp", __LINE__);
		return false;
	}
	width = width_;
	height = height_;

	window = SDL_CreateWindow(name_.c_str(), 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL);

	if (!window)
	{
		//Checks if window ptr has nothing in it (OR == nullptr)
		//std::cout << "Failed to create window" << std::endl;
		Debug::FatalError("Failed to create window", "Window.cpp", __LINE__);
		return false;
	}

	context = SDL_GL_CreateContext(window);
	SetAttributes();
	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		//std::cout << "Failed to initialize GLEW" << std::endl;
		Debug::FatalError("Failed to initialize GLEW", "Window.cpp", __LINE__);
		return false;
	}

	glEnable(GL_DEPTH_TEST);

	return true;
}

void Window::OnDestroy()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}

int Window::GetWidth() const
{
	return width;
}

int Window::GetHeight() const
{
	return height;
}

SDL_Window* Window::GetWindow() const
{
	return window;
}

void Window::SetAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	SDL_GL_SetSwapInterval(1);

	glewExperimental = GL_TRUE;
}
