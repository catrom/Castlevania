#pragma once

#include "GameObject.h"
#include "Sprites.h"
#include "Textures.h"

class Effect : public GameObject
{
public:
	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	void Render();


	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {}
};

