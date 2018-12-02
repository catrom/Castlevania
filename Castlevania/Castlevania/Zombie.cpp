#include "Zombie.h"



Zombie::Zombie()
{
	AddAnimation(ZOMBIE_ANI);
	AddAnimation(EFFECT_ANI);

	SetState(ZOMBIE);

	nx = -1;
	vx = -ZOMBIE_WALKING_SPEED;
}

void Zombie::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_ZOMBIE, FILEPATH_TEX_ZOMBIE, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texZombie = textures->Get(ID_TEX_ZOMBIE);

	sprites->Add(120001, 0, 0, 32, 64, texZombie);
	sprites->Add(120002, 32, 0, 64, 64, texZombie);

	LPANIMATION ani;

	ani = new Animation(200);
	ani->Add(120001, 150);
	ani->Add(120002, 150);
	animations->Add(ZOMBIE_ANI, ani);
}

void Zombie::Update(DWORD dt, vector<LPGAMEOBJECT>* Objects, vector<LPGAMEOBJECT>* coObject)
{
	if (state == ZOMBIE_DESTROYED && animations[state]->IsOver(150)) 
	{
		this->isEnable = false;
		return;
	}

	GameObject::Update(dt);

	x += dx;

	if (x <= 0)
	{
		x = 0;
		vx = ZOMBIE_WALKING_SPEED;
		nx = 1;
	}
	else if (x >= 500)
	{
		x = 500;
		vx = -ZOMBIE_WALKING_SPEED;
		nx = -1;
	}
}

void Zombie::Render()
{
	animations[state]->Render(1, nx, x, y);
}

void Zombie::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + ZOMBIE_BBOX_WIDTH;
	bottom = top + ZOMBIE_BBOX_HEIGHT;
}


