#include "Candle.h"



void Candle::LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations)
{
	textures->Add(ID_TEX_CANDLE, FILEPATH_TEX_CANDLE, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texCandle = textures->Get(ID_TEX_CANDLE);

	sprites->Add(30001, 0, 0, 32, 64, texCandle); // normal candle
	sprites->Add(30002, 32, 0, 64, 64, texCandle);


	LPANIMATION ani;

	ani = new Animation();
	ani->Add(30001, 150);
	ani->Add(30002, 150);
	animations->Add(BIG_CANDLE_ANI, ani);
}

void Candle::Render()
{
	animations[state]->Render(nx, x, y);
}

void Candle::DestroyedEffect()
{
	Effect * effect = new Effect();
	effect->AddAnimation(EFFECT_ANI);
	effect->SetState(EFFECT);
	effect->SetPosition(x, y);
	effect->Render();
}

void Candle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + CANDLE_BBOX_WIDTH;
	bottom = y + CANDLE_BBOX_HEIGHT;
}
