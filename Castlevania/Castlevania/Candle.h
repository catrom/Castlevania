#pragma once

#include "GameObject.h"
#include "Sprites.h"
#include "Textures.h"
#include "Effect.h"
#include "Items.h"

class Candle : public GameObject
{
public:
	Candle();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *Objects = NULL, vector<LPGAMEOBJECT*>* coObject = NULL);
	void Render();
	

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

