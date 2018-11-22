#include "Ground.h"

Ground::Ground() : GameObject()
{
	AddAnimation(GROUND_ANI_1);
	AddAnimation(GROUND_ANI_2);
}

void Ground::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_GROUND, FILEPATH_TEX_GROUND, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texGround = textures->Get(ID_TEX_GROUND);

	sprites->Add(40001, 0, 0, 32, 32, texGround);
	sprites->Add(40002, 32, 0, 64, 32, texGround);

	LPANIMATION ani;

	ani = new Animation();
	ani->Add(40001);
	animations->Add(GROUND_ANI_1, ani);

	ani = new Animation();
	ani->Add(40002);
	animations->Add(GROUND_ANI_2, ani);
}

void Ground::Render()
{
	animations[state]->Render(-1, x, y);
}

void Ground::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + GROUND_BBOX_WIDTH;
	b = y + GROUND_BBOX_HEIGHT;
}
