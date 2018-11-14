#pragma once

#include <vector>

#include "GameObject.h"
#include "Textures.h"
#include "Define.h"
#include "Whip.h"

using namespace std;

class Simon : public GameObject
{
	Whip* whip;

public:
	bool isStand = true;

	Simon() : GameObject() {}

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	void SetState(int state);

	

	bool IsStand();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};


