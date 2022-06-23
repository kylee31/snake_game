#include <iostream>
#include "Snakenode.h"
#include "SDL_image.h"

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;

//몸통 이미지
SDL_Rect jet_source_rect;
SDL_Rect jet_destination_rect;
SDL_Texture* jet_texture;

//먹이 이미지
SDL_Rect missile_source_rect;
SDL_Rect missile_destination_rect;
SDL_Texture* missile_texture;

Node *head = nullptr;
Node *tail = nullptr;

Node::Node(){
	{
		SDL_Surface* temp_surface = IMG_Load("../img/jelly.png");

		jet_source_rect.x = 0;
		jet_source_rect.y = 0;
		jet_source_rect.w = 100;
		jet_source_rect.h = 100;

		jet_destination_rect.x ;					//도착하는 지점의 위치
		jet_destination_rect.y ;					//도착하는 지점의 위치
		jet_destination_rect.w = jet_source_rect.w;		//넓이(크기)
		jet_destination_rect.h = jet_source_rect.h;		//높이(크기)

		jet_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
	}


	//미사일 이미지
	{
		SDL_Surface* temp_surface = IMG_Load("../img/food.png");

		missile_source_rect.x = 0;
		missile_source_rect.y = 0;
		missile_source_rect.w = 100;
		missile_source_rect.h = 100;

		missile_destination_rect.x;
		missile_destination_rect.y;
		missile_destination_rect.w = missile_source_rect.w;
		missile_destination_rect.h = missile_source_rect.h;

		missile_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
	}
}

Node::~Node() {
}

void Node::AddFront(int a,int b) {
	Node *n = new Node;
	n->next = head;
	head = n;
	head->i = a;
	head->j = b;
}

void Node::AddTail(int a, int b) {
	Node *n = head;
	while (n->next != nullptr) {
		n = n->next;
	}
	n->next = new Node;
	n->next->next = nullptr;

	tail= head;
	while (tail->next != nullptr) {
		tail = tail->next;
	}
	tail->i=a;
	tail->j=b;
}

void Node::DeleteTail() {
	if (head == nullptr) return;
	if (head->next == nullptr) {
		delete head;
		head = nullptr;
	}
	else {
		Node *n = head;
		while (n->next->next != nullptr) {
			n = n->next;
		}
		delete n->next;
		n->next = nullptr;
	}
}

void Node::DeleteHead() {
	Node *n = head;
	head = head->next;
	delete n;
}

void Node::GridToPixel(int i, int j, int &x, int &y) {
	x = 50 + 400*(double)i / (double)20;
	y = 50 + 400*(double)j / (double)20;
}

void Node::DrawSnakeNode(int a, int b) {
	int x, y;
	GridToPixel(a, b, x, y);
	SDL_Rect r = {jet_destination_rect.x =x,jet_destination_rect.y=y, jet_destination_rect.w =20, jet_destination_rect.h=20 };
	SDL_RenderCopy(g_renderer, jet_texture, &jet_source_rect, &jet_destination_rect);//내 캐릭터 그리기
	//SDL_RenderFillRect(g_renderer, &r);
}

void Node::DrawFood(int a, int b) {
	int x, y;
	GridToPixel(a, b, x, y);
	SDL_Rect r = { missile_destination_rect.x = x,missile_destination_rect.y = y, missile_destination_rect.w = 20, missile_destination_rect.h = 20 };
	SDL_RenderCopy(g_renderer, missile_texture, &missile_source_rect, &missile_destination_rect);
}