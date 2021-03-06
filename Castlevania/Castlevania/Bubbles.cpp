﻿#include "Bubbles.h"



Bubble::Bubble()
{
	AddAnimation("bubbles_ani");
	SetState(0);
}

void Bubble::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	GameObject::Update(dt);
	vy += BUBBLES_GRAVITY*dt;

	x += dx;
	y += dy;
}

void Bubble::Render()
{
	animations[state]->Render(1, nx, x, y);
}

Bubbles::Bubbles(float x, float y)
{
	// Khởi tạo 3 bubble

	Bubble * bubble;

	for (int i = 0; i < 3; i++)
	{
		bubble = new Bubble();
		bubble->SetPosition(x, y);

		float vx = (float)(-100 + rand() % 200) / 1000;
		float vy = (float)(-100 + rand() % 200) / 1000;
		bubble->SetSpeed(vx, vy);

		bubbles.push_back(bubble);
	}
}

Bubbles::~Bubbles()
{
	for (UINT i = 0; i < 3; i++)
		delete(bubbles[i]);

	bubbles.clear();
}

void Bubbles::Update(DWORD dt)
{
	for (auto bubble : bubbles)
	{
		bubble->Update(dt);
	}
}

void Bubbles::Render()
{
	for (auto bubble : bubbles)
	{
		bubble->Render();
	}
}


