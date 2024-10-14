#ifndef SDL_wrapper_H
#define SDL_wrapper_H
#include "SDL.h"
#include <SDL_ttf.h>
#include <iostream>

class SDLWrapper {
private:
	SDL_Window* fenetre;
	SDL_Renderer* renderer;
	bool isRunning;
	//texte/compteur fps
	TTF_Font* font;
	SDL_Texture* fpsTexture;
	int texW, texH;
	Uint32 lastFrameTime;
	int framecount;

public:
	SDLWrapper(const char* title, int win_width, int win_height);
	~SDLWrapper();
	
	bool processEvents();
	void clearScreen(Uint8 r, Uint8 g, Uint8 b);
	void updateScreen();
	SDL_Renderer* getRenderer();
	void getWindowSize(int& win_width,int& win_height);
	bool running() const;

	//texte/fps
	SDL_Texture* renderText(const std::string& message, SDL_Color color, int fontSize);
	float calculateFPS();
	void updateFPS();
	void renderFPS();
	
};

#endif
