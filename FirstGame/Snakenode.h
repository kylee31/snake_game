#pragma once
#include "SDL.h"

class Node
{
public:
	Node();
	~Node();

	void AddFront(int a, int b);
	void AddTail(int a, int b);
	void DeleteTail();
	void DeleteHead();

	void GridToPixel(int i, int j, int &x, int &y);
	void DrawSnakeNode(int i, int j);
	void DrawFood(int i, int j);

	int i;
	int j;
	Node *next;
};