#include "BreakWall.h"

BreakWall::BreakWall()
{
	AddAnimation("");
	AddAnimation("wall_break_ani");
}

void BreakWall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	if (state == BREAK && isBreakToPieces == false)
	{
		isBreakToPieces = true;
		pieces = new WallPieces(x, y);
	}

	if (pieces != NULL)
		pieces->Update(dt);
}

void BreakWall::Render()
{
	if (state == NORMAL)
		return;

	animations[state]->Render(1, -1, x, y);

	if (isBreakToPieces == true && pieces != NULL)
	{
		if (pieces->GetStartTimeRender() == 0)
			pieces->SetStartTimeRender(GetTickCount());
		else if (GetTickCount() - pieces->GetStartTimeRender() > WALLPIECES_TIME)
		{
			delete pieces;
			pieces = NULL;
			return;
		}

		pieces->Render();
	}
}

void BreakWall::SetState(int state)
{
	GameObject::SetState(state);
}

void BreakWall::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + GROUND_BBOX_WIDTH;
	bottom = top + GROUND_BBOX_HEIGHT;
}




