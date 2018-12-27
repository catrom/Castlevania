#pragma once

#include "GameObject.h"

class Enemy : public GameObject
{
protected:
	int HP;
	int score;
	int attack;

	DWORD respawnTime_Start;
	bool isRespawnWaiting;
	int respawnWaitingTime;

	D3DXVECTOR2 entryPosition; // đưa enemy về vị trí entry sau thời gian respawn

public:
	bool isSettedPosition;

	Enemy();
	~Enemy();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);
	virtual void Render() = 0;
	virtual void SetState(int state);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom) = 0;

	virtual void LoseHP(int x);

	void StartRespawnTimeCounter();
	bool IsAbleToActivate();

	void SetEntryPosition(float x, float y) { entryPosition.x = x; entryPosition.y = y; }
	D3DXVECTOR2 GetEntryPosition() { return entryPosition; }

	int GetHP() { return HP; }
	int GetScore() { return score; }
	int GetAttack() { return attack; }
};

