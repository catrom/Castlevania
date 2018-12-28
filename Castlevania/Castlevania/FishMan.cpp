#include "FishMan.h"
#include "Ground.h"
#include "Water.h"
#include "BreakWall.h"


FishMan::FishMan() : Enemy()
{
	AddAnimation("fishman_walk_ani");
	AddAnimation("effect1_ani");
	AddAnimation("");
	AddAnimation("fishman_jump_ani");
	AddAnimation("fishman_hit_ani");

	lastTimeShoot = 0; 
	deltaTimeToShoot = 0; 
	nxAfterShoot = 0;

	HP = 1;
	score = 300;
	attack = 2 + rand() % 3;
	respawnWaitingTime = 3000;
}

void FishMan::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	// Update fishman
	if (state == FISHMAN_DESTROYED && animations[state]->IsOver(EFFECT_ANI_TIME_DELAY) == true)
	{
		SetState(FISHMAN_INACTIVE);
		return;
	}
	
	if (stopMovement == true)
		return;

	if (state == FISHMAN_HIT && animations[state]->IsOver(FISHMAN_HIT_ANI_TIME_DELAY) == true)
	{
		nx = nxAfterShoot;
		SetState(FISHMAN_ACTIVE);
		return;
	}
	
	if (state == FISHMAN_INACTIVE)
		return;

	Enemy::Update(dt);
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

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Ground*>(e->obj) || dynamic_cast<BreakWall*>(e->obj))
			{
				if (e->ny != 0)
				{
					if (e->ny == CDIR_BOTTOM)
					{
						vy = 0;

						if (state == FISHMAN_JUMP) // jump xong chạm đất -> walk
							SetState(FISHMAN_ACTIVE);
					}
					else
						y += dy;
				}
			}
			else if (dynamic_cast<Water*>(e->obj))
			{
				if (e->ny == CDIR_BOTTOM)
				{
					Water * water = dynamic_cast<Water*>(e->obj);
					water->AddBubbles(x, y + FISHMAN_BBOX_HEIGHT);

					SetState(FISHMAN_INACTIVE);
				}
			}
		}
		
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void FishMan::Render()
{
	// render fishman
	if (state != FISHMAN_INACTIVE)
		animations[state]->Render(1, nx, x, y);
}

void FishMan::SetState(int state)
{
	Enemy::SetState(state);

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
		respawnTime_Start = 0;
		isRespawnWaiting = false;
		break;
	case FISHMAN_DESTROYED:
		vx = vy = 0;
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case FISHMAN_INACTIVE:
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

void FishMan::LoseHP(int x)
{
	Enemy::LoseHP(x);

	if (HP == 0)
		SetState(FISHMAN_DESTROYED);
}

