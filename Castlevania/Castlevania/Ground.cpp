#include "Ground.h"

Ground::Ground() : GameObject()
{

	Textures * texture = Textures::GetInstance();

	texture->Add(ID_TEX_GROUND, FILEPATH_TEX_GROUND, D3DCOLOR_XRGB(255, 255, 255));

	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();

	LPDIRECT3DTEXTURE9 texGround = texture->Get(ID_TEX_GROUND);

	sprites->Add(40001, 0, 0, 32, 32, texGround);
	
	LPANIMATION ani;

	ani = new Animation();
	ani->Add(40001);
	animations->Add(0, ani);

	AddAnimation(0);
	

}

void Ground::Render()
{
	animations[0]->Render(-1, x, y);
}

void Ground::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + GROUND_BBOX_WIDTH;
	b = y + GROUND_BBOX_HEIGHT;
}
