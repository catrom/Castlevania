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
	AddAnimation(STAIR_UP_ANI);
	AddAnimation(STAIR_DOWN_ANI);
	AddAnimation(HIT_STAIR_UP_ANI);
	AddAnimation(HIT_STAIR_DOWN_ANI);

	whip = new Whip();

	score = 0;
	item = -1;
	energy = 99;
	life = 3;
	subWeapon = BOOMERANG;
	HP = 10;
}

void Simon::LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations)
{
	textures->Add(ID_TEX_SIMON, FILEPATH_TEX_SIMON, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);

	sprites->Add(10001, 0, 0, 60, 64, texSimon); // stand

	sprites->Add(10011, 0, 0, 60, 64, texSimon); // walk
	sprites->Add(10012, 60, 0, 120, 64, texSimon);
	sprites->Add(10013, 120, 0, 180, 64, texSimon);
	sprites->Add(10014, 180, 0, 240, 64, texSimon);

	sprites->Add(10021, 300, 198, 360, 262, texSimon); // sit

	sprites->Add(10031, 240, 0, 300, 64, texSimon); // jump

	sprites->Add(10041, 420, 66, 480, 130, texSimon); // hit_sit
	sprites->Add(10042, 0, 132, 60, 196, texSimon);
	sprites->Add(10043, 60, 132, 120, 196, texSimon);

	sprites->Add(10051, 300, 0, 360, 64, texSimon); // hit_stand
	sprites->Add(10052, 360, 0, 420, 64, texSimon);
	sprites->Add(10053, 420, 0, 480, 64, texSimon);

	sprites->Add(10061, 120, 198, 180, 262, texSimon); // power up
	sprites->Add(10062, 60, 198, 120, 262, texSimon);
	sprites->Add(10063, 0, 198, 60, 262, texSimon);

	sprites->Add(10071, 240, 66, 300, 130, texSimon); // stair up
	sprites->Add(10072, 300, 66, 360, 130, texSimon);

	sprites->Add(10081, 120, 66, 180, 130, texSimon); // stair down
	sprites->Add(10082, 180, 66, 240, 130, texSimon);

	sprites->Add(10091, 300, 132, 360, 196, texSimon); // hit - stair up
	sprites->Add(10092, 360, 132, 420, 196, texSimon);
	sprites->Add(10093, 420, 132, 480, 196, texSimon);

	sprites->Add(10101, 120, 132, 180, 196, texSimon); // hit - stair down
	sprites->Add(10102, 180, 132, 240, 196, texSimon);
	sprites->Add(10103, 240, 132, 300, 196, texSimon);

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

	ani = new Animation();
	ani->Add(10071);
	ani->Add(10072);
	animations->Add(STAIR_UP_ANI, ani);

	ani = new Animation();
	ani->Add(10081);
	ani->Add(10082);
	animations->Add(STAIR_DOWN_ANI, ani);

	ani = new Animation();
	ani->Add(10091);
	ani->Add(10092);
	ani->Add(10093);
	animations->Add(HIT_STAIR_UP_ANI, ani);

	ani = new Animation();
	ani->Add(10101);
	ani->Add(10102);
	ani->Add(10103);
	animations->Add(HIT_STAIR_DOWN_ANI, ani);
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *Objects, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	if (state != STAIR_UP && state != STAIR_DOWN)
	{
		if (vy < -0.1f || vy > 0.1f)
			vy += SIMON_GRAVITY*dt;
		else vy += SIMON_GRAVITY_LOWER*dt;

	}
	



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
				if (ny != 0)
				{
					vy = 0;
					isTouchGround = true;
				}
				
				if (nx != 0 && state == STAIR_UP)
				{
					x -= nx*0.1f;
				}

				if (state == STAIR_DOWN)
				{
					state = STAND;
				}

				DebugOut(L"collision\n");
			}
			else if (dynamic_cast<Items*>(e->obj))
			{
				e->obj->isEnable = false;

				int idItem = e->obj->GetState();

				switch (idItem)
				{
				case STOP_WATCH:
				case DAGGER:
				case AXE:
				case HOLY_WATER:
				case BOOMERANG:
					subWeapon = idItem;
					break;
				case SMALL_HEART:
					energy += 1;
					break;
				case LARGE_HEART:
					energy += 5;
					break;
				case CROSS:
					break;
				case INVISIBILITY_POTION:
					break;
				case CHAIN:
					SetState(POWER); // đổi trạng thái power - biến hình nhấp nháy các kiểu đà điểu
					vx = 0;
					// lên đời whip
					if (whip->GetState() == NORMAL_WHIP) whip->SetState(SHORT_CHAIN);
					else if (whip->GetState() == SHORT_CHAIN) whip->SetState(LONG_CHAIN);
					break;
				case MONEY_BAG_RED:
					score += 100;
					break;
				case MONEY_BAG_BLUE:
					score += 400;
					break;
				case MONEY_BAG_WHITE:
					score += 700;
					break;
				case MONEY_BAG_FLASHING:
					score += 1000;
					break;
				case DOUBLE_SHOT:
				case TRIPLE_SHOT:
					item = idItem;
					break;
				case PORK_CHOP:
					HP += 2;
					break;
				case MAGIC_CRYSTAL:
					HP = 16;
					break;
				default:
					break;
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
	animations[state]->Render(1, nx, x, y);

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
		isMovingDown = false;
		isMovingUp = false;
		isStandOnStair = false;
		isStand = true;
		vx = 0;
		break;
	case WALK:
		isStandOnStair = false;
		if (nx > 0) vx = SIMON_WALKING_SPEED;
		else vx = -SIMON_WALKING_SPEED;
		break;
	case JUMP:
		isTouchGround = false;
		isStandOnStair = false;
		isStand = true;
		vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIT:
		isStandOnStair = false;
		isStand = false;
		vx = 0;
		vy = 0;
		break;
	case HIT_SIT:
		isStandOnStair = false;
		isStand = false;
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case HIT_STAND:
	case HIT:
	case POWER:
		isStandOnStair = false;
		isStand = true;
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case STAIR_UP:
		isTouchGround = false;
		isStand = true;
		if (nx > 0) vx = SIMON_STAIR_SPEED_X;
		else vx = -SIMON_STAIR_SPEED_X;
		vy = -SIMON_STAIR_SPEED_Y;
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case STAIR_DOWN:
		isStand = true;
		if (nx > 0) vx = SIMON_STAIR_SPEED_X;
		else vx = -SIMON_STAIR_SPEED_X;
		vy = SIMON_STAIR_SPEED_Y;
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

bool Simon::CheckCollisionWithStair(vector<LPGAMEOBJECT>* listStair)
{
	float simon_l, simon_t, simon_r, simon_b;
	GetBoundingBox(simon_l, simon_t, simon_r, simon_b);

	// thu nhỏ vùng xét va chạm, chỉ xét va chạm với chân của Simon
	simon_t += 55;
	simon_b += 5;  // bottom +5 để xét cho va chạm với bậc thang đầu tiên khi bước xuống
	simon_l += 5;
	simon_r -= 5;

	for (UINT i = 0; i < listStair->size(); i++)
	{
		float stair_l, stair_t, stair_r, stair_b;
		listStair->at(i)->GetBoundingBox(stair_l, stair_t, stair_r, stair_b);
		

		if (GameObject::AABB(simon_l, simon_t, simon_r, simon_b, stair_l, stair_t, stair_r, stair_b) == true)
		{
			//DebugOut(L"collision\n");

			if (listStair->at(i)->GetState() == 0) stairDirection = 1;
			else stairDirection = -1;

			stairCollided = listStair->at(i);

			// bậc thang ở dưới so với chân Simon->có thể di chuyển xuống.
			if (simon_b < stair_b) isMovingDown = true;
			
			// kiểm tra xem simon có thể di chuyển lên hay ko
			// vì mảng listStairs gồm các bậc thang liền kề nhau, nên chỉ cần kiểm tra 2 bậc là đủ.

			float upstair_x = -999, upstair_y = -999; // toạ độ của bậc thang liền kề ở phía trên (nếu có)

			if (i > 0)
			{
				listStair->at(i - 1)->GetPosition(upstair_x, upstair_y);

				float dx = abs(upstair_x - stair_l);
				float dy = upstair_y - stair_t;

				if (dx == GROUND_BBOX_WIDTH && dy == -GROUND_BBOX_HEIGHT) // vì bậc nằm trên nên dy = -...
				{
					isMovingUp = true;
					return true;
				}
			}
			
			if (i < listStair->size() - 1)
			{
				listStair->at(i + 1)->GetPosition(upstair_x, upstair_y);

				float dx = abs(upstair_x - stair_l);
				float dy = upstair_y - stair_t;

				if (dx == GROUND_BBOX_WIDTH && dy == -GROUND_BBOX_HEIGHT)  
				{
					isMovingUp = true;
					return true;
				}
			}

			// ko có bậc thang kế tiếp, tuy nhiên cần kiểm tra simon đã đi hết sprite thang hiện tại chưa
			// (một sprite là 32x32, gồm 2 bậc thang, mỗi lần simon chỉ đi lên 1 bậc)
			if (stair_t - y < 60)
			{
				isMovingUp = true;
				return true;
			}

			isMovingUp = false;
			return true; // collision between Simon and stairs
		}
			
	}

	isMovingUp = false;
	isMovingDown = false;

	return false;
}

void Simon::PositionCorrection(int prevState)
{
	float stair_x, stair_y;
	stairCollided->GetPosition(stair_x, stair_y);

	if (prevState == -1)
	{
		if (state == STAIR_UP)
		{
			if (stairDirection == 1)
			{
				x = stair_x - 34.0f;
				y = stair_y - 31.0f;
			}
			else
			{
				x = stair_x + 6.0f;
				y = stair_y - 31.0f;
			}
		}
		else if (state == STAIR_DOWN)
		{
			if (stairDirection == 1)
			{
				x = stair_x - 10.0f;
				y = stair_y - 47.0f;
			}
			else
			{
				x = stair_x - 18.0f;
				y = stair_y - 47.0f;
			}
		}
	}
	else 
	{
		if (state == STAIR_UP && prevState == STAIR_DOWN)
		{
			if (stairDirection == 1)
			{
				x -= 3.0f;
			}
			else
			{
				x += 3.0f;
			}
		}
		else if (state == STAIR_DOWN && prevState == STAIR_UP)
		{
			if (stairDirection == 1)
			{
				x += 3.0f;
			}
			else
			{
				x -= 3.0f;
			}
		}
	}
}

void Simon::StandOnStair()
{
	vx = 0;
	vy = 0;
}





