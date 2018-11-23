#include "Candle.h"



Candle::Candle() : GameObject()
{
	AddAnimation(BIG_CANDLE_ANI);
	AddAnimation(EFFECT_ANI);

	SetState(BIG_CANDLE);
}

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
	right = x + CANDLE_BBOX_WIDTH;
	bottom = y + CANDLE_BBOX_HEIGHT;
}
