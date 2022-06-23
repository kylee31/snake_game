#include "GameStage.h"
#include "GameClassPhase.h"
#include "Snakenode.h"

#include <iostream>
#include <windows.h>
#include <atlstr.h>
#include <string>
#include <cstdlib>
#include <ctime>

#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;

//상태 변화
int vect;

//배경 이미지
SDL_Rect bg_source_rect;
SDL_Rect bg_destination_rect;
SDL_Texture* bg_texture;

//배경음
Mix_Chunk *wave1;
Mix_Music *music1;

//텍스트
TTF_Font *game_font1;
SDL_Texture *title_score_en;
SDL_Rect title_score_en_rect;

//점수 텍스트
SDL_Texture *text_time;
SDL_Rect text_time_rect;


//노드의 좌표
int num_x;
int num_y;

//먹이 먹은 횟수
int eaten;


// 점수계산
int score;

extern Node *head;

Node *nd;
Node *eating;
Node eat;


 Stage::Stage()
{
	g_flag_running = true;

	srand((unsigned int)time(NULL));
	eat.i = rand() % 19;
	eat.j = rand() % 19;
	
	//초기 몸통
	nd->AddFront(0, 0);
	nd->AddFront(1, 0);
	nd->AddFront(2,0);

	

	//배경 이미지
	{
		SDL_Surface* bg_surface = IMG_Load("../img/space.jpg");

		bg_destination_rect.x = bg_source_rect.x = 0;
		bg_destination_rect.y = bg_source_rect.y = 0;
		bg_destination_rect.w = bg_source_rect.w = bg_surface->w;
		bg_destination_rect.h = bg_source_rect.h = bg_surface->h;

		bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
		SDL_FreeSurface(bg_surface);
	}


	// 글꼴과 크기, 색상 등
	{
		game_font1 = TTF_OpenFont("../Resources/moris.ttf", 30);


		SDL_Color white = { 0, 0, 0, 0 };
		SDL_Surface *tmp_surface = TTF_RenderText_Blended(game_font1, "SCORE :  ", white);

		title_score_en_rect.x = 0;
		title_score_en_rect.y = 0;
		title_score_en_rect.w = tmp_surface->w;
		title_score_en_rect.h = tmp_surface->h;

		title_score_en = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

		SDL_FreeSurface(tmp_surface);
		TTF_CloseFont(game_font1);
	}

	// 배경음악
	Mix_VolumeMusic(128);

	wave1 = Mix_LoadWAV("../Resources/eating.wav");
	if (wave1 == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}
	
	music1=Mix_LoadMUS("../Resources/lovely.mp3");
	if(!music1)
	{
		printf(" %s\n", Mix_GetError());
	}

	Mix_FadeInMusic(music1, -1, 2000);

	num_x = 1;
	num_y = 1;
	vect = 0;
	eaten = 0;
	
	score = 0;
	text_time = 0;

	system("cls");
}



 void Food() {

	 nd->AddFront(eat.i, eat.j);
	 score += 1;

	 if (num_x == eat.i&&num_y == eat.j) {

		 srand((unsigned int)time(NULL));
		 eat.i = rand() % 19;
		 eat.j = rand() % 19;
	 }
 }



 void Clear() {

	 vect = 0;
	 
	 Node *n = head;
	 while (n != nullptr) {
		 n->DeleteHead();
		 n = n->next;
	 }
	
	 nd->AddFront(1, 0);
	 nd->AddFront(2, 0);

	 num_x = 0;
	 num_y = 0;

	 eat.i = 0;
	 eat.j = 0;

	 score = -1;
}



bool Search() {
	Node *n = head->next;
	while (n != nullptr) {
		if (num_x == n->i && num_y == n->j) return true;
		n = n->next;
	 }
	return false;
}



void Stage::Update()
{
	//상태
	if (vect == 1)
	{
		num_x -= 1;
		nd->AddFront(num_x, num_y);
		nd->DeleteTail();

		if (num_x < 0) {
			eaten = -1;
			g_current_game_phase = PHASE_ENDING;
			Clear();
		}
	}

	if (vect == 2)
	{
		num_x += 1;
		nd->AddFront(num_x, num_y);
		nd->DeleteTail();

		if (num_x >= 20) {
			eaten = -1;
			g_current_game_phase = PHASE_ENDING;
			Clear();
		}
	}

	if (vect == 3)
	{
		num_y -= 1;
		nd->AddFront(num_x, num_y);
		nd->DeleteTail();

		if (num_y < 0) {
			eaten = -1;
			g_current_game_phase = PHASE_ENDING;
			Clear();
		}
	}

	if (vect == 4)
	{
		num_y += 1;
		nd->AddFront(num_x, num_y);
		nd->DeleteTail();

		if (num_y >= 20) {
			//num_y = 19;
			eaten = -1;
			g_current_game_phase = PHASE_ENDING;
			Clear();
		}
	}

	//몸통과 머리 부딪힘 검사

	if (Search() == true) {
		eaten = -1;
		g_current_game_phase = PHASE_ENDING;
		Clear();
	}
	

	//먹이
	if (num_x == eat.i && num_y == eat.j) {
		eaten += 1;
		Mix_PlayChannel(-1, wave1, 0);
		if (eaten == 10) {
			eaten = 0;
			g_current_game_phase = PHASE_CLEAR;
			Clear();
		}
		Food();
	}


	if (text_time != 0)
	{
		SDL_DestroyTexture(text_time);		// !!!중요!!!  이미 생성되어있는 texture 가 있으면 반드시 메모리에서 지워야한다. !!!
		text_time = 0;
	}

	game_font1 = TTF_OpenFont("../Resources/moris.ttf", 30);
	SDL_Color black = { 0, 0, 0, 0 };
	SDL_Surface *tmp_surface = TTF_RenderText_Blended(game_font1, std::to_string((long long)score).c_str(), black);

	text_time_rect.x = 100;
	text_time_rect.y = 20;
	text_time_rect.w = tmp_surface->w;
	text_time_rect.h = tmp_surface->h;

	text_time = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

	SDL_FreeSurface(tmp_surface);

}



void Stage::Render()
{
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color
	SDL_RenderCopy(g_renderer, bg_texture, &bg_source_rect, &bg_destination_rect);
	{
		Node *n = head;
		while (n != nullptr) {
			nd->DrawSnakeNode(n->i, n->j);
			n = n->next;
		}
	}
	eating->DrawFood(eat.i,eat.j);

	//텍스트							
	{
		SDL_Rect r;
		r.x = 50;
		r.y = 15;
		r.w = title_score_en_rect.w;
		r.h = title_score_en_rect.h;
		SDL_RenderCopy(g_renderer, title_score_en, 0, &r);
	}

	{
		SDL_Rect r;
		r.x = 160;
		r.y = 15;
		r.w = text_time_rect.w;
		r.h = text_time_rect.h;
		SDL_RenderCopy(g_renderer, text_time, 0, &r);
	}

	SDL_RenderPresent(g_renderer);
}



void Stage::HandleEvents()
{	
	SDL_Event event;

	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			if ( event.key.keysym.sym == SDLK_LEFT ){
				if (vect == 2) {
					vect = 2;
				}else{
				vect = 1;
				}
			}
			if ( event.key.keysym.sym == SDLK_RIGHT ){
				if (vect == 1) {
					vect = 1;
				}
				else{
				vect = 2;
				}
			}
			if (event.key.keysym.sym == SDLK_UP){
				if (vect == 4) {
					vect = 4;
				}
				else{
				vect = 3;
				}
			}
			if (event.key.keysym.sym == SDLK_DOWN){
				if (vect == 3) {
					vect = 3;
				}
				else{
				vect = 4;
				}
			}
			break;

		default:
			break;
		}
	}
}



Stage::~Stage()
{
	SDL_DestroyTexture(bg_texture);
	if (wave1) Mix_FreeChunk(wave1);
	if (music1) Mix_FreeMusic(music1);
	SDL_DestroyTexture(title_score_en);
}