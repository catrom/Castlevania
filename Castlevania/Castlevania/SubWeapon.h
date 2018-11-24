#pragma once

#include "GameObject.h"
#include "Textures.h"
#include "Define.h"

class SubWeapon  : public GameObject
{
public:
	SubWeapon();
	~SubWeapon();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *Objects = NULL, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();

	void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

