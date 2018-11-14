#include "Candle.h"



void Candle::LoadResources()
{
	Textures * texture = Textures::GetInstance();

	texture->Add(ID_TEX_CANDLE, FILEPATH_TEX_CANDLE, D3DCOLOR_XRGB(255, 255, 255));

	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();

	LPDIRECT3DTEXTURE9 texCandle = texture->Get(ID_TEX_CANDLE);

	sprites->Add(30001, 0, 0, 32, 64, texCandle); // normal candle
	sprites->Add(30002, 32, 0, 64, 64, texCandle);


	LPANIMATION ani;

	ani = new Animation();
	ani->Add(30001, 150);
	ani->Add(30002, 150);
	animations->Add(10, ani);

	AddAnimation(10);

	SetPosition(300.0f, 300.0f);
}

void Candle::Render()
{
	animations[state]->Render(nx, x, y);
}
