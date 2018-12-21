#pragma once

#include "GameObject.h"

class Stair : public GameObject
{
public:
	Stair();
	~Stair();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);

	virtual void Render();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom);
};

