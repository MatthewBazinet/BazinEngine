#ifndef WINDOW_H
#define WINDOW_H

#include<SDL.h>
#include<glew.h>
#include<SDL_opengl.h>
#include<string>
#include<iostream>

class Window
{
public:
	Window();
	~Window();

	bool OnCreate(std::string name_, int width_, int height_);
	void OnDestroy();
	int GetWidth() const;
	int GetHeight() const;
	SDL_Window* GetWindow() const;

private:
	//Sets OpenGL Attributes for before the context is created
	void SetPreAttributes();
	//Sets OpenGL Attributes for after the context is created
	void SetPostAttributes();

	int width;
	int height;

	SDL_Window* window;
	SDL_GLContext context;
};

#endif