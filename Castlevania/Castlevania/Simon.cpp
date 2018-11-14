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

	ani = new Animation(150);
	ani->Add(10041);
	ani->Add(10042);
	ani->Add(10043);
	ani->Add(10021);
	animations->Add(HIT_SIT, ani);

	ani = new Animation(150);
	ani->Add(10051);
	ani->Add(10052);
	ani->Add(10053);
	ani->Add(10001);
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
	
	/*if (y > 224)
	{
		vy = 0;
		y = 224.0f;
	}*/

	if (state == HIT_SIT || state == HIT_STAND) 
	{		
		D3DXVECTOR3 simonPositon;
		GetPosition(simonPositon.x, simonPositon.y);

		whip->SetOrientation(nx);
		whip->SetWhipPosition(simonPositon, isStand);
	}

	// Check collision when fighting
	if (state == HIT_SIT || state == HIT_STAND)
	{
		if (animations[state]->GetCurrentFrame() == animations[state]->GetFramesSize() - 2) // chỉ xét va chạm khi render tới sprite cuối cùng của roi
		{
			for (UINT i = 0; i < colliable_objects->size(); i++)
			{
				LPGAMEOBJECT e = colliable_objects->at(i);
				if (dynamic_cast<Candle *>(e))
				{
					float left, top, right, bottom;
					e->GetBoundingBox(left, top, right, bottom);

					DebugOut(L"%f %f %f %f\n", left, top, right, bottom);


					if (whip->CheckCollision(left, top, right, bottom) == true) // va chạm giữa roi và nến
					{
						DebugOut(L"collision\n");
						colliable_objects->erase(colliable_objects->begin() + i);
						i--;
					}
				}
			}
		}
	}

	// Check collision between Simon and other objects
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(colliable_objects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// ground
		x += min_tx*dx + nx*0.4f; 
		y += min_ty*dy + ny*0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			// collision of Simon and Candle -> do nothing -> update x;
			if (dynamic_cast<Candle *>(e->obj))
			{
				x -= nx*0.4f;
				
			}
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//for (int i = 0; i < coEventsResult.size(); i++) delete coEventsResult[i];
}

void Simon::Render()
{
	if (state == HIT_SIT || state == HIT_STAND) {		// lấy vị trí của simon để thực hiện gắn roi
		//D3DXVECTOR3 simonPositon;
		//GetPosition(simonPositon.x, simonPositon.y);

		//whip->SetOrientation(nx);
		//whip->SetWhipPosition(simonPositon, isStand);
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

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	// sprite có kích thước là 60x66, bbox là 40x62
	left = x + 10; 
	top = y + 2;
	right = x + SIMON_BBOX_WIDTH;
	bottom = y + SIMON_BBOX_HEIGHT;
}





