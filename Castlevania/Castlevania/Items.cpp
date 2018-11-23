#include "Items.h"


Items::Items() : GameObject()
{
	vy = ITEM_FALLING_SPEED;

	AddAnimation(LARGE_HEART_ANI);
	AddAnimation(CHAIN_ANI);
	AddAnimation(DAGGER_ANI);

	timeAppear = -1;
}

void Items::LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations)
{
	textures->Add(ID_TEX_ITEM_LARGE_HEART, FILEPATH_TEX_ITEM_LARGE_HEART, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ITEM_CHAIN, FILEPATH_TEX_ITEM_CHAIN, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ITEM_DAGGER, FILEPATH_TEX_ITEM_DAGGER, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texLargeHeart = textures->Get(ID_TEX_ITEM_LARGE_HEART);
	LPDIRECT3DTEXTURE9 texChain = textures->Get(ID_TEX_ITEM_CHAIN);
	LPDIRECT3DTEXTURE9 texDagger = textures->Get(ID_TEX_ITEM_DAGGER);

	sprites->Add(60001, 0, 0, 24, 20, texLargeHeart);
	sprites->Add(70001, 0, 0, 32, 32, texChain);
	sprites->Add(80001, 0, 0, 32, 18, texDagger);
	


	LPANIMATION ani;

	ani = new Animation();  // large heart
	ani->Add(60001);
	animations->Add(LARGE_HEART_ANI, ani);

	ani = new Animation();	// chain
	ani->Add(70001);
	animations->Add(CHAIN_ANI, ani);
		
	ani = new Animation();  // dagger
	ani->Add(80001);
	animations->Add(DAGGER_ANI, ani);
}

void Items::Render()
{
	animations[state]->Render(1, -1, x, y);
}

void Items::Update(DWORD dt, vector<LPGAMEOBJECT> *Objects, vector<LPGAMEOBJECT>* coObject)
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
	case LARGE_HEART: // large heart
		right = left + LARGE_HEART_BBOX_WIDTH;
		bottom = top + LARGE_HEART_BBOX_HEIGHT;
		break;
	case CHAIN: // chain
		right = left + CHAIN_BBOX_WIDTH;
		bottom = top + CHAIN_BBOX_HEIGHT;
		break;
	case DAGGER: // dagger
		right = left + DAGGER_BBOX_WIDTH;
		bottom = top + DAGGER_BBOX_HEIGHT;
		break;
	default:
		break;
	}
}
