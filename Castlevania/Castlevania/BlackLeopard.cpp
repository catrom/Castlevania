#include "BlackLeopard.h"

BlackLeopard::BlackLeopard()
{
	AddAnimation(BLACK_LEOPARD_ACTIVE_ANI);
	AddAnimation(EFFECT_ANI);
	AddAnimation(BLACK_LEOPARD_INACTIVE_ANI);
	AddAnimation(BLACK_LEOPARD_IDLE_ANI);
	AddAnimation(BLACK_LEOPARD_JUMP_ANI);

	nx = -1;
}

void BlackLeopard::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_BLACK_LEOPARD, FILEPATH_TEX_BLACK_LEOPARD, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texLeopard = textures->Get(ID_TEX_BLACK_LEOPARD);

	sprites->Add(130001, 0, 0, 64, 32, texLeopard);
	sprites->Add(130002, 64, 0, 128, 32, texLeopard);
	sprites->Add(130003, 128, 0, 196, 32, texLeopard);
	sprites->Add(130004, 196, 0, 256, 32, texLeopard);

	LPANIMATION ani;

	ani = new Animation(200);
	ani->Add(130002);
	ani->Add(130003);
	ani->Add(130004);
	animations->Add(BLACK_LEOPARD_ACTIVE_ANI, ani);

	ani = new Animation(200);
	ani->Add(130001);
	animations->Add(BLACK_LEOPARD_IDLE_ANI, ani);

	ani = new Animation(200);
	ani->Add(130004);
	animations->Add(BLACK_LEOPARD_JUMP_ANI, ani);
}

void BlackLeopard::Update(DWORD dt, vector<LPGAMEOBJECT>* Objects, vector<LPGAMEOBJECT>* coObject)
{
	DWORD now = GetTickCount();

	if (state == BLACK_LEOPARD_DESTROYED && animations[state]->IsOver(150) == true)
	{
		SetState(BLACK_LEOPARD_INACTIVE);
		return;
	}

	vy += BLACK_LEOPARD_GRAVITY*dt;
	GameObject::Update(dt);
	

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

		if (ny != 0)
		{
			vy = 0;

			if (state == BLACK_LEOPARD_JUMP)
			{
				this->nx = 1;
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
	{
		if (isRespawnWaiting == false)
			animations[state]->Render(1, nx, x, y);
	}
}

void BlackLeopard::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case BLACK_LEOPARD_ACTIVE:
		if (nx > 0) vx = BLACK_LEOPARD_RUNNING_SPEED_X;
		else vx = -BLACK_LEOPARD_RUNNING_SPEED_X;
		vy = BLACK_LEOPARD_RUNNING_SPEED_Y;
		isDroppedItem = false;
		respawnTime_Start = 0;
		isRespawnWaiting = false;
		break;
	case BLACK_LEOPARD_DESTROYED:
		vx = 0;
		break;
	case BLACK_LEOPARD_INACTIVE:
		vx = 0;
		vy = 0;
		StartRespawnTimeCounter();
		break;
	case BLACK_LEOPARD_IDLE:
		vx = 0;
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

bool BlackLeopard::IsAbleToActivate()
{
	DWORD now = GetTickCount();

	if (isRespawnWaiting == true && now - respawnTime_Start >= BLACK_LEOPARD_RESPAWN_TIME)
		return true;

	return false;
}


