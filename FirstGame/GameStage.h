#pragma once

#include "SDL.h"

class Stage{
public:
	Stage();	//void InitGame();
	~Stage();	//void ClearGame();

	void HandleEvents();
	void Update();
	void Render();

private:
	//배경 이미지
	SDL_Rect bg_source_rect;
	SDL_Rect bg_destination_rect;
	SDL_Texture* bg_texture;

	//jet 이미지
	SDL_Rect jet_source_rect;
	SDL_Rect jet_destination_rect;
	SDL_Texture* jet_texture;

	//missile 이미지
	SDL_Rect missile_source_rect;
	SDL_Rect missile_destination_rect;
	SDL_Texture* missile_texture;

	//텍스트
	SDL_Texture *title_score_en;
	SDL_Rect title_score_en_rect;

	//점수 텍스트
	SDL_Texture *text_time;
	SDL_Rect text_time_rect;
};