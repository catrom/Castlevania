#include "Enemy.h"



Enemy::Enemy()
{
	respawnTime_Start = 0;
	isRespawnWaiting = false;
	respawnWaitingTime = 0;
	isSettedPosition = false;
}

Enemy::~Enemy()
{
}

void Enemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	GameObject::Update(dt);
}

void Enemy::SetState(int state)
{
	GameObject::SetState(state);
}

void Enemy::StartRespawnTimeCounter()
{
	isRespawnWaiting = true; 
	respawnTime_Start = GetTickCount();
}

bool Enemy::IsAbleToActivate()
{
	DWORD now = GetTickCount();

	if (isRespawnWaiting == true && now - respawnTime_Start >= respawnWaitingTime)
		return true;

	return false;
}

void Enemy::LoseHP(int x)
{
	HP -= x;

	if (HP <= 0)
		HP = 0;
}
