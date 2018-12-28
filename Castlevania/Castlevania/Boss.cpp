#include "Boss.h"

Boss::Boss() : Enemy()
{
	AddAnimation("boss_fly_ani");
	AddAnimation("effect2_ani");
	AddAnimation("boss_idle_ani");

	isFlyToTarget = false;
	isFlyToSimon = false;

	idTarget = 0;

	startTimeWaiting = 0;
	isStopWaiting = false;

	dropItem = false;

	HP = 2;
	score = 3000;
	attack = 3;
}

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	if (state == BOSS_DESTROYED)
	{
		if (animations[state]->IsOver(EFFECT_2_ANI_TIME_DELAY) == true)
			dropItem = true;

		return;
	}

	if (isStopWaiting == true)
	{
		if (GetTickCount() - startTimeWaiting > BOSS_STOP_TIME_WAITING)
		{
			vx = vy = 0;
			isStopWaiting = false;
			startTimeWaiting = 0;
		}
		else
			return;
	}

	if (isFlyToTarget == false)
	{
		isFlyToTarget = true;

		// deternmind target
		if (idTarget == 1)
		{
			isFlyToSimon = true;
			target = simonPostion;
		}
		else 
		{
			target = GetRandomSpot();
		}

		// get velocity
		GetVelocity();
	}
	else
	{
		FlyToTarget(dt);
	}
}

void Boss::Render()
{
	animations[state]->Render(1, nx, x, y);
}

void Boss::SetState(int state)
{
	Enemy::SetState(state);

	switch (state)
	{
	case BOSS_ACTIVE:
		break;
	case BOSS_DESTROYED:
		vx = 0;
		vy = 0;
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case BOSS_INACTIVE:
		x = entryPosition.x;
		y = entryPosition.y;
		vx = 0;
		vy = 0;
		break;
	default:
		break;
	}
}

D3DXVECTOR2 Boss::GetRandomSpot()
{
	D3DXVECTOR2 randomSpot;

	float left = entryPosition.x - BOSS_RECT_RANDOMSPOT_BBOX_WIDTH;
	float top = entryPosition.y;

	float distance = 0;

	do // chọn điểm random sao cho quãng đường bay dài dài một tí
	{
		randomSpot.x = left + rand() % (2 * BOSS_RECT_RANDOMSPOT_BBOX_WIDTH);
		randomSpot.y = top + rand() % (BOSS_RECT_RANDOMSPOT_BBOX_HEIGHT);

		float dx = abs(x - randomSpot.x);
		float dy = abs(y - randomSpot.y);

		distance = sqrt(pow(x - randomSpot.x, 2) + pow(y - randomSpot.y, 2));
	} while (distance < 100.0f);

	return randomSpot;
}

void Boss::FlyToTarget(DWORD dt)
{
	x += vx*dt;
	y += vy*dt;

	if (abs(x - target.x) <= 1.0f)
	{
		isFlyToTarget = false;
		this->SetPosition(target.x, target.y);

		idTarget = (idTarget + 1) % 3;

		if (isFlyToSimon == true)
		{
			isFlyToSimon = false;
		}
		else
		{
			StartStopTimeCounter();
		}
	}
}

void Boss::GetVelocity()
{
	float dx = abs(x - target.x);
	float dy = abs(y - target.y);

	// lấy phương hướng
	int nx, ny;

	if (x < target.x) nx = 1;
	else nx = -1;

	if (y < target.y) ny = 1;
	else ny = -1;

	// tính vận tốc
	if (isFlyToSimon == true)
	{
		vx = nx * dx / BOSS_FAST_TIME_TO_FLY;
		vy = ny * dy / BOSS_FAST_TIME_TO_FLY;
	}
	else
	{
		vx = nx * dx / BOSS_DEFAULT_TIME_TO_FLY;
		vy = ny * dy / BOSS_DEFAULT_TIME_TO_FLY;
	}
}

void Boss::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + 13; // 70, 96
	top = y;
	right = left + BOSS_BBOX_WIDTH;
	bottom = top + BOSS_BBOX_HEIGHT;
}

void Boss::GetActiveBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = entryPosition.x + 120;
	right = left + BOSS_ACTIVE_BBOX_WIDTH;
	top = entryPosition.y;
	bottom = entryPosition.y + BOSS_ACTIVE_BBOX_HEIGHT;
}

void Boss::LoseHP(int x)
{
	Enemy::LoseHP(x);

	if (HP == 0)
		SetState(BOSS_DESTROYED);
}

