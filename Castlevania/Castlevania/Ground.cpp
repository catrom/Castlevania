#include "Ground.h"

Ground::Ground() : GameObject()
{
	AddAnimation("ground1_ani");
	AddAnimation("ground2_ani");
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