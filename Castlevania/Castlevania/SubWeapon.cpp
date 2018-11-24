#include "SubWeapon.h"



SubWeapon::SubWeapon()
{
	AddAnimation(WEAPONS_STOP_WATCH_ANI);
	AddAnimation(WEAPONS_DAGGER_ANI);
	AddAnimation(WEAPONS_AXE_ANI);
	AddAnimation(WEAPONS_HOLY_WATER_ANI);
	AddAnimation(WEAPONS_BOOMERANG_ANI);

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
	ani->Add(90012);
	ani->Add(90013);
	animations->Add(WEAPONS_HOLY_WATER_ANI, ani);

	ani = new Animation();
	ani->Add(90021);
	ani->Add(90022);
	ani->Add(90023);
	animations->Add(WEAPONS_BOOMERANG_ANI, ani);
}

void SubWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* Objects, vector<LPGAMEOBJECT>* coObject)
{
	GameObject::Update(dt);

	switch (state)
	{
	case AXE:
		vy += 0.02f;
		break;
	case HOLY_WATER:
		vy += 0.02f;
		break;
	case BOOMERANG:
		vx += (-nx * 0.01f);
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
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		if (state == HOLY_WATER && ny != 0)
		{
			SetEnable(false);
		}
		else if (state == AXE)
		{
			if (y > 350.0f) SetEnable(false);
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void SubWeapon::Render()
{
	if (state != STOP_WATCH)
		animations[state]->Render(1, nx, x, y);
}

void SubWeapon::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case STOP_WATCH:
		break;
	case DAGGER:
		vx = nx * WEAPONS_DAGGER_SPEED;
		vy = 0;
		break;
	case AXE:
		vx = nx * WEAPONS_AXE_SPEED_X;
		vy = -WEAPONS_AXE_SPEED_Y;
		break;
	case HOLY_WATER:
		vx = nx * WEAPONS_HOLY_WATER_SPEED_X;
		vy = -WEAPONS_HOLY_WATER_SPEED_Y;
		break;
	case BOOMERANG:
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
	case STOP_WATCH:
		right = left + 26;
		bottom = top + 28;
	case DAGGER:
		right = left + 32;
		bottom = top + 18;
	case AXE:
		right = left + 30;
		bottom = top + 28;
	case HOLY_WATER:
		right = left + 32;
		bottom = top + 32;
	case BOOMERANG:
		right = left + 30;
		bottom = top + 28;
	default:
		break;
	}
}


