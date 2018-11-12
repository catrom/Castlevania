#include "Whip.h"


void Whip::LoadResources()
{
	Textures * texture = Textures::GetInstance();

	texture->Add(ID_TEX_WHIP, FILEPATH_TEX_WHIP, D3DCOLOR_XRGB(255, 255, 255));

	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();

	LPDIRECT3DTEXTURE9 texWhip = texture->Get(ID_TEX_SIMON);

	sprites->Add(20001, 0, 0, 240, 66, texWhip); // normal whip
	sprites->Add(20002, 240, 0, 480, 66, texWhip);
	sprites->Add(20003, 480, 0, 720, 66, texWhip);


	LPANIMATION ani;

	ani = new Animation();
	ani->Add(20001, 150);
	ani->Add(20002, 150);
	ani->Add(20003, 200);
	animations->Add(NORMAL_WHIP, ani);

	AddAnimation(NORMAL_WHIP);

	SetPosition(100.0f, 300.0f);
}

void Whip::Update()
{
}

void Whip::Render()
{
	animations[state]->Render(isOverAnimation, nx, x, y);
}

void Whip::SetWhipPosition(D3DXVECTOR3 simonPositon, bool isStand)
{
	simonPositon.x -= 90.0f;
	if (isStand == false)
		simonPositon.y += 15.0f;

	SetPosition(simonPositon.x, simonPositon.y);
}


