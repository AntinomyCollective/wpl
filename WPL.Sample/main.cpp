
#include "../WPL/WPL.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"
#include <iostream>

#pragma comment(lib, "SDL2/SDL2main.lib")
#pragma comment(lib, "SDL2/SDL2.lib")
#pragma comment(lib, "WPL.lib")

using namespace std;
using namespace wpl;

int main(int argc, char * argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	auto window = SDL_CreateWindow("Demo", 100, 100, 800, 500, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);

	VideoPlayer videoPlayer(wmInfo.info.win.window);
	videoPlayer.openVideo(L"demo.wmv");
	videoPlayer.play();

	auto exit = SDL_FALSE;

	while(!exit) {
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				exit = SDL_TRUE;
				break;
			}

			if(event.key.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
					case SDLK_RIGHT: videoPlayer.play(); break;
					case SDLK_LEFT: videoPlayer.pause(); break;
					case SDLK_DOWN: videoPlayer.stop(); break;

					default: break;
				}
			}
		}

		videoPlayer.updateVideoWindow();
		videoPlayer.repaint();
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return(0);
}
