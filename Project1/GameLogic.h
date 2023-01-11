#pragma once
#include "include/SDL.h"
#include "include/SDL_image.h"
#include "pch.h"
#include "Entity.h"
#include <vector>

class Game
{
public:
	Game(int width, int height);
	void Run();
	void Init();
	void DrawRect(int r, int g, int b, int a, SDL_Rect* rect);
	void DrawEntity(Entity& entity, SDL_Rect& rect);
	void Clear();
private:
	void Exit();
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Surface* _windowSurface;
	int _width, _height;
};


