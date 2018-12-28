#pragma once

#include "GameObject.h"

class Bat : public GameObject
{
public:
	Bat();
	~Bat();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);
	virtual void Render();
	virtual void SetState(int state);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {}
};

