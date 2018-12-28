#include "Stair.h"



Stair::Stair()
{
	AddAnimation("stair_leftup_ani");
	AddAnimation("stair_rightdown_ani");
}

void Stair::Render()
{
	animations[state]->Render(1, -1, x, y);
}

void Stair::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = l + STAIR_BBOX_WIDTH;
	b = t + STAIR_BBOX_HEIGHT;
}
