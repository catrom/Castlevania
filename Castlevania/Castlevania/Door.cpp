#include "Door.h"



Door::Door() : GameObject()
{
	AddAnimation("door1_ani");
	AddAnimation("door2_idle_ani");
	AddAnimation("door2_open_ani");
}

void Door::Render()
{
	if (state == DOOR_2_OPEN && animations[state]->IsOver(DOOR_2_OPEN_ANI_TIME_DELAY) == true)
		state = DOOR_2_IDLE;

	animations[state]->Render(1, -1, x, y);
}

void Door::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	switch (state)
	{
	case DOOR_1:
		l = 1376;
		t = 272;
		r = l + DOOR_BBOX_WIDTH;
		b = t + DOOR_BBOX_HEIGHT;
		break;
	case DOOR_2_IDLE:
	case DOOR_2_OPEN:
		l = x - 16;
		t = y;
		r = l + DOOR_BBOX_WIDTH;
		b = t + DOOR_BBOX_HEIGHT;
		break;
	default:
		break;
	}
}