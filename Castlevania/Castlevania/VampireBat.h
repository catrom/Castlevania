#pragma once

#include "GameObject.h"

class VampireBat : public GameObject
{
	DWORD respawnTime_Start = 0;
	bool isRespawnWaiting = false;
	float velocityVariation = VAMPIRE_BAT_SPEED_VARIATION;
	bool isSettedPosition = false;

public:
	VampireBat();
	~VampireBat();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *Objects = NULL, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);
	void Render();
	void SetState(int state);

	void StartRespawnTimeCounter() { isRespawnWaiting = true; respawnTime_Start = GetTickCount(); }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom);

	bool IsRespawnWaiting() { return isRespawnWaiting; }
	void SetIsRespawnWaiting(bool x) { isRespawnWaiting = x; }

	bool IsSettedPosition() { return isSettedPosition; }
	void SetIsSettedPosition(bool x) { isSettedPosition = x; }

	bool IsAbleToActivate();

	DWORD get() { return this->respawnTime_Start; }
};

