#include "Window.h"

Window::Window() : window(nullptr), context(nullptr)
{
	height = 0.0f;
	width = 0.0f;
	setRendererType(RendererType::OPENGL);
}

Window::~Window()
{
	OnDestroy();
}

SDL_Window* Window::CreatesWindow(std::string name_, int width_, int height_)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		Log::FatalError("Failed to initilize SDL", "Window.cpp", __LINE__);
		return nullptr;
	}
	this->width = width_;
	this->height = height_;

	window = SDL_CreateWindow(name_.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL);

	if (!window) {
		Log::FatalError("Failed to create window", "Window.cpp", __LINE__);
		return nullptr;
	}

	OnCreate();

	Log::Info("OpenGL Version: " + std::string((char*)glGetString(GL_VERSION)), "Window.cpp", __LINE__);
	Log::Info("Graphics Card Vendor: " + std::string((char*)glGetString(GL_VENDOR)), "Window.cpp", __LINE__);
	std::cout << "Graphics Card Vendor: " << std::string((char*)glGetString(GL_VENDOR)) << std::endl;
	return window;
}

bool Window::OnCreate()
{
	context = SDL_GL_CreateContext(window);
	SetPreAttributes();
	SetPostAttributes();

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		Log::FatalError("Failed to initialize GLEW", "Window.cpp", __LINE__);

	}	
	glViewport(0, 0, width, height);
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

void Window::SetPreAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	glewExperimental = GL_TRUE;
}

void Window::SetPostAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
}
