#pragma once

#include <vector>

#include "GameObject.h"
#include "Bubbles.h"

class Water : public GameObject
{
	vector<Bubbles *> bubblesList;

public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	void AddBubbles(float x, float y);
};

