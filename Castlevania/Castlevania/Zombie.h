#pragma once

#include "GameObject.h"
#include "Items.h"

class Zombie : public GameObject
{
public:
	Zombie();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *Objects = NULL, vector<LPGAMEOBJECT>* coObject = NULL);
	void Render();


	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

