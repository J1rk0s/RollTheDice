#pragma once
#include "include/SDL.h"
#include "include/SDL_image.h"

class Entity
{
public:
	Entity(SDL_Texture* texture);
	Entity(const char* pathToTexture, SDL_Renderer* renderer);
	SDL_Texture* _texture;
};