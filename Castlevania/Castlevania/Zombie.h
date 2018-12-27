#pragma once

#include "Enemy.h"

class Zombie : public Enemy
{
public:
	Zombie();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);
	virtual void Render();
	virtual void SetState(int state);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom);

	virtual void LoseHP(int x);
};

