#include "Entity.h"

Entity::Entity(SDL_Texture* texture) {
	this->_texture = texture;
}
Entity::Entity(const char* pathToTexture, SDL_Renderer* renderer) {
	SDL_Surface* sur = IMG_Load(pathToTexture);
	SDL_Texture* texture;
	this->_texture = SDL_CreateTextureFromSurface(renderer, sur);
	SDL_FreeSurface(sur);
}