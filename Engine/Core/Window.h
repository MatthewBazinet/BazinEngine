#ifndef WINDOW_H
#define WINDOW_H

#include<SDL.h>
#include<glew.h>
#include<SDL_opengl.h>
#include<string>
#include<iostream>
#include "Log.h"
#include "Renderer.h"

class Window : public Renderer
{
public:
	Window();
	~Window();

	virtual SDL_Window* CreatesWindow(std::string name_, int width_, int height_);
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Render() {};
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