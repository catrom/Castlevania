#pragma once

#include "GameObject.h"

class WallPiece : public GameObject
{
public:
	WallPiece();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);
	void Render();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {}
};

typedef WallPiece * LPWALLPIECES;

// Mỗi cụm có 4 pieces
class WallPieces
{
	DWORD startTime = 0;
	vector<LPWALLPIECES> pieces;

public:
	WallPieces(float x, float y);
	~WallPieces();

	void Update(DWORD dt);
	void Render();

	DWORD GetStartTimeRender() { return startTime; }
	void SetStartTimeRender(DWORD x) { startTime = x; }
};

