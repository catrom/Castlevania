#pragma once

#include "GameObject.h"
#include "Sprites.h"
#include "Textures.h"

class Candle : public GameObject
{
public:
	Candle() : GameObject() {}

	void LoadResources();
	void Render();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {}
};

