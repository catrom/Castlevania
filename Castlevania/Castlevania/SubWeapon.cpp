#include "SubWeapon.h"
#include "Candle.h"
#include "Zombie.h"
#include "BlackLeopard.h"
#include "VampireBat.h"
#include "FishMan.h"
#include "FireBall.h"
#include "Simon.h"
#include "Boss.h"
#include "Ground.h"

SubWeapon::SubWeapon()
{
	AddAnimation("weapon_stopwatch_ani");
	AddAnimation("weapon_dagger_ani");
	AddAnimation("weapon_axe_ani");
	AddAnimation("weapon_holywater_ani");
	AddAnimation("weapon_boomerang_ani");
	AddAnimation("weapon_holywatershattered_ani");

	state = -1; // no subweapon
}

void SubWeapon::UpdateCollisionState()
{
	if (state == WEAPONS_DAGGER || state == WEAPONS_BOOMERANG)
		this->isEnable = false;
	else
	{
		x += dx;
		y += dy;
	}
}

void SubWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	if (isHolyWaterShattered == true && 
		GetTickCount() - holyWaterShatteredCounter > WEAPONS_HOLY_WATER_TIME_EFFECT)
	{
		isHolyWaterShattered = false;
		holyWaterShatteredCounter = 0;
		this->isEnable = false;
		return;
	}

	GameObject::Update(dt);

	switch (state)
	{
	case WEAPONS_AXE:
		vy += WEAPONS_AXE_GRAVITY*dt;
		break;
	case WEAPONS_HOLY_WATER:
		vy += WEAPONS_HOLY_WATER_GRAVITY*dt;
		break;
	case WEAPONS_BOOMERANG:
		if (nx > 0) vx -= WEAPONS_BOOMERANG_TURNBACK_SPEED;
		else vx += WEAPONS_BOOMERANG_TURNBACK_SPEED;
		break;
	default:
		break;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObject, coEvents);

	static int  c = 0;

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		// kiểm tra va chạm với object
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Candle*>(e->obj))
			{
				Candle * candle = dynamic_cast<Candle*>(e->obj);
				candle->SetState(CANDLE_DESTROYED);

				targetTypeHit = CANDLE;
				GetCoordinateObject(e->obj);

				UpdateCollisionState();
			}
			else if (dynamic_cast<FireBall*>(e->obj))
			{
				FireBall * fireball = dynamic_cast<FireBall*>(e->obj);
				fireball->SetEnable(false);

				targetTypeHit = FIREBALL;
				GetCoordinateObject(e->obj);

				UpdateCollisionState();
			}
			else if (dynamic_cast<Zombie*>(e->obj))
			{
				Zombie * zombie = dynamic_cast<Zombie*>(e->obj);
				zombie->LoseHP(2);
				targetTypeHit = ZOMBIE;

				if (zombie->GetState() == ZOMBIE_DESTROYED)
				{
					scoreReceived += zombie->GetScore();
					GetCoordinateObject(e->obj);
				}

				UpdateCollisionState();
			}
			else if (dynamic_cast<BlackLeopard*>(e->obj))
			{
				BlackLeopard * blackLeopard = dynamic_cast<BlackLeopard*>(e->obj);
				blackLeopard->LoseHP(2);
				targetTypeHit = BLACK_LEOPARD;

				if (blackLeopard->GetState() == BLACK_LEOPARD_DESTROYED)
				{
					scoreReceived += blackLeopard->GetScore();
					GetCoordinateObject(e->obj);
				}
				
				UpdateCollisionState();
			}
			else if (dynamic_cast<VampireBat*>(e->obj))
			{
				VampireBat * vampirebat = dynamic_cast<VampireBat*>(e->obj);
				vampirebat->LoseHP(2);
				targetTypeHit = VAMPIRE_BAT;

				if (vampirebat->GetState() == VAMPIRE_BAT_DESTROYED)
				{
					scoreReceived += vampirebat->GetScore();
					GetCoordinateObject(e->obj);
				}

				UpdateCollisionState();
			}
			else if (dynamic_cast<FishMan*>(e->obj))
			{
				FishMan * fishman = dynamic_cast<FishMan*>(e->obj);
				fishman->LoseHP(2);
				targetTypeHit = FISHMAN;

				if (fishman->GetState() == FISHMAN_DESTROYED)
				{
					scoreReceived += fishman->GetScore();
					GetCoordinateObject(e->obj);
				}

				UpdateCollisionState();
			}
			else if (dynamic_cast<Boss*>(e->obj))
			{
				Boss * boss = dynamic_cast<Boss*>(e->obj);
				boss->LoseHP(2);
				targetTypeHit = BOSS;
				GetCoordinateObject(e->obj);

				if (boss->GetState() == BOSS_DESTROYED)
					scoreReceived += boss->GetScore();

				UpdateCollisionState();
			}
			else if (dynamic_cast<Ground*>(e->obj))
			{
				if (state == WEAPONS_HOLY_WATER && e->ny == -1)
					SetState(WEAPONS_HOLY_WATER_SHATTERED);

				x += dx;
				y += dy;
			}
			else if (dynamic_cast<Simon*>(e->obj))
			{
				if (state == WEAPONS_BOOMERANG)
					this->isEnable = false;
			}
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void SubWeapon::Render()
{
	RenderSpark();

	if (this->isEnable == true && state != WEAPONS_STOP_WATCH)
		animations[state]->Render(1, nx, x, y);
}

void SubWeapon::RenderSpark()
{
	if (sparkCoord.size() > 0)
	{
		if (startTimeRenderSpark == 0)
			startTimeRenderSpark = GetTickCount();
		else if (GetTickCount() - startTimeRenderSpark > SPARK_ANI_TIME_DELAY)
		{
			startTimeRenderSpark = 0;
			sparkCoord.clear();
		}

		for (auto coord : sparkCoord)
			spark->Render(1, -1, coord[0], coord[1]);
	}
}

void SubWeapon::SetState(int state)
{
	GameObject::SetState(state);

	scoreReceived = 0;
	targetTypeHit = -1;

	switch (state)
	{
	case WEAPONS_STOP_WATCH:
		break;
	case WEAPONS_DAGGER:
		if (nx > 0) vx = WEAPONS_DAGGER_SPEED;
		else vx = -WEAPONS_DAGGER_SPEED;
		vy = 0;
		break;
	case WEAPONS_AXE:
		if (nx > 0) vx = WEAPONS_AXE_SPEED_X;
		else vx = -WEAPONS_AXE_SPEED_X;
		vy = -WEAPONS_AXE_SPEED_Y;
		break;
	case WEAPONS_HOLY_WATER:
		vx = nx * WEAPONS_HOLY_WATER_SPEED_X;
		vy = -WEAPONS_HOLY_WATER_SPEED_Y;
		break;
	case WEAPONS_HOLY_WATER_SHATTERED:
		vx = 0;
		vy = 0;
		StartHolyWaterEffect();
		break;
	case WEAPONS_BOOMERANG:
		vx = nx * WEAPONS_BOOMERANG_SPEED;
		vy = 0;
		break;
	default:
		break;
	}
}

void SubWeapon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	switch (state)
	{
	case WEAPONS_STOP_WATCH:
		right = left;  // no need to get boundingbox
		bottom = top;
		break;
	case WEAPONS_DAGGER:
		right = left + WEAPONS_DAGGER_BBOX_WIDTH;
		bottom = top + WEAPONS_DAGGER_BBOX_HEIGHT;
		break;
	case WEAPONS_AXE:
		right = left + WEAPONS_AXE_BBOX_WIDTH;
		bottom = top + WEAPONS_AXE_BBOX_HEIGHT;
		break;
	case WEAPONS_HOLY_WATER:
		right = left + WEAPONS_HOLY_WATER_BBOX_WIDTH;
		bottom = top + WEAPONS_AXE_BBOX_HEIGHT;
		break;
	case WEAPONS_BOOMERANG:
		right = left + WEAPONS_BOOMERANG_BBOX_WIDTH;
		bottom = top + WEAPONS_BOOMERANG_BBOX_HEIGHT;
		break;
	default:
		right = left;
		bottom = top;
		break;
	}
}

void SubWeapon::GetCoordinateObject(LPGAMEOBJECT obj)
{
	float l, t, r, b;
	obj->GetBoundingBox(l, t, r, b);

	sparkCoord.push_back({ l, t });
}


