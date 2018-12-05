#pragma once

#include "GameObject.h"
#include "Bubbles.h"

class FishMan : public GameObject
{
	DWORD respawnTime_Start = 0;
	bool isRespawnWaiting = false;
	bool isAbleToShoot = false; // random để biết fishman có khả năng bắn hay không
	
	DWORD startTime = 0; // thời gian xuất hiện
	DWORD deltaTimeToShoot = 0; // khoảng thời gian kể từ lúc fishman xuất hiện đến lúc bắn 

	// Hiệu ứng bọt nước
	bool isNeedToCreateBubbles = false;
	bool isRenderingBubbles = false;
	DWORD startTimeRenderBubbles = 0;
	Bubbles * bubbles;

public:
	FishMan();
	~FishMan();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *Objects = NULL, vector<LPGAMEOBJECT>* coObject = NULL);
	void Render();
	void SetState(int state);

	void StartRespawnTimeCounter() { isRespawnWaiting = true; respawnTime_Start = GetTickCount(); }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom);

	void SetIsRespawnWaiting(bool x) { isRespawnWaiting = x; }
	bool IsRespawnWaiting() { return isRespawnWaiting; }

	bool IsAbleToActivate();

	bool IsAbleToShoot() { return isAbleToShoot; }
	void SetIsAbleToShoot(bool x) { isAbleToShoot = x; }

	int GetStartTime() { return startTime; }
	int GetDeltaTimeToShoot() { return deltaTimeToShoot; }

	void SetIsNeedToCreateBubbles(bool x) { isNeedToCreateBubbles = x; }
};

