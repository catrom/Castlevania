#pragma once

#include <vector>

#include "GameObject.h"
#include "Textures.h"
#include "Define.h"
#include "Whip.h"
#include "Candle.h"

using namespace std;

class Simon : public GameObject
{
	Whip* whip;

public:
	bool isStand = true; // xác định trạng thái để lấy vị trí gắn roi cho phù hợp

	Simon() : GameObject() {}

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	void SetState(int state);

	bool IsTouchGround() { return vy == 0; }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};


