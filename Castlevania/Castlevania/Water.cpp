#include "Water.h"

void Water::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	DWORD now = GetTickCount();

	for (UINT i = 0; i < bubblesList.size(); i++)
	{
		if (now - bubblesList[i]->GetStartTimeRender() > BUBBLES_TIME)
		{
			bubblesList.erase(bubblesList.begin() + i);
			i--;
		}
		else
			bubblesList[i]->Update(dt);
	}
}

void Water::Render()
{
	for (auto bubbles : bubblesList)
		bubbles->Render();
}

void Water::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x - WATER_BBOX_WIDTH;
	r = x + WATER_BBOX_WIDTH;
	t = y;
	b = t + WATER_BBOX_HEIGHT;
}

void Water::AddBubbles(float x, float y)
{
	Bubbles * bubbles = new Bubbles(x, y);
	bubbles->SetStartTimeRender(GetTickCount());

	bubblesList.push_back(bubbles);
}
