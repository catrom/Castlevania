#include "FireBall.h"



FireBall::FireBall()
{
	AddAnimation("fireball_ani");
	SetState(FIREBALL);
}

void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	if (stopMovement == true)
		return;

	GameObject::Update(dt);
	x += dx;
}

void FireBall::Render()
{
	animations[state]->Render(1, nx, x, y);
}

void FireBall::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case FIREBALL:
		if (nx == 1) vx = FIREBALL_SPEED;
		else vx = -FIREBALL_SPEED;
		vy = 0;
		break;
	default:
		break;
	}
}

void FireBall::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + FIREBALL_BBOX_WIDTH;
	bottom = top + FIREBALL_BBOX_HEIGHT;
}
