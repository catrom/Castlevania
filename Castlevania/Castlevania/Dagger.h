#pragma once

#include "GameObject.h"
#include "Sprites.h"
#include "Textures.h"
#include "Ground.h"


class Dagger : public GameObject
{
public:
	Dagger();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations) {};
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *Objects = NULL, vector<LPGAMEOBJECT*>* coObject = NULL);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

