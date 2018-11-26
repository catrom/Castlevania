#include "Candle.h"



Candle::Candle() : GameObject()
{
	AddAnimation(BIG_CANDLE_ANI);
	AddAnimation(SMALL_CANDLE_ANI);
	AddAnimation(EFFECT_ANI);

	SetState(BIG_CANDLE);
}

void Candle::LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations)
{
	textures->Add(ID_TEX_CANDLE, FILEPATH_TEX_CANDLE, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_SMALL_CANDLE, FILEPATH_TEX_SMALL_CANDLE, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texBigCandle = textures->Get(ID_TEX_CANDLE);

	sprites->Add(30001, 0, 0, 32, 64, texBigCandle); // normal candle
	sprites->Add(30002, 32, 0, 64, 64, texBigCandle);

	LPDIRECT3DTEXTURE9 texSmallCandle = textures->Get(ID_TEX_SMALL_CANDLE);
	sprites->Add(30003, 0, 0, 16, 32, texSmallCandle); // normal candle
	sprites->Add(30004, 16, 0, 32, 32, texSmallCandle);

	LPANIMATION ani;

	ani = new Animation();
	ani->Add(30001, 150);
	ani->Add(30002, 150);
	animations->Add(BIG_CANDLE_ANI, ani);

	ani = new Animation();
	ani->Add(30003, 150);
	ani->Add(30004, 150);
	animations->Add(SMALL_CANDLE_ANI, ani);

}

void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>* Objects, vector<LPGAMEOBJECT>* coObject)
{
	if (state == DESTROYED && animations[state]->IsOver(150)) 	//nếu render xong hết đốm lửa rồi thì set enable = false -> biến mất
	{
		this->isEnable = false;

		if (idItem != -1)
		{
			// Tạo một item theo id và thêm vào Objects

			Items * item = new Items();
			item->isEnable = true;
			item->SetPosition(x, y);
			item->SetItem(idItem);

			Objects->push_back(item);
		}
	}
		
}

void Candle::Render()
{
	animations[state]->Render(1, nx, x, y);
}

void Candle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	if (state == BIG_CANDLE)
	{
		right = left + CANDLE_BBOX_WIDTH;
		bottom = top + CANDLE_BBOX_HEIGHT;
	}
	
	else if (state == SMALL_CANDLE)
	{
		right = left + SMALL_CANDLE_BBOX_WIDTH;
		bottom = top + SMALL_CANDLE_BBOX_HEIGHT;
	}
}
