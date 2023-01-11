#include "GameLogic.h"
#include <iostream>

// WEB = https://lazyfoo.net/tutorials/SDL/

Game::Game(int width, int height) {
	this->_window = nullptr;
	this->_renderer = nullptr;
	this->_width = width;
	this->_height = height;
}

void Game::Run() {
	this->Init();
	SDL_RenderSetScale(this->_renderer, 4, 4);

	SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
	SDL_Surface* sur = IMG_Load("res/textures/maze.png");
	SDL_Texture* texture;
	texture = SDL_CreateTextureFromSurface(this->_renderer, sur);
	SDL_FreeSurface(sur);
	SDL_Rect dest;
	dest.w = 5;
	dest.h = 5;
	dest.x = 20;
	dest.y = 100;
	Entity entity("res/textures/block.jpg", this->_renderer);

	int close = 0;
	int xM, yM;
	while (!close) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				close = 1;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_LEFT:
					dest.x -= 1;
					break;
				case SDL_SCANCODE_RIGHT:
					dest.x += 1;
					break;
				case SDL_SCANCODE_UP:
					dest.y -= 1;
					break;
				case SDL_SCANCODE_DOWN:
					dest.y += 1;
					break;
				default:
					break;
				}
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&xM, &yM);
				std::cout << "X: " << xM << "\nY: " << yM << "\n";
			}

		}
		if (dest.x < 0) {
			dest.x = 0;
		}
		if (dest.x - dest.w > this->_width) {
			dest.x = this->_width - dest.w;
		}
		if (dest.y - dest.h > this->_height) {
			dest.y = this->_height - dest.h;
		}
		if (dest.y < 0) {
			dest.y = 0;
		}
		this->Clear();
		this->DrawEntity(entity, dest);
		//SDL_BlitSurface(sur, NULL, this->_windowSurface, NULL);
		//SDL_UpdateWindowSurface(this->_window);
		//this->DrawRect(255,5,255,255, &dest);
		SDL_Delay(1000 / 60);
	}
	this->Exit();
}

void Game::DrawRect(int r, int g, int b, int a, SDL_Rect* rect) {
	SDL_SetRenderDrawColor(this->_renderer, r, g, b, a);
	SDL_RenderFillRect(this->_renderer, rect);
	SDL_RenderPresent(this->_renderer);
}

void Game::Clear() {
	SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
	SDL_RenderPresent(this->_renderer);
	SDL_RenderClear(this->_renderer);
}

void Game::Exit() {
	SDL_DestroyRenderer(this->_renderer);
	SDL_FreeSurface(this->_windowSurface);
	SDL_DestroyWindow(this->_window);
	SDL_Quit();
}

SDL_Color GetPixelColor(const SDL_Surface* pSurface, const int X, const int Y) {
	const Uint8 Bpp = pSurface->format->BytesPerPixel;

	Uint8* pPixel = (Uint8*)pSurface->pixels + Y * pSurface->pitch + X * Bpp;

	Uint32 PixelData = *(Uint32*)pPixel;

	SDL_Color Color = { 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE };

	SDL_GetRGB(PixelData, pSurface->format, &Color.r, &Color.g, &Color.b);

	return Color;
}

void Game::DrawEntity(Entity& entity, SDL_Rect& rect) {
	SDL_QueryTexture(entity._texture, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderClear(this->_renderer);
	SDL_RenderCopy(this->_renderer, entity._texture, NULL, &rect);
	SDL_RenderPresent(this->_renderer);
}

void Game::Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		return;
	}
	this->_window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->_width, this->_height, SDL_WINDOW_SHOWN);
	this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
	this->_windowSurface = SDL_GetWindowSurface(this->_window);
}