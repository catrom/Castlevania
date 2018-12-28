#include "Bat.h"



Bat::Bat()
{
	AddAnimation("bat_ani");
	SetState(0);

	vx = (float)(-50 + rand() % 100) / 1000;
	vy = (float)(-50 + rand() % 100) / 1000;

	x = 100 + rand() % 300;
	y = 50 + rand() % 100;
}

Bat::~Bat()
{
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	GameObject::Update(dt);

	x += dx;
	y += dy;
}

void Bat::Render()
{
	animations[state]->Render(0, 0, x, y);
}

void Bat::SetState(int state)
{
	GameObject::SetState(state);
}
