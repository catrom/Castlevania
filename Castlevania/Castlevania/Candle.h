#pragma once

#include "GameObject.h"
#include "Sprites.h"
#include "Textures.h"
#include "Effect.h"

class Candle : public GameObject
{
public:

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	void Render();

	void DestroyedEffect();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

