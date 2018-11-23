#pragma once

#include <vector>

#include "GameObject.h"
#include "Textures.h"
#include "Define.h"
#include "Whip.h"
#include "Candle.h"
#include "Effect.h"
#include "Ground.h"
#include "Items.h"
#include "Dagger.h"

using namespace std;

class Simon : public GameObject
{
	Whip* whip;
	Dagger* dagger;

public:
	bool isStand = true; // xác định trạng thái đứng/ngồi để lấy vị trí gắn roi cho phù hợp
	bool isPowered = false; // lấy item, phóng item (up + fight key)

	Simon();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *Objects = NULL, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int state);

	bool IsTouchGround() { return vy == 0; }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};


