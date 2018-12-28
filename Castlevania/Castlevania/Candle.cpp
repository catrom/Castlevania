#include "Candle.h"



Candle::Candle() : GameObject()
{
	AddAnimation("bigcandle_ani");
	AddAnimation("smallcandle_ani");
	AddAnimation("effect1_ani");

	SetState(BIG_CANDLE);
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