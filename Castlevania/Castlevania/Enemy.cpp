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

void Enemy::RenderActiveBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = Textures::GetInstance()->Get(ID_TEX_BBOX_2);

	float l, t, r, b;

	GetActiveBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	Game::GetInstance()->Draw(1, 0, l, t, bbox, 0, 0, rect.right, rect.bottom, 50);
}

void Enemy::LoseHP(int x)
{
	HP -= x;

	if (HP <= 0)
		HP = 0;
}
