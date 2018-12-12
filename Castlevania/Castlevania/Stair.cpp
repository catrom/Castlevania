#include "Stair.h"



Stair::Stair()
{
	AddAnimation(STAIR_LEFT_UP_ANI);
	AddAnimation(STAIR_RIGHT_DOWN_ANI);
}


Stair::~Stair()
{
}

void Stair::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_STAIR, FILEPATH_TEX_STAIR, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texStair = textures->Get(ID_TEX_STAIR);

	sprites->Add(100001, 0, 0, 32, 32, texStair);
	sprites->Add(100002, 32, 0, 64, 32, texStair);

	LPANIMATION ani;

	ani = new Animation();
	ani->Add(100001);
	animations->Add(STAIR_LEFT_UP_ANI, ani);

	ani = new Animation();
	ani->Add(100002);
	animations->Add(STAIR_RIGHT_DOWN_ANI, ani);
}

void Stair::Render()
{
	animations[state]->Render(1, -1, x, y);
}

void Stair::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = l + STAIR_BBOX_WIDTH;
	b = t + STAIR_BBOX_HEIGHT;
}

void Stair::GetActiveBoundingBox(float & left, float & top, float & right, float & bottom)
{
	GetBoundingBox(left, top, right, bottom);
}
