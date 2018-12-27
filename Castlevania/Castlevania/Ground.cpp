#include "Ground.h"

Ground::Ground() : GameObject()
{
	AddAnimation("ground1_ani");
	AddAnimation("ground2_ani");
}

void Ground::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_GROUND, FILEPATH_TEX_GROUND, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texGround = textures->Get(ID_TEX_GROUND);

	sprites->Add("ground1", 0, 0, 32, 32, texGround);
	sprites->Add("ground2", 32, 0, 64, 32, texGround);

	LPANIMATION ani;

	ani = new Animation();
	ani->Add("ground1");
	animations->Add("ground1_ani", ani);

	ani = new Animation();
	ani->Add("ground2");
	animations->Add("ground2_ani", ani);
}

void Ground::Render()
{
	animations[state]->Render(1, -1, x, y);
}

void Ground::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = l + GROUND_BBOX_WIDTH;
	b = t + GROUND_BBOX_HEIGHT;
}

void Ground::GetActiveBoundingBox(float & left, float & top, float & right, float & bottom)
{
	GetBoundingBox(left, top, right, bottom);
}
