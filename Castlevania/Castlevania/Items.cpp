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
	AddAnimation("item_invisibilitypotion_ani");
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
		right = left + 30;
		bottom = top + 32;
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
		right = left + 32;
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
		right = left + 26;
		bottom = top + 32;
		break;
	default:
		right = left;
		bottom = top;
		break;
	}
}