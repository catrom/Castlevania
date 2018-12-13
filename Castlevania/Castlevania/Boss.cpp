#include "Boss.h"



Boss::Boss()
{
	AddAnimation(BOSS_ACTIVE_ANI);
	AddAnimation(EFFECT_2_ANI);
	AddAnimation(BOSS_INACTIVE_ANI);
	AddAnimation(EFFECT_ANI);

	SetState(BOSS_INACTIVE);
}

Boss::~Boss()
{
}

void Boss::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_BOSS, FILEPATH_TEX_BOSS, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texBoss = textures->Get(ID_TEX_BOSS);

	sprites->Add(160001, 0, 0, 96, 46, texBoss);
	sprites->Add(160002, 96, 0, 192, 46, texBoss);
	sprites->Add(160003, 192, 0, 288, 46, texBoss);

	LPANIMATION ani;

	ani = new Animation(200);
	ani->Add(160002);
	ani->Add(160003);
	animations->Add(BOSS_ACTIVE_ANI, ani);

	ani = new Animation();
	ani->Add(160001);
	animations->Add(BOSS_INACTIVE_ANI, ani);
}

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	if (state == BOSS_DESTROYED)
	{
		if (animations[state]->IsOver(1000) == true)
		{
			dropItem = true;
		}

		return;
	}

	if (state == BOSS_HURT && animations[state]->IsOver(50) == true)
	{
		SetState(BOSS_ACTIVE);
	}

	if (isStopWaiting == true)
	{
		if (GetTickCount() - startTimeWaiting > BOSS_STOP_TIME_WAITING)
		{
			isStopWaiting = false;
			startTimeWaiting = 0;
		}
		else
		{
			return;
		}
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
	GameObject::SetState(state);

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
		vx = 0;
		vy = 0;
		break;
	case BOSS_HURT:
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
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

		if (max(dx, dy) / min(dx, dy) > 1.5) 
			continue;

		distance = sqrt(pow(x - randomSpot.x, 2) + pow(y - randomSpot.y, 2));
	} while (distance < 100.0f);

	return randomSpot;
}

void Boss::FlyToTarget(DWORD dt)
{
	x += vx*dt;
	y += vy*dt;

	if (abs(x - target.x) <= 2.0f)
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
	vx = BOSS_DEFAULT_VELOCITY;
	vy = BOSS_DEFAULT_VELOCITY * (dy / dx);
	
	vx *= nx;
	vy *= ny;
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
	left = entryPosition.x + 100;
	right = left + BOSS_ACTIVE_BBOX_WIDTH;
	top = entryPosition.y;
	bottom = entryPosition.y + BOSS_ACTIVE_BBOX_HEIGHT;
}

void Boss::LoseHP(int x)
{
	HP -= x;
	if (HP <= 0) {
		HP = 0;
		SetState(BOSS_DESTROYED);
	}
}

