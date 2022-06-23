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
	//��� �̹���
	SDL_Rect bg_source_rect;
	SDL_Rect bg_destination_rect;
	SDL_Texture* bg_texture;

	//jet �̹���
	SDL_Rect jet_source_rect;
	SDL_Rect jet_destination_rect;
	SDL_Texture* jet_texture;

	//missile �̹���
	SDL_Rect missile_source_rect;
	SDL_Rect missile_destination_rect;
	SDL_Texture* missile_texture;

	//�ؽ�Ʈ
	SDL_Texture *title_score_en;
	SDL_Rect title_score_en_rect;

	//���� �ؽ�Ʈ
	SDL_Texture *text_time;
	SDL_Rect text_time_rect;
};