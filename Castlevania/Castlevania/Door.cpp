#include "Door.h"



Door::Door() : GameObject()
{
	AddAnimation("door1_ani");
	AddAnimation("door2_idle_ani");
	AddAnimation("door2_open_ani");
}


Door::~Door()
{
}

void Door::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_DOOR, FILEPATH_TEX_DOOR, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_GATE, FILEPATH_TEX_GATE, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texDoor = textures->Get(ID_TEX_DOOR);

	sprites->Add("door1", 0, 0, 96, 288, texDoor);

	LPANIMATION ani;

	ani = new Animation();
	ani->Add("door1");
	animations->Add("door1_ani", ani);


	LPDIRECT3DTEXTURE9 texGate = textures->Get(ID_TEX_GATE);

	sprites->Add("door2_idle", 0, 0, 48, 96, texGate);

	sprites->Add("door2_open_1", 0, 0, 48, 96, texGate);
	sprites->Add("door2_open_2", 48, 0, 96, 96, texGate);
	sprites->Add("door2_open_3", 96, 0, 144, 96, texGate);
	sprites->Add("door2_open_4", 144, 0, 192, 96, texGate);
	sprites->Add("door2_open_5", 0, 0, 48, 96, texGate);

	ani = new Animation(700);
	ani->Add("door2_idle");
	animations->Add("door2_idle_ani", ani);

	ani = new Animation(700);
	ani->Add("door2_open_1");
	ani->Add("door2_open_2");
	ani->Add("door2_open_3", 2000);
	ani->Add("door2_open_4");
	ani->Add("door2_open_5", 1000);
	animations->Add("door2_open_ani", ani);

}

void Door::Render()
{
	if (state == DOOR_2_OPEN && animations[state]->IsOver(DOOR_2_OPEN_ANI_TIME_DELAY) == true)
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
