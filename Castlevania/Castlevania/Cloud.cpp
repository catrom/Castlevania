#include "Cloud.h"



Cloud::Cloud()
{
	AddAnimation("cloud_ani");
	SetState(0);

	x = 440;
	y = 160;
	vx = -0.015f;
	vy = -0.003f;
}

Cloud::~Cloud()
{
}

void Cloud::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	GameObject::Update(dt);
	x += dx;
	y += dy;
}

void Cloud::Render()
{
	animations[state]->Render(0, 0, x, y);
}

void Cloud::SetState(int state)
{
	GameObject::SetState(state);
}
