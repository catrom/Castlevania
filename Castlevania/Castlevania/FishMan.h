#pragma once

#include "Enemy.h"

class FishMan : public Enemy
{
	DWORD lastTimeShoot; // thời gian kể từ lúc vừa bắn xong đến lần bắn tiếp theo
	DWORD deltaTimeToShoot; // khoảng thời gian kể từ lúc fishman xuất hiện đến lúc bắn 
	int nxAfterShoot; // Hướng quay mặt sau khi bắn (để luôn quay mặt về phía Simon)

public:
	FishMan();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);
	virtual void Render();
	virtual void SetState(int state);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom);

	virtual void LoseHP(int x);

	int GetLastTimeShoot() { return lastTimeShoot; }
	int GetDeltaTimeToShoot() { return deltaTimeToShoot; }

	void SetNxAfterShoot(int x) { nxAfterShoot = x; }
};

