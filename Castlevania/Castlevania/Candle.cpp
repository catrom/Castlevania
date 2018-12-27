#include "Candle.h"



Candle::Candle() : GameObject()
{
	AddAnimation("bigcandle_ani");
	AddAnimation("smallcandle_ani");
	AddAnimation("effect1_ani");

	SetState(BIG_CANDLE);
}

void Candle::LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations)
{
	textures->Add(ID_TEX_CANDLE, FILEPATH_TEX_CANDLE, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_SMALL_CANDLE, FILEPATH_TEX_SMALL_CANDLE, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texBigCandle = textures->Get(ID_TEX_CANDLE);

	sprites->Add("bigcandle_1", 0, 0, 32, 64, texBigCandle); // normal candle
	sprites->Add("bigcandle_2", 32, 0, 64, 64, texBigCandle);

	LPDIRECT3DTEXTURE9 texSmallCandle = textures->Get(ID_TEX_SMALL_CANDLE);
	sprites->Add("smallcandle_1", 0, 0, 16, 32, texSmallCandle); // normal candle
	sprites->Add("smallcandle_2", 16, 0, 32, 32, texSmallCandle);

	LPANIMATION ani;

	ani = new Animation();
	ani->Add("bigcandle_1", 150);
	ani->Add("bigcandle_2", 150);
	animations->Add("bigcandle_ani", ani);

	ani = new Animation();
	ani->Add("smallcandle_1", 150);
	ani->Add("smallcandle_2", 150);
	animations->Add("smallcandle_ani", ani);

}

void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	if (state == CANDLE_DESTROYED && animations[state]->IsOver(EFFECT_ANI_TIME_DELAY) == true) 	//nếu render xong hết đốm lửa rồi thì set enable = false -> biến mất
		this->isEnable = false;
}

void Candle::Render()
{
	animations[state]->Render(1, nx, x, y);
}

void Candle::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case BIG_CANDLE:
	case SMALL_CANDLE:
		break;
	case CANDLE_DESTROYED:
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	default:
		break;
	}
}

void Candle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	switch (state)
	{
	case BIG_CANDLE:
		right = left + CANDLE_BBOX_WIDTH;
		bottom = top + CANDLE_BBOX_HEIGHT;
		break;
	case SMALL_CANDLE:
		right = left + SMALL_CANDLE_BBOX_WIDTH;
		bottom = top + SMALL_CANDLE_BBOX_HEIGHT;
		break;
	default:
		right = left;
		bottom = top;
		break;
	}
}

void Candle::GetActiveBoundingBox(float & left, float & top, float & right, float & bottom)
{
	GetBoundingBox(left, top, right, bottom);
}
