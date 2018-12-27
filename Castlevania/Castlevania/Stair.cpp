#include "Stair.h"



Stair::Stair()
{
	AddAnimation("stair_leftup_ani");
	AddAnimation("stair_rightdown_ani");
}


Stair::~Stair()
{
}

void Stair::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_STAIR, FILEPATH_TEX_STAIR, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texStair = textures->Get(ID_TEX_STAIR);

	sprites->Add("stair_leftup", 0, 0, 32, 32, texStair);
	sprites->Add("stair_rightdown", 32, 0, 64, 32, texStair);

	LPANIMATION ani;

	ani = new Animation();
	ani->Add("stair_leftup");
	animations->Add("stair_leftup_ani", ani);

	ani = new Animation();
	ani->Add("stair_rightdown");
	animations->Add("stair_rightdown_ani", ani);
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
