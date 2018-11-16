#pragma once

#include "GameObject.h"
#include "Sprites.h"
#include "Textures.h"
#include "Ground.h"

class Items : public GameObject
{
public:
	Items();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT*>* coObject = NULL);

	void GetRandomItem();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

};

