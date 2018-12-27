#include "Simon.h"
#include "Candle.h"
#include "Ground.h"
#include "Items.h"
#include "Door.h"
#include "Zombie.h"
#include "BlackLeopard.h"
#include "VampireBat.h"
#include "FishMan.h"
#include "FireBall.h"
#include "Stair.h"
#include "Boss.h"
#include "ChangeSceneObject.h"
#include "Water.h"

Simon::Simon() : GameObject()
{
	SetState(STAND);

	AddAnimation(STAND_ANI);
	AddAnimation(WALK_ANI);
	AddAnimation(SIT_ANI);
	AddAnimation(JUMP_ANI);
	AddAnimation(HIT_SIT_ANI);
	AddAnimation(HIT_STAND_ANI);
	AddAnimation(POWER_ANI);
	AddAnimation(STAIR_UP_ANI);
	AddAnimation(STAIR_DOWN_ANI);
	AddAnimation(HIT_STAIR_UP_ANI);
	AddAnimation(HIT_STAIR_DOWN_ANI);
	AddAnimation(DEFLECT_ANI);
	AddAnimation(DEAD_ANI);

	score = 0;
	item = -1;
	energy = 5;
	life = 3;
	subWeapon = -1;
	HP = 16;
}

Simon::~Simon()
{
}

void Simon::LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations)
{
	textures->Add(ID_TEX_SIMON, FILEPATH_TEX_SIMON, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);

	sprites->Add(10001, 0, 0, 60, 64, texSimon);		// stand

	sprites->Add(10011, 0, 0, 60, 64, texSimon);		// walk
	sprites->Add(10012, 60, 0, 120, 64, texSimon);
	sprites->Add(10013, 120, 0, 180, 64, texSimon);
	sprites->Add(10014, 180, 0, 240, 64, texSimon);

	sprites->Add(10021, 300, 198, 360, 262, texSimon);	// sit

	sprites->Add(10031, 240, 0, 300, 64, texSimon);		// jump

	sprites->Add(10041, 420, 66, 480, 130, texSimon);	// hit_sit
	sprites->Add(10042, 0, 132, 60, 196, texSimon);
	sprites->Add(10043, 60, 132, 120, 196, texSimon);

	sprites->Add(10051, 300, 0, 360, 64, texSimon);		// hit_stand
	sprites->Add(10052, 360, 0, 420, 64, texSimon);
	sprites->Add(10053, 420, 0, 480, 64, texSimon);

	sprites->Add(10061, 120, 198, 180, 262, texSimon);	// power up
	sprites->Add(10062, 60, 198, 120, 262, texSimon);
	sprites->Add(10063, 0, 198, 60, 262, texSimon);

	sprites->Add(10071, 240, 66, 300, 130, texSimon);	// stair up
	sprites->Add(10072, 300, 66, 360, 130, texSimon);

	sprites->Add(10081, 120, 66, 180, 130, texSimon);	// stair down
	sprites->Add(10082, 180, 66, 240, 130, texSimon);

	sprites->Add(10091, 300, 132, 360, 196, texSimon);	// hit - stair up
	sprites->Add(10092, 360, 132, 420, 196, texSimon);
	sprites->Add(10093, 420, 132, 480, 196, texSimon);

	sprites->Add(10101, 120, 132, 180, 196, texSimon);	// hit - stair down
	sprites->Add(10102, 180, 132, 240, 196, texSimon);
	sprites->Add(10103, 240, 132, 300, 196, texSimon);

	sprites->Add(10111, 0, 66, 60, 130, texSimon);		// deflect - when collide with enemy

	sprites->Add(10121, 240, 198, 300, 264, texSimon);	// dead


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

	ani = new Animation();
	ani->Add(10001);
	ani->Add(10111, 400);
	ani->Add(10021);
	animations->Add(DEFLECT_ANI, ani);

	ani = new Animation();
	ani->Add(10121);
	animations->Add(DEAD_ANI, ani);
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, bool stopMovement)
{
	GameObject::Update(dt);

	// Update vy
	if (isStandOnStair == false && isAutoWalk == false)
	{
		if (vy > -SIMON_SPEED_Y_LOWER_ZONE && vy < SIMON_SPEED_Y_LOWER_ZONE)
			vy += SIMON_GRAVITY_LOWER*dt;
		else 
			vy += SIMON_GRAVITY*dt;
	}

	// Auto - walk
	if (isAutoWalk == true)
		DoAutoWalk();
	
	// Reset untouchable timer if untouchable time has passed
	if (untouchableTimer->IsTimeUp() == true)
		untouchableTimer->Stop();

	// Reset invisibility timer if invisibility time has passed
	if (invisibilityTimer->IsTimeUp() == true)
		invisibilityTimer->Stop();

	// Check collision between Simon and other objects
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0 && isAutoWalk == false)
	{
		x += dx;
		y += dy;

		if (vy > SIMON_SPEED_Y_LOWER_ZONE)
			isFalling = true;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		if (isAutoWalk == false)
		{
			x += min_tx*dx + nx*0.1f;
			y += min_ty*dy + ny*0.1f;
		}


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Ground*>(e->obj))
			{
				if (e->ny != 0)
				{
					// BUG: 
					// Simon deflect ngay lập tức va chạm với ground (đôi lúc) -> không bật nhảy được.
					if (e->ny == -1 && (state != DEFLECT || (state == DEFLECT && vy > 0) ))
					{
						vy = 0;
						isTouchGround = true;
						isFalling = false;

						if (HP == 0)
						{
							SetState(DEAD);
							return;
						}
					}
					else
						y += dy;		
				}
				
				// Khi đang lên/xuống cầu thang, va chạm theo trục x sẽ không được xét tới
				if (state == STAIR_UP || state == STAIR_DOWN)
					if (nx != 0) x -= nx*0.1f;
			}
			else if (dynamic_cast<Door*>(e->obj))
			{
				auto door = dynamic_cast<Door*>(e->obj);

				if (door->GetState() == DOOR_2_IDLE)
				{
					vx = 0;

					if (e->nx == 1.0f)	 // Simon đã đi qua cửa
						x += 1.0f;		 // +1 để không bị overlap
					else
					{
						door->SetState(DOOR_2_OPEN);
						door->animations[DOOR_2_OPEN]->SetAniStartTime(GetTickCount());

						isWalkThroughDoor = true;
					}
				}
				else if (e->obj->GetState() == DOOR_1)	// đi qua cửa của scene 1
				{
					SetState(WALK);
					vx = SIMON_WALKING_SPEED_LOWER;
					vy = 0;
					AutoWalk(80, STAND, 1);
				}
			}
			else if (dynamic_cast<ChangeSceneObject*>(e->obj))
			{
				x += dx;
				y += dy;

				ChangeSceneObject * obj = dynamic_cast<ChangeSceneObject*>(e->obj);

				if ((obj->GetIDNextScene() == SCENE_3 && this->state == STAIR_DOWN) ||
					(obj->GetIDNextScene() == SCENE_2 && (this->state == STAIR_UP || this->state == WALK)))
				{
					isAutoWalk = false;
					this->changeScene = obj->GetIDNextScene();
				}	
			}
			else if (dynamic_cast<Water*>(e->obj))
			{
				Water * water = dynamic_cast<Water*>(e->obj);
				water->AddBubbles(x, y + SIMON_BBOX_HEIGHT);

				SetState(DEAD);
				isFallingWater = true;
				return;
			}
			else if (dynamic_cast<FireBall*>(e->obj))
			{
				LoseHP(1);
				e->obj->SetEnable(false);
			}
			else if (dynamic_cast<Zombie*>(e->obj) || dynamic_cast<BlackLeopard*>(e->obj)
				|| dynamic_cast<VampireBat*>(e->obj) || dynamic_cast<FishMan*>(e->obj)
				|| dynamic_cast<Boss*>(e->obj))
			{
				if (state != POWER && untouchableTimer->IsTimeUp() == true && invisibilityTimer->IsTimeUp() == true)
				{
					untouchableTimer->Start();

					if (dynamic_cast<Zombie*>(e->obj))
					{
						Zombie * zombie = dynamic_cast<Zombie*>(e->obj);
						LoseHP(zombie->GetAttack());
					}
					else if (dynamic_cast<BlackLeopard*>(e->obj))
					{
						BlackLeopard * leopard = dynamic_cast<BlackLeopard*>(e->obj);
						LoseHP(leopard->GetAttack());
					}
					else if (dynamic_cast<VampireBat*>(e->obj)) 
					{
						VampireBat * bat = dynamic_cast<VampireBat*>(e->obj);
						bat->SetState(VAMPIRE_BAT_DESTROYED);	// nếu dơi tông trúng simon thì cho huỷ
						LoseHP(bat->GetAttack());
					}
					else if (dynamic_cast<FishMan*>(e->obj))
					{
						FishMan * fishman = dynamic_cast<FishMan*>(e->obj);
						LoseHP(fishman->GetAttack());
					}
					else if (dynamic_cast<Boss*>(e->obj))
					{
						Boss * boss = dynamic_cast<Boss*>(e->obj);
						LoseHP(boss->GetAttack());
					}
					
					if (isStandOnStair == false || HP == 0)  // Simon đứng trên cầu thang sẽ không bị bật ngược lại
					{
						// đặt trạng thái deflect cho simon
						if (e->nx != 0)
						{
							if (e->nx == 1.0f && this->nx == 1) this->nx = -1;
							else if (e->nx == -1.0f && this->nx == -1) this->nx = 1;
						}

						SetState(DEFLECT);
					}
				}
				else
				{
					if (e->nx != 0) x += dx;
					if (e->ny != 0) y += dy;
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void Simon::Render()
{
	if (isFallingWater == true)
		return;

	int tempState = state;
	int alpha = 255;

	// Khi Simon rơi từ trên cao xuống thì luôn co chân
	// Sử dụng biến tạm để không thay đổi trạng thái gốc của Simon
	if (state != DEAD && IsHit() == false && isFalling == true)
		tempState = JUMP;

	if (untouchableTimer->IsTimeUp() == false)  // Để render Simon nhấp nháy trong trạng thái isUntouchable
		alpha = rand() % 255;
	else if (invisibilityTimer->IsTimeUp() == false)
	{
		float ratio = (float)(GetTickCount() - invisibilityTimer->GetStartTime()) / SIMON_INVISIBILITY_TIME;

		if (ratio < 0.5f)			// nhấp nháy
			alpha = 50;
		else 
			alpha = (int)(255 * ratio);	// render rõ dần theo thời gian
	}

	animations[tempState]->Render(1, nx, x, y, alpha);
}

void Simon::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case STAND:
		isStandOnStair = false;
		isFallingWater = false;
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
		vy = -SIMON_JUMP_SPEED_Y;
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case SIT:
		isStandOnStair = false;
		vx = 0;
		vy = 0;
		break;
	case HIT_SIT:
		isStandOnStair = false;
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case HIT_STAND:
		isStandOnStair = false;
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case POWER:
		isStandOnStair = false;
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case STAIR_UP:
		if (nx > 0) vx = SIMON_STAIR_SPEED_X;
		else vx = -SIMON_STAIR_SPEED_X;
		vy = -SIMON_STAIR_SPEED_Y;
		isStandOnStair = true;
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case STAIR_DOWN:
		if (nx > 0) vx = SIMON_STAIR_SPEED_X;
		else vx = -SIMON_STAIR_SPEED_X;
		vy = SIMON_STAIR_SPEED_Y;
		isStandOnStair = true;
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case DEFLECT:
		vy = -SIMON_DEFLECT_SPEED_Y;
		if (nx > 0) vx = -SIMON_DEFLECT_SPEED_X;
		else vx = SIMON_DEFLECT_SPEED_X;
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case HIT_STAIR_UP:
	case HIT_STAIR_DOWN:
		vx = 0;
		vy = 0;
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case DEAD:
		untouchableTimer->Stop();
		invisibilityTimer->Stop();
		vx = 0;
		vy = 0;
		life -= 1;
		break;
	default:
		break;
	}
}

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	// sprite có kích thước là 60x66, bbox là 40x62
	left = x + 15; //30,60
	top = y + 2;  //62,66
	right = left + SIMON_BBOX_WIDTH;
	bottom = top + SIMON_BBOX_HEIGHT;

}

void Simon::GetActiveBoundingBox(float & left, float & top, float & right, float & bottom)
{
	GetBoundingBox(left, top, right, bottom);
}

void Simon::LoseHP(int x)
{
	HP -= x;

	if (HP <= 0)
		HP = 0;
}

bool Simon::CheckCollisionWithStair(vector<LPGAMEOBJECT>* listStair)
{
	canMoveUpStair = false;
	canMoveDownStair = false;


	float simon_l, simon_t, simon_r, simon_b;
	GetBoundingBox(simon_l, simon_t, simon_r, simon_b);

	// thu nhỏ vùng xét va chạm, chỉ xét va chạm với chân của Simon
	simon_t += 50;
	simon_b += 5;  // bottom +5 để xét cho va chạm với bậc thang đầu tiên khi bước xuống

	for (UINT i = 0; i < listStair->size(); i++)
	{
		float stair_l, stair_t, stair_r, stair_b;
		listStair->at(i)->GetBoundingBox(stair_l, stair_t, stair_r, stair_b);


		if (GameObject::AABB(simon_l, simon_t, simon_r, simon_b, stair_l, stair_t, stair_r, stair_b) == true)
		{
			if (listStair->at(i)->GetState() == 0) stairDirection = 1;
			else stairDirection = -1;

			stairCollided = listStair->at(i);

			// bậc thang ở dưới so với chân Simon->có thể di chuyển xuống.
			if (simon_b < stair_b) canMoveDownStair = true;
			if (y >= stair_t - 35) canMoveUpStair = true;

			// kiểm tra xem simon có thể di chuyển lên/xuống hay ko
			// (dựa vào toạ độ của 2 bậc liền kề hơn/kém nhau 32)

			float upstair_x = -999, upstair_y = -999; // toạ độ của bậc thang liền kề

			for (UINT j = 0; j < listStair->size(); j++)
			{
				if (i == j)
					continue;

				listStair->at(j)->GetPosition(upstair_x, upstair_y);

				float dx = abs(upstair_x - stair_l);
				float dy = upstair_y - stair_t;

				if (dx == GROUND_BBOX_WIDTH && dy == -GROUND_BBOX_HEIGHT) // vì bậc nằm trên nên dy = -...
					canMoveUpStair = true;

				if (dx == GROUND_BBOX_WIDTH && dy == GROUND_BBOX_HEIGHT) // vì bậc nằm duoi nên dy = +...
					canMoveDownStair = true;
			}
		

			return true; // collision between Simon and stairs
		}

	}

	return false;
}

bool Simon::CheckCollisionWithItem(vector<LPGAMEOBJECT> * listItem)
{
	float simon_l, simon_t, simon_r, simon_b;
	float item_l, item_t, item_r, item_b;

	GetBoundingBox(simon_l, simon_t, simon_r, simon_b);

	for (UINT i = 0; i < listItem->size(); i++)
	{
		if (listItem->at(i)->IsEnable() == false)
			continue;

		listItem->at(i)->GetBoundingBox(item_l, item_t, item_r, item_b);

		if (GameObject::AABB(simon_l, simon_t, simon_r, simon_b, item_l, item_t, item_r, item_b) == true)
		{
			listItem->at(i)->isEnable = false;

			int idItem = listItem->at(i)->GetState();

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
				isGotCrossItem = true;
				break;
			case INVISIBILITY_POTION:
				invisibilityTimer->Start();
				break;
			case CHAIN:
				SetState(POWER); // đổi trạng thái power - biến hình nhấp nháy các kiểu đà điểu
				vx = 0;
				isGotChainItem = true;
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
				item = idItem;
				isGotDoubleShotItem = true;
				break;
			case TRIPLE_SHOT:
				item = idItem;
				isGotTripleShotItem = true;
				break;
			case PORK_CHOP:
				HP += 2;
				if (HP > SIMON_HP)
					HP = SIMON_HP;
				break;
			case MAGIC_CRYSTAL:
				HP = SIMON_HP;
				break;
			default:
				break;
			}

			return true;
		}
	}
}

void Simon::CheckCollisionWithEnemyActiveArea(vector<LPGAMEOBJECT>* listObjects)
{
	float simon_l, simon_t, simon_r, simon_b;

	GetBoundingBox(simon_l, simon_t, simon_r, simon_b);

	for (UINT i = 0; i < listObjects->size(); i++)
	{
		Enemy * enemy = dynamic_cast<Enemy*>(listObjects->at(i));

		if (enemy == NULL)
			continue;

		// Không cần xét vùng active nữa khi nó đang active / destroyed
		if (enemy->GetState() == ACTIVE || enemy->GetState() == DESTROYED)
			continue;

		float enemy_l, enemy_t, enemy_r, enemy_b;
		enemy->GetActiveBoundingBox(enemy_l, enemy_t, enemy_r, enemy_b);

		if (GameObject::AABB(simon_l, simon_t, simon_r, simon_b, enemy_l, enemy_t, enemy_r, enemy_b) == true)
		{
			D3DXVECTOR2 enemyEntryPostion = enemy->GetEntryPosition();

			if (dynamic_cast<Zombie*>(enemy))
			{
				Zombie * zombie = dynamic_cast<Zombie*>(enemy);

				if (zombie->GetState() == ZOMBIE_INACTIVE && zombie->IsAbleToActivate() == true)
					zombie->SetState(ZOMBIE_ACTIVE);
			}
			else if (dynamic_cast<BlackLeopard*>(enemy))
			{
				BlackLeopard * leopard = dynamic_cast<BlackLeopard*>(enemy);
				if (leopard->GetState() == BLACK_LEOPARD_IDLE)
					leopard->SetState(BLACK_LEOPARD_ACTIVE);
			}
			else if (dynamic_cast<VampireBat*>(enemy))
			{
				VampireBat * bat = dynamic_cast<VampireBat*>(enemy);

				if (bat->GetState() == VAMPIRE_BAT_INACTIVE && bat->IsAbleToActivate() == true)
					bat->SetState(VAMPIRE_BAT_ACTIVE);
			}
			else if (dynamic_cast<FishMan*>(enemy))
			{
				FishMan * fishman = dynamic_cast<FishMan*>(enemy);

				if (fishman->GetState() == FISHMAN_INACTIVE && fishman->IsAbleToActivate() == true)
					fishman->SetState(FISHMAN_ACTIVE);
			}
			else if (dynamic_cast<Boss*>(enemy))
			{
				Boss * boss = dynamic_cast<Boss*>(enemy);
				boss->SetState(BOSS_ACTIVE);
			}
		}
	}
}

void Simon::AutoWalk(float distance, int new_state, int new_nx)
{
	isAutoWalk = true;

	autoWalkDistance = distance;
	stateAfterAutoWalk = new_state;
	nxAfterAutoWalk = new_nx;
}

void Simon::DoAutoWalk()
{
	if (abs(dx) <= abs(autoWalkDistance))
	{
		x += dx;
		y += dy;
		autoWalkDistance -= dx;
	}
	else
	{
		x += autoWalkDistance;
		state = stateAfterAutoWalk;
		nx = nxAfterAutoWalk;

		SetState(state);
		if (state == STAIR_DOWN) y += 1.0f; // + 1.0f để đảm bảo simon sẽ va chạm với bậc thang trong lần update kế tiếp

		isAutoWalk = false;
		autoWalkDistance = 0;
		stateAfterAutoWalk = -1;
		nxAfterAutoWalk = 0;
	}
}

bool Simon::IsHit()
{
	return state == HIT_SIT || state == HIT_STAND || state == HIT_STAIR_DOWN || state == HIT_STAIR_UP;
}





