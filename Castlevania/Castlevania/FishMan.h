#pragma once

#include "GameObject.h"
#include "Bubbles.h"

class FishMan : public GameObject
{
	DWORD respawnTime_Start = 0;
	bool isRespawnWaiting = false;
	
	DWORD lastTimeShoot = 0; // thời gian kể từ lúc vừa bắn xong đến lần bắn tiếp theo
	DWORD deltaTimeToShoot = 0; // khoảng thời gian kể từ lúc fishman xuất hiện đến lúc bắn 

	int nxAfterShoot = 0; // Hướng quay mặt sau khi bắn (để luôn quay mặt về phía Simon)

	// Hiệu ứng bọt nước
	bool isNeedToCreateBubbles = false;
	bool isRenderingBubbles = false;
	DWORD startTimeRenderBubbles = 0;
	Bubbles * bubbles;

public:
	FishMan();
	~FishMan();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *Objects = NULL, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);
	void Render();
	void SetState(int state);

	void StartRespawnTimeCounter() { isRespawnWaiting = true; respawnTime_Start = GetTickCount(); }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom);

	void SetIsRespawnWaiting(bool x) { isRespawnWaiting = x; }
	bool IsRespawnWaiting() { return isRespawnWaiting; }

	bool IsAbleToActivate();

	int GetLastTimeShoot() { return lastTimeShoot; }
	int GetDeltaTimeToShoot() { return deltaTimeToShoot; }

	void SetIsNeedToCreateBubbles(bool x) { isNeedToCreateBubbles = x; }
	void SetNxAfterShoot(int x) { nxAfterShoot = x; }

	bool IsRenderingBubbles() { return isRenderingBubbles; }
};

