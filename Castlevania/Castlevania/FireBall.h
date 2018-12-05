#pragma once

#include "GameObject.h"

class FireBall : public GameObject
{
public:
	FireBall();
	~FireBall();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *Objects = NULL, vector<LPGAMEOBJECT>* coObject = NULL);
	void Render();

	void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

