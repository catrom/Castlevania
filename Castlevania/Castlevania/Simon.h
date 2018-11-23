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

	int score;
	int item;
	int energy;
	int life;
	int subWeapon;
	int HP;

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
	
	int GetEnergy() { return this->energy; }
	int GetLife() { return this->life; }
	int GetScore() { return this->score; }
	int GetItem() { return this->item; }
	int GetSubWeapon() { return this->subWeapon; }
	int GetHP() { return this->HP; }
};


