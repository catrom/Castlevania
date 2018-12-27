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


SubWeapon::~SubWeapon()
{
}

void SubWeapon::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_WEAPONS_STOP_WATCH, FILEPATH_TEX_WEAPONS_STOP_WATCH, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_WEAPONS_DAGGER, FILEPATH_TEX_WEAPONS_DAGGER, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_WEAPONS_AXE, FILEPATH_TEX_WEAPONS_AXE, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_WEAPONS_HOLY_WATER, FILEPATH_TEX_WEAPONS_HOLY_WATER, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_WEAPONS_BOOMERANG, FILEPATH_TEX_WEAPONS_BOOMERANG, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 tex;

	tex = textures->Get(ID_TEX_WEAPONS_AXE);
	sprites->Add("weapon_axe_1", 0, 0, 30, 28, tex);
	sprites->Add("weapon_axe_2", 30, 0, 60, 28, tex);
	sprites->Add("weapon_axe_3", 60, 0, 90, 28, tex);
	sprites->Add("weapon_axe_4", 90, 0, 120, 28, tex);

	tex = textures->Get(ID_TEX_WEAPONS_HOLY_WATER);
	sprites->Add("weapon_holywater", 0, 0, 32, 26, tex);
	sprites->Add("weapon_holywatershattered_1", 32, 0, 64, 26, tex);
	sprites->Add("weapon_holywatershattered_2", 64, 0, 96, 26, tex);

	tex = textures->Get(ID_TEX_WEAPONS_BOOMERANG);
	sprites->Add("weapon_boomerang_1", 0, 0, 28, 28, tex);
	sprites->Add("weapon_boomerang_2", 28, 0, 56, 28, tex);
	sprites->Add("weapon_boomerang_3", 56, 0, 84, 28, tex);

	tex = textures->Get(ID_TEX_WEAPONS_DAGGER);
	sprites->Add("weapon_dagger", 0, 0, 32, 18, tex);

	tex = textures->Get(ID_TEX_WEAPONS_STOP_WATCH);
	sprites->Add("weapon_stopwatch", 0, 0, 26, 28, tex);

	LPANIMATION ani;

	ani = new Animation();
	ani->Add("weapon_stopwatch");
	animations->Add("weapon_stopwatch_ani", ani);

	ani = new Animation();
	ani->Add("weapon_dagger");
	animations->Add("weapon_dagger_ani", ani);

	ani = new Animation();
	ani->Add("weapon_axe_1");
	ani->Add("weapon_axe_2");
	ani->Add("weapon_axe_3");
	ani->Add("weapon_axe_4");
	animations->Add("weapon_axe_ani", ani);

	ani = new Animation();
	ani->Add("weapon_holywater");
	animations->Add("weapon_holywater_ani", ani);

	ani = new Animation();
	ani->Add("weapon_holywatershattered_1");
	ani->Add("weapon_holywatershattered_2");
	animations->Add("weapon_holywatershattered_ani", ani);

	ani = new Animation();
	ani->Add("weapon_boomerang_1");
	ani->Add("weapon_boomerang_2");
	ani->Add("weapon_boomerang_3");
	animations->Add("weapon_boomerang_ani", ani);
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

void SubWeapon::GetActiveBoundingBox(float & left, float & top, float & right, float & bottom)
{
	GetBoundingBox(left, top, right, bottom);
}

void SubWeapon::GetCoordinateObject(LPGAMEOBJECT obj)
{
	float l, t, r, b;
	obj->GetBoundingBox(l, t, r, b);

	sparkCoord.push_back({ l, t });
}


