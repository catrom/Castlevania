#pragma once

#include <vector>
#include "GameObject.h"

class Boss : public GameObject
{
	int HP = BOSS_HP; 

	bool isFlyToTarget = false;
	bool isFlyToSimon = false;

	D3DXVECTOR2 simonPostion;
	D3DXVECTOR2 target;

	int idTarget = 0;		

	int startTimeWaiting = 0;
	bool isStopWaiting = false;

	bool dropItem = false;

public:
	Boss();
	~Boss();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);
	void Render();
	void SetState(int state);

	D3DXVECTOR2 GetRandomSpot();
	void FlyToTarget(DWORD dt);
	void GetVelocity();

	void StartStopTimeCounter() { isStopWaiting = true; startTimeWaiting = GetTickCount(); }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom);

	void SetSimonPosition(float sx, float sy) { simonPostion.x = sx; simonPostion.y = sy; }

	int GetIdTarget() { return idTarget; }

	bool DropItem() { return dropItem; }

	void LoseHP(int x);
	int GetHP() { return HP; }
};


