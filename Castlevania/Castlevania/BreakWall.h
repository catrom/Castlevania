#pragma once

#include "GameObject.h"
#include "WallPieces.h"

class BreakWall : public GameObject
{
	bool isBreakToPieces = false;
	WallPieces * pieces = NULL;

public:
	BreakWall();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);
	void Render();
	void SetState(int state);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

