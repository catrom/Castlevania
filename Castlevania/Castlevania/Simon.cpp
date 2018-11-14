#include "Simon.h"

void Simon::LoadResources()
{
	Textures * texture = Textures::GetInstance();

	texture->Add(ID_TEX_SIMON, FILEPATH_TEX_SIMON, D3DCOLOR_XRGB(255, 255, 255));

	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();

	LPDIRECT3DTEXTURE9 texSimon = texture->Get(ID_TEX_SIMON);

	sprites->Add(10001, 0, 0, 60, 66, texSimon); // stand

	sprites->Add(10011, 0, 0, 60, 66, texSimon); // walk
	sprites->Add(10012, 60, 0, 120, 66, texSimon);
	sprites->Add(10013, 120, 0, 180, 66, texSimon);
	sprites->Add(10014, 180, 0, 240, 66, texSimon);

	sprites->Add(10021, 300, 198, 360, 264, texSimon); // sit

	sprites->Add(10031, 240, 0, 300, 66, texSimon); // jump

	sprites->Add(10041, 420, 66, 480, 132, texSimon); // hit_sit
	sprites->Add(10042, 0, 132, 60, 198, texSimon);
	sprites->Add(10043, 60, 132, 120, 198, texSimon);

	sprites->Add(10051, 300, 0, 360, 66, texSimon); // hit_stand
	sprites->Add(10052, 360, 0, 420, 66, texSimon); 
	sprites->Add(10053, 420, 0, 480, 66, texSimon); 

	

	LPANIMATION ani;

	ani = new Animation();
	ani->Add(10001);
	animations->Add(STAND, ani);

	ani = new Animation();
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	animations->Add(WALK, ani);

	ani = new Animation();
	ani->Add(10021);
	animations->Add(SIT, ani);

	ani = new Animation();
	ani->Add(10031);
	animations->Add(JUMP, ani);

	ani = new Animation();
	ani->Add(10041, 150);
	ani->Add(10042, 150);
	ani->Add(10043, 200);
	animations->Add(HIT_SIT, ani);

	ani = new Animation();
	ani->Add(10051, 150);
	ani->Add(10052, 150);
	ani->Add(10053, 200);
	animations->Add(HIT_STAND, ani);

	AddAnimation(STAND);
	AddAnimation(WALK);
	AddAnimation(SIT);
	AddAnimation(JUMP);
	AddAnimation(HIT_SIT);
	AddAnimation(HIT_STAND);

	SetPosition(0.0f, 224.0f);

	whip = new Whip();
	whip->LoadResources();
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	GameObject::Update(dt);

	vy += SIMON_GRAVITY;
	if (y > 224)
	{
		vy = 0;
		y = 224.0f;
	}
}

void Simon::Render()
{
	if (state == HIT_SIT || state == HIT_STAND) {		// lấy vị trí của simon để thực hiện gắn roi
		D3DXVECTOR3 simonPositon;
		GetPosition(simonPositon.x, simonPositon.y);

		whip->SetOrientation(nx);
		whip->SetWhipPosition(simonPositon, isStand);
		whip->Render();
	}

	animations[state]->Render(nx, x, y);
}

void Simon::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case STAND:
		isStand = true;
		vx = 0;
		break;
	case WALK:
		if (nx > 0) vx = SIMON_WALKING_SPEED;
		else vx = -SIMON_WALKING_SPEED;
		break;
	case JUMP:
		isStand = true;
		if (y == 224)
			vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIT:
		isStand = false;
		vx = 0;
		vy = 0;
		break;
	case HIT_SIT:
		isStand = false;
		animations[HIT_SIT]->Reset();
		break;
	case HIT_STAND:
		isStand = true;
		animations[HIT_STAND]->Reset();
		break;
	default:
		break;
	}
}

bool Simon::IsStand()
{
	return this->y == 224.0f;
}

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + SIMON_BBOX_WIDTH;
	bottom = y + SIMON_BBOX_HEIGHT;
}





