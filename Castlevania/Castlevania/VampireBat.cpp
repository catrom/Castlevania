#include "VampireBat.h"



VampireBat::VampireBat()
{
	AddAnimation(VAMPIRE_BAT_ANI);
	AddAnimation(EFFECT_ANI);

	nx = 1;
}

VampireBat::~VampireBat()
{
}

void VampireBat::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_VAMPIRE_BAT, FILEPATH_TEX_VAMPIRE_BAT, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texBat = textures->Get(ID_TEX_VAMPIRE_BAT);

	sprites->Add(140001, 0, 0, 32, 32, texBat);
	sprites->Add(140002, 32, 0, 64, 32, texBat);
	sprites->Add(140003, 64, 0, 96, 32, texBat);
	sprites->Add(140004, 96, 0, 128, 32, texBat);


	LPANIMATION ani;

	ani = new Animation(150);
	ani->Add(140003);
	ani->Add(140002);
	ani->Add(140003);
	ani->Add(140004);
	animations->Add(VAMPIRE_BAT_ANI, ani);
}

void VampireBat::Update(DWORD dt, vector<LPGAMEOBJECT>* Objects, vector<LPGAMEOBJECT>* coObject)
{
	GameObject::Update(dt);

	vy += velocityVariation;

	if (vy >= VAMPIRE_BAT_FLYING_SPEED_Y || vy <= -VAMPIRE_BAT_FLYING_SPEED_Y)
		velocityVariation *= -1;

	x += dx;
	y += dy;
}

void VampireBat::Render()
{
	animations[state]->Render(1, nx, x, y);
}

void VampireBat::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case VAMPIRE_BAT_ACTIVE:
		x = entryPosition.x;
		y = entryPosition.y;
		if (nx > 0) vx = VAMPIRE_BAT_FLYING_SPEED_X;
		else vx = -VAMPIRE_BAT_FLYING_SPEED_X;
		vy = 0;
		isDroppedItem = false;
		respawnTime_Start = 0;
		isRespawnWaiting = false;
		break;
	case VAMPIRE_BAT_DESTROYED:
		vx = 0;
		break;
	case VAMPIRE_BAT_INACTIVE:
		vx = 0;
		StartRespawnTimeCounter();
		break;
	default:
		break;
	}
}

void VampireBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + 11; // 10,32
	top = y;
	right = left + VAMPIRE_BAT_BBOX_WIDTH;
	bottom = top + VAMPIRE_BAT_BBOX_HEIGHT;
}

void VampireBat::GetActiveBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + VAMPIRE_BAT_ACTIVE_BBOX_WIDTH;
	bottom = top + VAMPIRE_BAT_ACTIVE_BBOX_HEIGHT;
}

bool VampireBat::IsAbleToActivate()
{
	DWORD now = GetTickCount();

	if (isRespawnWaiting == true && now - respawnTime_Start >= VAMPIRE_BAT_RESPAWN_TIME)
		return true;

	return false;
}
