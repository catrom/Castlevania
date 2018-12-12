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
	AddAnimation(WEAPONS_STOP_WATCH_ANI);
	AddAnimation(WEAPONS_DAGGER_ANI);
	AddAnimation(WEAPONS_AXE_ANI);
	AddAnimation(WEAPONS_HOLY_WATER_ANI);
	AddAnimation(WEAPONS_BOOMERANG_ANI);
	AddAnimation(WEAPONS_HOLY_WATER_SHATTERED_ANI);

	state = -1; // no subweapon
}


SubWeapon::~SubWeapon()
{
}

void SubWeapon::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	// no need to add StopWatch and Dagger again (get them from Items)
	textures->Add(ID_TEX_WEAPONS_AXE, FILEPATH_TEX_WEAPONS_AXE, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_WEAPONS_HOLY_WATER, FILEPATH_TEX_WEAPONS_HOLY_WATER, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_WEAPONS_BOOMERANG, FILEPATH_TEX_WEAPONS_BOOMERANG, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 tex;

	tex = textures->Get(ID_TEX_WEAPONS_AXE);
	sprites->Add(90001, 0, 0, 30, 28, tex);
	sprites->Add(90002, 30, 0, 60, 28, tex);
	sprites->Add(90003, 60, 0, 90, 28, tex);
	sprites->Add(90004, 90, 0, 120, 28, tex);

	tex = textures->Get(ID_TEX_WEAPONS_HOLY_WATER);
	sprites->Add(90011, 0, 0, 32, 26, tex);
	sprites->Add(90012, 32, 0, 64, 26, tex);
	sprites->Add(90013, 64, 0, 96, 26, tex);

	tex = textures->Get(ID_TEX_WEAPONS_BOOMERANG);
	sprites->Add(90021, 0, 0, 28, 28, tex);
	sprites->Add(90022, 28, 0, 56, 28, tex);
	sprites->Add(90023, 56, 0, 84, 28, tex);

	LPANIMATION ani;

	ani = new Animation();
	ani->Add(80001);		// ID from Items.cpp
	animations->Add(WEAPONS_STOP_WATCH_ANI, ani);

	ani = new Animation();
	ani->Add(80002);		// ID from Items.cpp
	animations->Add(WEAPONS_DAGGER_ANI, ani);

	ani = new Animation();
	ani->Add(90001);		
	ani->Add(90002);
	ani->Add(90003);
	ani->Add(90004);
	animations->Add(WEAPONS_AXE_ANI, ani);

	ani = new Animation();
	ani->Add(90011);
	animations->Add(WEAPONS_HOLY_WATER_ANI, ani);

	ani = new Animation();
	ani->Add(90012);
	ani->Add(90013);
	animations->Add(WEAPONS_HOLY_WATER_SHATTERED_ANI, ani);

	ani = new Animation();
	ani->Add(90021);
	ani->Add(90022);
	ani->Add(90023);
	animations->Add(WEAPONS_BOOMERANG_ANI, ani);
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

				if (state == WEAPONS_DAGGER || state == WEAPONS_AXE || state == WEAPONS_BOOMERANG)
					this->isEnable = false;
			}
			else if (dynamic_cast<FireBall*>(e->obj))
			{
				FireBall * fireball = dynamic_cast<FireBall*>(e->obj);
				fireball->SetEnable(false);

				if (state == WEAPONS_DAGGER || state == WEAPONS_AXE || state == WEAPONS_BOOMERANG)
					this->isEnable = false;
			}
			else if (dynamic_cast<Zombie*>(e->obj))
			{
				Zombie * zombie = dynamic_cast<Zombie*>(e->obj);
				zombie->SetState(ZOMBIE_DESTROYED);
				scoreReceived = SCORE_ZOMBIE;
				targetTypeHit = ZOMBIE;

				if (state == WEAPONS_DAGGER || state == WEAPONS_AXE || state == WEAPONS_BOOMERANG)
					this->isEnable = false;
			}
			else if (dynamic_cast<BlackLeopard*>(e->obj))
			{
				BlackLeopard * blackLeopard = dynamic_cast<BlackLeopard*>(e->obj);
				blackLeopard->SetState(BLACK_LEOPARD_DESTROYED);
				scoreReceived = SCORE_BLACK_LEOPARD;
				targetTypeHit = BLACK_LEOPARD;

				if (state == WEAPONS_DAGGER || state == WEAPONS_AXE || state == WEAPONS_BOOMERANG)
					this->isEnable = false;
			}
			else if (dynamic_cast<VampireBat*>(e->obj))
			{
				VampireBat * vampirebat = dynamic_cast<VampireBat*>(e->obj);
				vampirebat->SetState(VAMPIRE_BAT_DESTROYED);
				scoreReceived = SCORE_VAMPIRE_BAT;
				targetTypeHit = VAMPIRE_BAT;

				if (state == WEAPONS_DAGGER || state == WEAPONS_AXE || state == WEAPONS_BOOMERANG)
					this->isEnable = false;
			}
			else if (dynamic_cast<FishMan*>(e->obj))
			{
				FishMan * fishman = dynamic_cast<FishMan*>(e->obj);
				fishman->SetState(FISHMAN_DESTROYED);
				scoreReceived = SCORE_FISHMAN;
				targetTypeHit = FISHMAN;

				if (state == WEAPONS_DAGGER || state == WEAPONS_AXE || state == WEAPONS_BOOMERANG)
					this->isEnable = false;
			}
			else if (dynamic_cast<Boss*>(e->obj))
			{
				Boss * boss = dynamic_cast<Boss*>(e->obj);
				boss->LoseHP(2);
				targetTypeHit = BOSS;

				if (state == WEAPONS_DAGGER || state == WEAPONS_AXE || state == WEAPONS_BOOMERANG)
					this->isEnable = false;
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
	if (state != WEAPONS_STOP_WATCH)
		animations[state]->Render(1, nx, x, y);
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

void SubWeapon::GetActiveBoundingBox(float & left, float & top, float & right, float & bottom)
{
	GetBoundingBox(left, top, right, bottom);
}


