#include "Door.h"



Door::Door() : GameObject()
{
	AddAnimation(DOOR_1_ANI);
	AddAnimation(DOOR_2_IDLE_ANI);
	AddAnimation(DOOR_2_OPEN_ANI);
}


Door::~Door()
{
}

void Door::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_DOOR, FILEPATH_TEX_DOOR, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_GATE, FILEPATH_TEX_GATE, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texDoor = textures->Get(ID_TEX_DOOR);

	sprites->Add(110001, 0, 0, 96, 288, texDoor);

	LPANIMATION ani;

	ani = new Animation();
	ani->Add(110001);
	animations->Add(DOOR_1_ANI, ani);


	LPDIRECT3DTEXTURE9 texGate = textures->Get(ID_TEX_GATE);

	sprites->Add(110011, 0, 0, 48, 96, texGate);
	sprites->Add(110012, 48, 0, 96, 96, texGate);
	sprites->Add(110013, 96, 0, 144, 96, texGate);
	sprites->Add(110014, 144, 0, 192, 96, texGate);

	ani = new Animation(700);
	ani->Add(110011);
	animations->Add(DOOR_2_IDLE_ANI, ani);

	ani = new Animation(700);
	ani->Add(110011);
	ani->Add(110012);
	ani->Add(110013, 2000);
	ani->Add(110014);
	ani->Add(110011, 1000);
	animations->Add(DOOR_2_OPEN_ANI, ani);

}

void Door::Render()
{
	if (state == DOOR_2_OPEN && animations[state]->IsOver(5000) == true)
		state = DOOR_2_IDLE;

	animations[state]->Render(1, -1, x, y);
}

void Door::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	switch (state)
	{
	case DOOR_1:
		l = 1376;
		t = 272;
		r = l + DOOR_BBOX_WIDTH;
		b = t + DOOR_BBOX_HEIGHT;
		break;
	case DOOR_2_IDLE:
	case DOOR_2_OPEN:
		l = x - 16;
		t = y;
		r = l + DOOR_BBOX_WIDTH;
		b = t + DOOR_BBOX_HEIGHT;
		break;
	default:
		break;
	}
}

void Door::GetActiveBoundingBox(float & left, float & top, float & right, float & bottom)
{
	GetBoundingBox(left, top, right, bottom);
}
