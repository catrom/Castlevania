#include "BlackLeopard.h"

BlackLeopard::BlackLeopard() : Enemy()
{
	AddAnimation("leopard_run_ani");
	AddAnimation("effect1_ani");
	AddAnimation("");
	AddAnimation("leopard_idle_ani");
	AddAnimation("leopard_jump_ani");

	isJumping = false;
	HP = 1;
	score = 200;
	attack = 2;
	respawnWaitingTime = 20000;
}

void BlackLeopard::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_BLACK_LEOPARD, FILEPATH_TEX_BLACK_LEOPARD, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texLeopard = textures->Get(ID_TEX_BLACK_LEOPARD);

	sprites->Add("leopard_idle", 0, 0, 64, 32, texLeopard);

	sprites->Add("leopard_run_1", 64, 0, 128, 32, texLeopard);
	sprites->Add("leopard_run_2", 128, 0, 192, 32, texLeopard);
	sprites->Add("leopard_run_3", 192, 0, 256, 32, texLeopard);
	sprites->Add("leopard_run_4", 128, 0, 192, 32, texLeopard);
	
	sprites->Add("leopard_jump", 192, 0, 256, 32, texLeopard);

	LPANIMATION ani;

	ani = new Animation(200);
	ani->Add("leopard_run_1");
	ani->Add("leopard_run_2");
	ani->Add("leopard_run_3");
	ani->Add("leopard_run_4");
	animations->Add("leopard_run_ani", ani);

	ani = new Animation(200);
	ani->Add("leopard_idle");
	animations->Add("leopard_idle_ani", ani);

	ani = new Animation(200);
	ani->Add("leopard_jump");
	animations->Add("leopard_jump_ani", ani);
}

void BlackLeopard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	DWORD now = GetTickCount();

	if (state == BLACK_LEOPARD_DESTROYED && animations[state]->IsOver(EFFECT_ANI_TIME_DELAY) == true)
	{
		SetState(BLACK_LEOPARD_INACTIVE);
		return;
	}

	if (stopMovement == true)
		return;

	vy += BLACK_LEOPARD_GRAVITY*dt;
	Enemy::Update(dt);
	

	// Check collision between zombie and ground (jumping on ground)
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObject, coEvents);

	//DebugOut(L"%d ", coEvents.size());

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;

		if (state == BLACK_LEOPARD_ACTIVE && isJumping == false) // không va chạm với ground và chưa nhảy -> nhảy
		{
			isJumping = true;
			SetState(BLACK_LEOPARD_JUMP);
		}
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += dx;
		y += min_ty*dy + ny*0.1f;

		if (ny == -1)
		{
			vy = 0;

			if (state == BLACK_LEOPARD_JUMP)
			{
				(this->nx) *= -1;
				SetState(BLACK_LEOPARD_ACTIVE);
			}
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void BlackLeopard::Render()
{
	if (state != BLACK_LEOPARD_INACTIVE)
		animations[state]->Render(1, nx, x, y);
}

void BlackLeopard::SetState(int state)
{
	Enemy::SetState(state);

	switch (state)
	{
	case BLACK_LEOPARD_ACTIVE:
		if (nx > 0) vx = BLACK_LEOPARD_RUNNING_SPEED_X;
		else vx = -BLACK_LEOPARD_RUNNING_SPEED_X;
		vy = BLACK_LEOPARD_RUNNING_SPEED_Y;
		isJumping = false;
		break;
	case BLACK_LEOPARD_DESTROYED:
		vx = 0;
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case BLACK_LEOPARD_INACTIVE:
		x = entryPosition.x;
		y = entryPosition.y;
		vx = 0;
		vy = 0;
		StartRespawnTimeCounter();
		break;
	case BLACK_LEOPARD_IDLE:
		vx = 0;
		respawnTime_Start = 0;
		isRespawnWaiting = false;
		isDroppedItem = false;
		break;
	case BLACK_LEOPARD_JUMP:
		vy = -BLACK_LEOPARD_RUNNING_SPEED_Y;
	default:
		break;
	}
}

void BlackLeopard::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + 27;  // (10/64)
	top = y;
	right = left + BLACK_LEOPARD_BBOX_WIDTH;
	bottom = top + BLACK_LEOPARD_BBOX_HEIGHT;
}

void BlackLeopard::GetActiveBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = entryPosition.x - BLACK_LEOPARD_ACTIVE_BBOX_WIDTH;
	right = entryPosition.x + BLACK_LEOPARD_ACTIVE_BBOX_WIDTH;
	top = entryPosition.y - BLACK_LEOPARD_ACTIVE_BBOX_HEIGHT;
	bottom = entryPosition.y + BLACK_LEOPARD_ACTIVE_BBOX_HEIGHT;
}

void BlackLeopard::LoseHP(int x)
{
	Enemy::LoseHP(x);

	if (HP == 0)
		SetState(BLACK_LEOPARD_DESTROYED);
}


