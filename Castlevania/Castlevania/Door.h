#pragma once

#include "GameObject.h"

class Door : public GameObject
{
public:
	Door();
	~Door();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false) {}
	virtual void Render();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom);
	
};

