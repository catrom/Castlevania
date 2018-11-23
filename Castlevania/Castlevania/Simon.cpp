#include "Simon.h"

Simon::Simon() : GameObject()
{
	SetState(STAND);

	AddAnimation(STAND_ANI);
	AddAnimation(WALK_ANI);
	AddAnimation(SIT_ANI);
	AddAnimation(JUMP_ANI);
	AddAnimation(HIT_SIT_ANI);
	AddAnimation(HIT_STAND_ANI);
	AddAnimation(HIT_STAND_ANI);
	AddAnimation(POWER_ANI);

	whip = new Whip();
	dagger = new Dagger();
}

void Simon::LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations)
{
	textures->Add(ID_TEX_SIMON, FILEPATH_TEX_SIMON, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);

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

	sprites->Add(10061, 120, 198, 180, 264, texSimon); // power up
	sprites->Add(10062, 60, 198, 120, 264, texSimon); 
	sprites->Add(10063, 0, 198, 60, 264, texSimon);


	LPANIMATION ani;

	ani = new Animation();
	ani->Add(10001);
	animations->Add(STAND_ANI, ani);

	ani = new Animation();
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	animations->Add(WALK_ANI, ani);

	ani = new Animation();
	ani->Add(10021);
	animations->Add(SIT_ANI, ani);

	ani = new Animation();
	ani->Add(10031);
	animations->Add(JUMP_ANI, ani);

	ani = new Animation();
	ani->Add(10041);
	ani->Add(10042);
	ani->Add(10043);
	animations->Add(HIT_SIT_ANI, ani);

	ani = new Animation();
	ani->Add(10051);
	ani->Add(10052);
	ani->Add(10053);
	animations->Add(HIT_STAND_ANI, ani);

	ani = new Animation(50);
	ani->Add(10061);
	ani->Add(10062);
	ani->Add(10063);
	animations->Add(POWER_ANI, ani);
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *Objects, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	if (vy < -0.1f || vy > 0.1f)
		vy += SIMON_GRAVITY*dt;
	else vy += SIMON_GRAVITY_LOWER*dt;


	// simple collision with border map
	if (x < 0) x = 0;
	//if (x >= 1476) x = 1476;


	// Check collision between Simon and other objects
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx*dx + nx*0.1f;
		y += min_ty*dy + ny*0.1f;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			// collision of Simon and Candle -> do nothing -> update x, y;
			if (dynamic_cast<Candle*>(e->obj))
			{
				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;
			}
			else if (dynamic_cast<Ground*>(e->obj))
			{
				if (ny != 0) vy = 0;
			}
			else if (dynamic_cast<Items*>(e->obj))
			{
				e->obj->isEnable = false;
				
				if (e->obj->GetState() == DAGGER)
					isPowered = true;		// phóng dao

				if (e->obj->GetState() == CHAIN)  // nếu item nhận được là chain
				{
					SetState(POWER);			// đổi trạng thái power - biến hình nhấp nháy các kiểu đà điểu
					vx = 0;

					// lên đời whip
					if (whip->GetState() == NORMAL_WHIP) whip->SetState(SHORT_CHAIN);
					else if (whip->GetState() == SHORT_CHAIN) whip->SetState(LONG_CHAIN);
				}
			}
			else
			{
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) 
			delete coEvents[i];


	// Check collision when fighting
	if (state == HIT_SIT || state == HIT_STAND)
	{
		// lấy vị trí của simon để set vị trí cho roi

		whip->SetOrientation(nx);
		whip->SetWhipPosition(D3DXVECTOR3(x, y, 0), isStand);


		//DebugOut(L"current: %d\n", animations[state]->GetCurrentFrame());

		if (animations[state]->GetCurrentFrame() == animations[state]->GetFramesSize() - 1) // chỉ xét va chạm khi render tới sprite cuối cùng của roi
		{
			for (UINT i = 0; i < coObjects->size(); i++)
			{
				LPGAMEOBJECT obj = coObjects->at(i);
				if (dynamic_cast<Candle*>(obj))
				{
					Candle * e = dynamic_cast<Candle*> (obj);

					float left, top, right, bottom;

					e->GetBoundingBox(left, top, right, bottom);

					//DebugOut(L"%f %f %f %f\n", left, top, right, bottom);


					if (whip->CheckCollision(left, top, right, bottom) == true) // va chạm giữa roi và nến
					{
						DebugOut(L"collision\n");

						e->SetState(DESTROYED);
						e->animations[DESTROYED]->SetAniStartTime(GetTickCount());
					}
				}
			}
		}
	}
}

void Simon::Render()
{
	animations[state]->Render(nx, x, y);

	if (state == HIT_SIT || state == HIT_STAND) 
	{
		whip->Render(animations[state]->GetCurrentFrame());
	}

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
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case HIT_STAND:
	case HIT:
	case POWER:
		isStand = true;
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
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
	right = left + SIMON_BBOX_WIDTH;
	bottom = top + SIMON_BBOX_HEIGHT;
}





