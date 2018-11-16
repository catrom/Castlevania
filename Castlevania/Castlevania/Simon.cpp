#include "Simon.h"

Simon::Simon() : GameObject()
{
	whip = new Whip();
	whip->AddAnimation(NORMAL_WHIP_ANI);
	whip->SetState(NORMAL_WHIP);
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

	ani = new Animation(150);
	ani->Add(10041);
	ani->Add(10042);
	ani->Add(10043);
	//ani->Add(10021);
	animations->Add(HIT_SIT_ANI, ani);

	ani = new Animation(150);
	ani->Add(10051);
	ani->Add(10052);
	ani->Add(10053);
	//ani->Add(10001);
	animations->Add(HIT_STAND_ANI, ani);
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT*>* coObjects)
{
	GameObject::Update(dt);

	vy += SIMON_GRAVITY*dt;


	// simple collision with border map
	if (x < 0) x = 0;
	if (x >= 1476) x = 1476;


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
				x += dx;
				y += min_ty*dy + ny*0.4f;

				if (ny != 0) vy = 0;
			}
			else if (dynamic_cast<Items*>(e->obj))
			{
				// will add more case for item type
				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;

				
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
		D3DXVECTOR3 simonPositon;
		GetPosition(simonPositon.x, simonPositon.y);

		whip->SetOrientation(nx);
		whip->SetWhipPosition(simonPositon, isStand);


		//DebugOut(L"current: %d\n", animations[state]->GetCurrentFrame());

		if (animations[state]->GetCurrentFrame() == animations[state]->GetFramesSize() - 1) // chỉ xét va chạm khi render tới sprite cuối cùng của roi
		{
			for (UINT i = 0; i < coObjects->size(); i++)
			{
				LPGAMEOBJECT * obj = coObjects->at(i);
				if (dynamic_cast<Candle*>(*obj))
				{
					Candle * e = dynamic_cast<Candle*> (*obj);

					float left, top, right, bottom;

					e->GetBoundingBox(left, top, right, bottom);

					//DebugOut(L"%f %f %f %f\n", left, top, right, bottom);


					if (whip->CheckCollision(left, top, right, bottom) == true) // va chạm giữa roi và nến
					{
						DebugOut(L"collision\n");

						//e->DestroyedEffect();
						
						
						// Tạo một random item và thay thế vào vị trí con trỏ của Candle*
			
						item = new Items();
						item->SetPosition(e->x, e->y);
						item->GetRandomItem();

						*(obj) = item;

					}
				}
			}
		}
	}
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
		animations[state]->Reset();
		animations[state]->setAniStartTime(GetTickCount());
		break;
	case HIT_STAND:
		isStand = true;
		animations[state]->Reset();
		animations[state]->setAniStartTime(GetTickCount());
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





