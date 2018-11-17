#include "Dagger.h"



Dagger::Dagger() : GameObject()
{
	vx = ITEM_DAGGER_SPEED;
	AddAnimation(DAGGER_ANI);
	SetState(DAGGER_STATE);
}

void Dagger::Render()
{
	animations[state]->Render(-nx, x, y);
}

void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT>* Objects, vector<LPGAMEOBJECT*>* coObject)
{
	if (nx < 0) vx = -ITEM_DAGGER_SPEED;
	else vx = ITEM_DAGGER_SPEED;

	GameObject::Update(dt);
	x += dx;
}

void Dagger::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + DAGGER_BBOX_WIDTH;
	bottom = top + DAGGER_BBOX_HEIGHT;
}

