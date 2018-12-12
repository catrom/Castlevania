#include "Items.h"


Items::Items() : GameObject()
{
	vy = ITEM_FALLING_SPEED;

	AddAnimation(STOP_WATCH_ANI);
	AddAnimation(DAGGER_ANI);
	AddAnimation(AXE_ANI);
	AddAnimation(HOLY_WATER_ANI);
	AddAnimation(BOOMERANG_ANI);
	AddAnimation(SMALL_HEART_ANI);
	AddAnimation(LARGE_HEART_ANI);
	AddAnimation(CROSS_ANI);
	AddAnimation(INVISIBILITY_POTION_ANI);
	AddAnimation(CHAIN_ANI);
	AddAnimation(MONEY_BAG_RED_ANI);
	AddAnimation(MONEY_BAG_BLUE_ANI);
	AddAnimation(MONEY_BAG_WHITE_ANI);
	AddAnimation(MONEY_BAG_FLASHING_ANI);
	AddAnimation(DOUBLE_SHOT_ANI);
	AddAnimation(TRIPLE_SHOT_ANI);
	AddAnimation(PORK_CHOP_ANI);
	AddAnimation(MAGIC_CRYSTAL_ANI);

	timeAppear = -1;
}

void Items::LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations)
{
	textures->Add(ID_TEX_ITEM_STOP_WATCH, FILEPATH_TEX_ITEM_STOP_WATCH, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ITEM_DAGGER, FILEPATH_TEX_ITEM_DAGGER, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ITEM_AXE, FILEPATH_TEX_ITEM_AXE, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ITEM_HOLY_WATER, FILEPATH_TEX_ITEM_HOLY_WATER, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ITEM_BOOMERANG, FILEPATH_TEX_ITEM_BOOMERANG, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ITEM_SMALL_HEART, FILEPATH_TEX_ITEM_SMALL_HEART, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ITEM_LARGE_HEART, FILEPATH_TEX_ITEM_LARGE_HEART, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ITEM_CROSS, FILEPATH_TEX_ITEM_CROSS, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ITEM_INVISIBILITY_POTION, FILEPATH_TEX_ITEM_INVISIBILITY_POTION, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ITEM_CHAIN, FILEPATH_TEX_ITEM_CHAIN, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ITEM_MONEY_BAG, FILEPATH_TEX_ITEM_MONEY_BAG, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ITEM_DOUBLE_SHOT, FILEPATH_TEX_ITEM_DOUBLE_SHOT, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ITEM_TRIPLE_SHOT, FILEPATH_TEX_ITEM_TRIPLE_SHOT, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ITEM_PORK_CHOP, FILEPATH_TEX_ITEM_PORK_CHOP, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ITEM_MAGIC_CRYSTAL, FILEPATH_TEX_ITEM_MAGIC_CRYSTAL, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 tex;

	tex = textures->Get(ID_TEX_ITEM_STOP_WATCH);
	sprites->Add(80001, 0, 0, 26, 28, tex);

	tex = textures->Get(ID_TEX_ITEM_DAGGER);
	sprites->Add(80002, 0, 0, 32, 18, tex);

	tex = textures->Get(ID_TEX_ITEM_AXE);
	sprites->Add(80003, 0, 0, 30, 28, tex);

	tex = textures->Get(ID_TEX_ITEM_HOLY_WATER);
	sprites->Add(80004, 0, 0, 28, 28, tex);

	tex = textures->Get(ID_TEX_ITEM_BOOMERANG);
	sprites->Add(80005, 0, 0, 30, 28, tex);

	tex = textures->Get(ID_TEX_ITEM_SMALL_HEART);
	sprites->Add(80006, 0, 0, 16, 16, tex);

	tex = textures->Get(ID_TEX_ITEM_LARGE_HEART);
	sprites->Add(80007, 0, 0, 24, 20, tex);

	tex = textures->Get(ID_TEX_ITEM_CROSS);
	sprites->Add(80008, 0, 0, 32, 32, tex);

	tex = textures->Get(ID_TEX_ITEM_INVISIBILITY_POTION);
	sprites->Add(80009, 0, 0, 29, 36, tex);

	tex = textures->Get(ID_TEX_ITEM_CHAIN);
	sprites->Add(80010, 0, 0, 32, 32, tex);

	tex = textures->Get(ID_TEX_ITEM_MONEY_BAG);
	sprites->Add(80011, 0, 0, 30, 30, tex); //	red -- 100 point
	sprites->Add(80012, 60, 0, 90, 30, tex); //	blue -- 400 
	sprites->Add(80013, 30, 0, 60, 30, tex); //	white -- 700

	tex = textures->Get(ID_TEX_ITEM_DOUBLE_SHOT);
	sprites->Add(80014, 0, 0, 28, 28, tex);

	tex = textures->Get(ID_TEX_ITEM_TRIPLE_SHOT);
	sprites->Add(80015, 0, 0, 28, 28, tex);

	tex = textures->Get(ID_TEX_ITEM_PORK_CHOP);
	sprites->Add(80016, 0, 0, 32, 26, tex);

	tex = textures->Get(ID_TEX_ITEM_MAGIC_CRYSTAL);
	sprites->Add(80017, 0, 0, 28, 32, tex); 
	sprites->Add(80018, 28, 0, 56, 32, tex);
	


	LPANIMATION ani;

	ani = new Animation();  
	ani->Add(80001);
	animations->Add(STOP_WATCH_ANI, ani);

	ani = new Animation();
	ani->Add(80002);
	animations->Add(DAGGER_ANI, ani);

	ani = new Animation();
	ani->Add(80003);
	animations->Add(AXE_ANI, ani);

	ani = new Animation();
	ani->Add(80004);
	animations->Add(HOLY_WATER_ANI, ani);

	ani = new Animation();
	ani->Add(80005);
	animations->Add(BOOMERANG_ANI, ani);

	ani = new Animation();
	ani->Add(80006);
	animations->Add(SMALL_HEART_ANI, ani);

	ani = new Animation();
	ani->Add(80007);
	animations->Add(LARGE_HEART_ANI, ani);

	ani = new Animation();
	ani->Add(80008);
	animations->Add(CROSS_ANI, ani);

	ani = new Animation();
	ani->Add(80009);
	animations->Add(INVISIBILITY_POTION_ANI, ani);

	ani = new Animation();
	ani->Add(80010);
	animations->Add(CHAIN_ANI, ani);

	ani = new Animation();
	ani->Add(80011);
	animations->Add(MONEY_BAG_RED_ANI, ani);

	ani = new Animation();
	ani->Add(80012);
	animations->Add(MONEY_BAG_BLUE_ANI, ani);

	ani = new Animation();
	ani->Add(80013);
	animations->Add(MONEY_BAG_WHITE_ANI, ani);

	ani = new Animation(50);
	ani->Add(80011);
	ani->Add(80012);
	ani->Add(80013);
	animations->Add(MONEY_BAG_FLASHING_ANI, ani);

	ani = new Animation();
	ani->Add(80014);
	animations->Add(DOUBLE_SHOT_ANI, ani);

	ani = new Animation();
	ani->Add(80015);
	animations->Add(TRIPLE_SHOT_ANI, ani);

	ani = new Animation();
	ani->Add(80016);
	animations->Add(PORK_CHOP_ANI, ani);

	ani = new Animation(50);
	ani->Add(80017);
	ani->Add(80018);
	animations->Add(MAGIC_CRYSTAL_ANI, ani);

}

void Items::Render()
{
	animations[state]->Render(1, -1, x, y);
}

void Items::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	if (state != MAGIC_CRYSTAL)
	{
		if (timeAppear == -1)
		{
			timeAppear = GetTickCount();
		}
		else
		{
			DWORD now = GetTickCount();

			if (now - timeAppear > ITEM_TIME_DESTROYED)
			{
				isEnable = false;
				return;
			}
		}
	}


	GameObject::Update(dt);

	// Check collision between item and ground (falling on ground)
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

		y += min_ty*dy + ny*0.1f;
		if (ny != 0) vy = 0;
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Items::SetItem(int idItem)
{
	state = idItem;
}

void Items::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	switch (state)
	{
	case STOP_WATCH:
		right = left + 26;
		bottom = top + 28;
		break;
	case DAGGER:
		right = left + 32;
		bottom = top + 18;
		break;
	case AXE:
		right = left + 30;
		bottom = top + 28;
		break;
	case HOLY_WATER:
		right = left + 28;
		bottom = top + 28;
		break;
	case BOOMERANG:
		right = left + 30;
		bottom = top + 28;
		break;
	case SMALL_HEART:
		right = left + 16;
		bottom = top + 16;
		break;
	case LARGE_HEART:
		right = left + 24;
		bottom = top + 20;
		break;
	case CROSS:
		right = left + 32;
		bottom = top + 32;
		break;
	case INVISIBILITY_POTION:
		right = left + 29;
		bottom = top + 36;
		break;
	case CHAIN:
		right = left + 32;
		bottom = top + 32;
		break;
	case MONEY_BAG_RED:
	case MONEY_BAG_BLUE:
	case MONEY_BAG_WHITE:
	case MONEY_BAG_FLASHING:
		right = left + 30;
		bottom = top + 30;
		break;
	case DOUBLE_SHOT:
	case TRIPLE_SHOT:
		right = left + 28;
		bottom = top + 28;
		break;
	case PORK_CHOP:
		right = left + 32;
		bottom = top + 26;
		break;
	case MAGIC_CRYSTAL:
		right = left + 28;
		bottom = top + 32;
		break;
	default:
		right = left;
		bottom = top;
		break;
	}
}

void Items::GetActiveBoundingBox(float & left, float & top, float & right, float & bottom)
{
	GetBoundingBox(left, top, right, bottom);
}
