#include "Whip.h"


Whip::Whip() : GameObject()
{
	AddAnimation(NORMAL_WHIP_ANI);
	AddAnimation(SHORT_CHAIN_ANI);
	AddAnimation(LONG_CHAIN_ANI);

	SetState(NORMAL_WHIP);
}

void Whip::LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations)
{
	textures->Add(ID_TEX_WHIP, FILEPATH_TEX_WHIP, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texWhip = textures->Get(ID_TEX_WHIP);

	sprites->Add(20001, 0, 0, 240, 66, texWhip); // normal whip
	sprites->Add(20002, 240, 0, 480, 66, texWhip);
	sprites->Add(20003, 480, 0, 720, 66, texWhip);

	sprites->Add(20011, 0, 66, 240, 132, texWhip); // short chain
	sprites->Add(20012, 240, 66, 480, 132, texWhip);
	sprites->Add(20013, 480, 66, 720, 132, texWhip);

	sprites->Add(20021, 0, 132, 240, 198, texWhip); // long chain
	sprites->Add(20022, 240, 132, 480, 198, texWhip);
	sprites->Add(20023, 480, 132, 720, 198, texWhip);
	sprites->Add(20024, 0, 198, 240, 264, texWhip);
	sprites->Add(20025, 240, 198, 480, 264, texWhip);
	sprites->Add(20026, 480, 198, 720, 264, texWhip);
	sprites->Add(20027, 0, 264, 240, 330, texWhip);
	sprites->Add(20028, 240, 264, 480, 330, texWhip);
	sprites->Add(20029, 480, 264, 720, 330, texWhip);
	sprites->Add(20030, 0, 330, 240, 396, texWhip);
	sprites->Add(20031, 240, 330, 480, 396, texWhip);
	sprites->Add(20032, 480, 330, 720, 396, texWhip);

	LPANIMATION ani;

	ani = new Animation();
	ani->Add(20001);
	ani->Add(20002);
	ani->Add(20003);
	animations->Add(NORMAL_WHIP_ANI, ani);

	ani = new Animation();
	ani->Add(20011);
	ani->Add(20012);
	ani->Add(20013);
	animations->Add(SHORT_CHAIN_ANI, ani);

	ani = new Animation(25);
	ani->Add(20021);
	ani->Add(20022);
	ani->Add(20023);
	ani->Add(20024);
	ani->Add(20025);
	ani->Add(20026);
	ani->Add(20027);
	ani->Add(20028);
	ani->Add(20029);
	ani->Add(20030);
	ani->Add(20031);
	ani->Add(20032);
	animations->Add(LONG_CHAIN_ANI, ani);
}

void Whip::Render(int currentID)
{
	animations[state]->RenderByID(currentID, nx, x, y);
}

void Whip::SetWhipPosition(D3DXVECTOR3 simonPositon, bool isStand)
{
	simonPositon.x -= 90.0f;
	if (isStand == false)
		simonPositon.y += 15.0f;

	SetPosition(simonPositon.x, simonPositon.y);
}

bool Whip::CheckCollision(float obj_left, float obj_top, float obj_right, float obj_bottom)
{
	float whip_left,
		whip_top,
		whip_right,
		whip_bottom;

	GetBoundingBox(whip_left, whip_top, whip_right, whip_bottom);

	return GameObject::AABB(whip_left, whip_top, whip_right, whip_bottom, obj_left, obj_top, obj_right, obj_bottom);
}

void Whip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	top = y + 15;
	bottom = top + WHIP_BBOX_HEIGHT;
	if (nx < 0)
	{
		if (state != LONG_CHAIN)
			left = x + 50;
		else left = x + 20;
	}
	else if (nx > 0)
	{
		if (state != LONG_CHAIN)
			left = (240 - 50) - WHIP_BBOX_WIDTH + x;
		else left = (240 - 20) - WHIP_BBOX_WIDTH + x;
	}

	right = left + WHIP_BBOX_WIDTH;
}


