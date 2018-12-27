#include "Items.h"


Items::Items() : GameObject()
{
	AddAnimation("item_stopwatch_ani");
	AddAnimation("item_dagger_ani");
	AddAnimation("item_axe_ani");
	AddAnimation("item_holywater_ani");
	AddAnimation("item_boomerang_ani");
	AddAnimation("item_smallheart_ani");
	AddAnimation("item_largeheart_ani");
	AddAnimation("item_cross_ani");
	AddAnimation("item_invisibilitypostion_ani");
	AddAnimation("item_chain_ani");
	AddAnimation("item_redmoneybag_ani");
	AddAnimation("item_bluemoneybag_ani");
	AddAnimation("item_whitemoneybag_ani");
	AddAnimation("item_flashingmoneybag_ani");
	AddAnimation("item_doubleshot_ani");
	AddAnimation("item_tripleshot_ani");
	AddAnimation("item_porkchop_ani");
	AddAnimation("item_magiccrystal_ani");

	timeAppear = -1;
	vy = ITEM_FALLING_SPEED;
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
	sprites->Add("item_stopwatch", 0, 0, 26, 28, tex);

	tex = textures->Get(ID_TEX_ITEM_DAGGER);
	sprites->Add("item_dagger", 0, 0, 32, 18, tex);

	tex = textures->Get(ID_TEX_ITEM_AXE);
	sprites->Add("item_axe", 0, 0, 30, 28, tex);

	tex = textures->Get(ID_TEX_ITEM_HOLY_WATER);
	sprites->Add("item_holywater", 0, 0, 28, 28, tex);

	tex = textures->Get(ID_TEX_ITEM_BOOMERANG);
	sprites->Add("item_boomerang", 0, 0, 30, 28, tex);

	tex = textures->Get(ID_TEX_ITEM_SMALL_HEART);
	sprites->Add("item_smallheart", 0, 0, 16, 16, tex);

	tex = textures->Get(ID_TEX_ITEM_LARGE_HEART);
	sprites->Add("item_largeheart", 0, 0, 24, 20, tex);

	tex = textures->Get(ID_TEX_ITEM_CROSS);
	sprites->Add("item_cross", 0, 0, 32, 32, tex);

	tex = textures->Get(ID_TEX_ITEM_INVISIBILITY_POTION);
	sprites->Add("item_invisibilitypostion", 0, 0, 29, 36, tex);

	tex = textures->Get(ID_TEX_ITEM_CHAIN);
	sprites->Add("item_chain", 0, 0, 32, 32, tex);

	tex = textures->Get(ID_TEX_ITEM_MONEY_BAG);
	sprites->Add("item_redmoneybag", 0, 0, 30, 30, tex); //	red -- 100 point
	sprites->Add("item_bluemoneybag", 60, 0, 90, 30, tex); //	blue -- 400 
	sprites->Add("item_whitemoneybag", 30, 0, 60, 30, tex); //	white -- 700

	tex = textures->Get(ID_TEX_ITEM_DOUBLE_SHOT);
	sprites->Add("item_doubleshot", 0, 0, 28, 28, tex);

	tex = textures->Get(ID_TEX_ITEM_TRIPLE_SHOT);
	sprites->Add("item_tripleshot", 0, 0, 28, 28, tex);

	tex = textures->Get(ID_TEX_ITEM_PORK_CHOP);
	sprites->Add("item_porkchop", 0, 0, 32, 26, tex);

	tex = textures->Get(ID_TEX_ITEM_MAGIC_CRYSTAL);
	sprites->Add("item_magiccrystal_1", 0, 0, 28, 32, tex); 
	sprites->Add("item_magiccrystal_2", 28, 0, 56, 32, tex);
	


	LPANIMATION ani;

	ani = new Animation();  
	ani->Add("item_stopwatch");
	animations->Add("item_stopwatch_ani", ani);

	ani = new Animation();
	ani->Add("item_dagger");
	animations->Add("item_dagger_ani", ani);

	ani = new Animation();
	ani->Add("item_axe");
	animations->Add("item_axe_ani", ani);

	ani = new Animation();
	ani->Add("item_holywater");
	animations->Add("item_holywater_ani", ani);

	ani = new Animation();
	ani->Add("item_boomerang");
	animations->Add("item_boomerang_ani", ani);

	ani = new Animation();
	ani->Add("item_smallheart");
	animations->Add("item_smallheart_ani", ani);

	ani = new Animation();
	ani->Add("item_largeheart");
	animations->Add("item_largeheart_ani", ani);

	ani = new Animation();
	ani->Add("item_cross");
	animations->Add("item_cross_ani", ani);

	ani = new Animation();
	ani->Add("item_invisibilitypostion");
	animations->Add("item_invisibilitypostion_ani", ani);

	ani = new Animation();
	ani->Add("item_chain");
	animations->Add("item_chain_ani", ani);

	ani = new Animation();
	ani->Add("item_redmoneybag");
	animations->Add("item_redmoneybag_ani", ani);

	ani = new Animation();
	ani->Add("item_bluemoneybag");
	animations->Add("item_bluemoneybag_ani", ani);

	ani = new Animation();
	ani->Add("item_whitemoneybag");
	animations->Add("item_whitemoneybag_ani", ani);

	ani = new Animation(50);
	ani->Add("item_redmoneybag");
	ani->Add("item_bluemoneybag");
	ani->Add("item_whitemoneybag");
	animations->Add("item_flashingmoneybag_ani", ani);

	ani = new Animation();
	ani->Add("item_doubleshot");
	animations->Add("item_doubleshot_ani", ani);

	ani = new Animation();
	ani->Add("item_tripleshot");
	animations->Add("item_tripleshot_ani", ani);

	ani = new Animation();
	ani->Add("item_porkchop");
	animations->Add("item_porkchop_ani", ani);

	ani = new Animation(50);
	ani->Add("item_magiccrystal_1");
	ani->Add("item_magiccrystal_2");
	animations->Add("item_magiccrystal_ani", ani);

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
