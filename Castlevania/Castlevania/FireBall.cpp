#include "FireBall.h"



FireBall::FireBall()
{
	AddAnimation(FIREBALL_ANI);
	SetState(FIREBALL);
}


FireBall::~FireBall()
{
}

void FireBall::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_FIREBALL, FILEPATH_TEX_FIREBALL, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texFireball = textures->Get(ID_TEX_FIREBALL);

	sprites->Add(160001, 0, 0, 14, 12, texFireball);
	

	LPANIMATION ani;

	ani = new Animation(100);
	ani->Add(160001);
	animations->Add(FIREBALL_ANI, ani);
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

void FireBall::GetActiveBoundingBox(float & left, float & top, float & right, float & bottom)
{
	GetBoundingBox(left, top, right, bottom);
}

