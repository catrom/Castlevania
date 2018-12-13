#include "FishMan.h"



FishMan::FishMan()
{
	AddAnimation(FISHMAN_ACTIVE_ANI);
	AddAnimation(EFFECT_ANI);
	AddAnimation(FISHMAN_INACTIVE_ANI);
	AddAnimation(FISHMAN_JUMP_ANI);
	AddAnimation(FISHMAN_HIT_ANI);
}


FishMan::~FishMan()
{
}

void FishMan::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_FISHMAN, FILEPATH_TEX_FISHMAN, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texFishman = textures->Get(ID_TEX_FISHMAN);

	sprites->Add(150001, 0, 0, 32, 64, texFishman);
	sprites->Add(150002, 32, 0, 64, 64, texFishman);
	sprites->Add(150003, 64, 0, 96, 64, texFishman);

	LPANIMATION ani;

	ani = new Animation(200);
	ani->Add(150002);
	ani->Add(150003);
	animations->Add(FISHMAN_ACTIVE_ANI, ani);

	ani = new Animation(1000);
	ani->Add(150001);
	animations->Add(FISHMAN_HIT_ANI, ani);

	ani = new Animation();
	ani->Add(150003);
	animations->Add(FISHMAN_JUMP_ANI, ani);
}

void FishMan::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	// Update bubbles
	if (isRenderingBubbles == true && stopMovement == false)
	{
		DWORD now = GetTickCount();

		if (now - startTimeRenderBubbles <= 1000)
		{
			bubbles->Update(dt);
		}
		else
		{
			isRenderingBubbles = false;
			startTimeRenderBubbles = 0;
		}
	}

	// Update fishman
	if (state == FISHMAN_DESTROYED && animations[state]->IsOver(150) == true)
	{
		SetState(FISHMAN_INACTIVE);
		return;
	}
	
	if (stopMovement == true)
		return;

	if (state == FISHMAN_HIT && animations[state]->IsOver(1000) == true)
	{
		nx = nxAfterShoot;
		SetState(FISHMAN_ACTIVE);
		return;
	}
	
	if (state == FISHMAN_INACTIVE)
	{
		return;
	}

	GameObject::Update(dt);
	vy += FISHMAN_GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObject, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += dx;
		y += min_ty*dy + ny*0.1f;

		if (ny != 0)
		{
			if (ny == -1.0f)
			{
				vy = 0;
				
				if (state == FISHMAN_JUMP) // jump xong chạm đất -> walk
				{
					SetState(FISHMAN_ACTIVE);
				}
			}
			else
			{
				y += dy;
			}
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void FishMan::Render()
{
	// render bubbles
	if (isRenderingBubbles == true)
		bubbles->Render();

	// render fishman
	if (state != FISHMAN_INACTIVE)
		animations[state]->Render(1, nx, x, y);
}

void FishMan::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case FISHMAN_ACTIVE:
		if (nx > 0) vx = FISHMAN_WALKING_SPEED_X;
		else vx = -FISHMAN_WALKING_SPEED_X;
		lastTimeShoot = GetTickCount();
		deltaTimeToShoot = 500 + rand() % 2000; // Random trong khoảng thời gian là 0.5 - 2s
		break;
	case FISHMAN_JUMP:
		vx = 0;
		vy = -FISHMAN_JUMP_SPEED_Y;
		isDroppedItem = false;
		isNeedToCreateBubbles = false;
		respawnTime_Start = 0;
		isRespawnWaiting = false;
		bubbles = new Bubbles(x, y + 32);
		isRenderingBubbles = true;
		startTimeRenderBubbles = GetTickCount();
		break;
	case FISHMAN_DESTROYED:
		vx = vy = 0;
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case FISHMAN_INACTIVE:
		if (isNeedToCreateBubbles == true)
		{
			bubbles = new Bubbles(x, y + 32);
			isRenderingBubbles = true;
			startTimeRenderBubbles = GetTickCount();
		}
		x = entryPosition.x;
		y = entryPosition.y;
		vx = vy = 0;
		isSettedPosition = false;
		StartRespawnTimeCounter();
		break;
	case FISHMAN_HIT:
		vx = vy = 0;
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	default:
		break;
	}
}

void FishMan::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + 11; // 10,32
	top = y + 2;  // 60,64
	right = left + FISHMAN_BBOX_WIDTH;
	bottom = top + FISHMAN_BBOX_HEIGHT;
}

void FishMan::GetActiveBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = entryPosition.x - FISHMAN_ACTIVE_BBOX_WIDTH;
	right = entryPosition.x + FISHMAN_ACTIVE_BBOX_WIDTH;
	top = entryPosition.y - FISHMAN_ACTIVE_BBOX_HEIGHT;
	bottom = entryPosition.y;
}

bool FishMan::IsAbleToActivate()
{
	DWORD now = GetTickCount();

	if (isRespawnWaiting == true && now - respawnTime_Start >= FISHMAN_RESPAWN_TIME)
		return true;

	return false;
}

