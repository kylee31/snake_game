#include "SDL.h"
#include <iostream>

#include "GameClassPhase.h"
#include "GameStage.h"
#include "GameIntro.h"
#include "GameEnding.h"
#include "GameClear.h"

#include "SDL_mixer.h"
#include "SDL_ttf.h"


/////////////////////////////////////////////////
// Declaration
SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;

bool InitializeWindow(const char* title, int xpos, int ypos, int width, int height, int fullscreen);
void ClearWindow();

int g_current_game_phase;

int main(int argc, char* argv[])
{
	InitializeWindow("First Example", 10, 50, 500, 500, false);

	TTF_Init();

	// Open the audio device 
	int audio_rate = 44100;//MIX_DEFAULT_FREQUENCY;
	Uint16 audio_format = MIX_DEFAULT_FORMAT;
	int audio_channels = 2;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, 4096) < 0)
	{
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		Mix_CloseAudio();
	}
	else
	{
		// For debug
		Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
		printf("Opened audio at %d Hz %d bit %s\n", audio_rate,
			(audio_format & 0xFF),
			(audio_channels > 2) ? "surround" :
			(audio_channels > 1) ? "stereo" : "mono");

	}

	//InitGame();

	Intro intro;
	Stage stage;
	Ending end;
	Clear clear;

	g_current_game_phase = PHASE_INTRO;

	while ( g_flag_running )
	{

		if (g_current_game_phase == PHASE_INTRO)
		{
			intro.HandleEvents();
			intro.Update();
			intro.Render();
		}
		if (g_current_game_phase == PHASE_STAGE)
		{
			stage.HandleEvents();
			stage.Update();
			stage.Render();
		}
		if (g_current_game_phase == PHASE_ENDING)
		{
			end.HandleEvents();
			end.Update();
			end.Render();
		}
		if (g_current_game_phase == PHASE_CLEAR)
		{
			clear.HandleEvents();
			clear.Update();
			clear.Render();
		}
		SDL_Delay(100);	// 30 밀리세컨드 기다린다.
	}

	//ClearGame();
	ClearWindow();

	TTF_Quit();

	return 0;
}


////////////////////////////////////
// Functions for the Window
bool InitializeWindow(const char* title, int xpos, int ypos, int width, int height, int fullscreen)
{
	int flags = 0;
	if(fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// attempt to initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";
		// init the window
		g_window = SDL_CreateWindow(title, xpos, ypos, 
			width, height, flags);

		if(g_window != 0) // window init success
		{
			std::cout << "window creation success\n";
			g_renderer = SDL_CreateRenderer(g_window, -1, 0);
			if(g_renderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(g_renderer, 
					255,255,255,255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}
	std::cout << "init success\n";
	g_flag_running = true; // everything inited successfully, start the main loop

	return true;

}


void ClearWindow()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(g_window);
	SDL_DestroyRenderer(g_renderer);
	SDL_Quit();
}