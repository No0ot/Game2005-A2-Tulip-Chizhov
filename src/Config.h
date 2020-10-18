#pragma once
#ifndef __CONFIG__
#define __CONFIG__

#include <SDL_ttf.h>
#include <memory>
#include "glm/vec2.hpp"

class Config {
public:
	static const int SCREEN_WIDTH = 1600;
	static const int SCREEN_HEIGHT = 900;
	static const float PX_PER_METER;
	static const int TILE_SIZE = 50;
	static const int ROW_NUM = SCREEN_HEIGHT / TILE_SIZE;
	static const int COL_NUM = SCREEN_WIDTH / TILE_SIZE;
	static const int TILE_COST = 1;
	static const int MINE_NUM = 50;
	static const int SCORE = 0;
	static const int LIVES = 5;

	// Define Custom Deleters for shared_ptr types
	static void SDL_DelRes(SDL_Window* r) { SDL_DestroyWindow(r); }
	static void SDL_DelRes(SDL_Renderer* r) { SDL_DestroyRenderer(r); }
	static void SDL_DelRes(SDL_Texture* r) { SDL_DestroyTexture(r); }
	static void SDL_DelRes(SDL_Surface* r) { SDL_FreeSurface(r); }
	static void SDL_DelRes(TTF_Font* r) { TTF_CloseFont(r); }

	// template function to create and return shared_ptr instance
	template <typename T>
	static std::shared_ptr<T> make_resource(T* t) {
		return std::shared_ptr<T>(t, [](T* t) { Config::SDL_DelRes(t); });
	}

};

const float PX_PER_METER = 10;

#endif /* defined (__CONFIG__) */