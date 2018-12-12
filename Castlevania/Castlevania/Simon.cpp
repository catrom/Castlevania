#include "Simon.h"
#include "Candle.h"
#include "Effect.h"
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
	AddAnimation(WALK_ANI);  // for auto - walk
	AddAnimation(DEFLECT_ANI);

	score = 0;
	item = -1;
	energy = 99;
	life = 3;
	subWeapon = HOLY_WATER;
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

	sprites->Add(10111, 0, 66, 60, 130, texSimon); // deflect - when collied with enemy

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
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, bool stopMovement)
{
	GameObject::Update(dt);

	if (state != STAIR_UP && state != STAIR_DOWN && 
		state != HIT_STAIR_UP && state != HIT_STAIR_DOWN && 
		isAutoWalk == false)
	{
		if (vy < -0.2f || vy > 0.2f)
			vy += SIMON_GRAVITY*dt;
		else vy += SIMON_GRAVITY_LOWER*dt;
	}

	// Auto walk conditions
	if (isAutoWalk == true)
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
			if (state == STAIR_DOWN) y += 2.0f;

			isAutoWalk = false;
			autoWalkDistance = 0;
			stateAfterAutoWalk = -1;
			nxAfterAutoWalk = 0;
		}

		return; // no need to check collision
	}

	// Reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		isUntouchable = false;
	}

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
			if (dynamic_cast<Candle*>(e->obj) ||
				dynamic_cast<Stair*>(e->obj) ||
				dynamic_cast<Items*>(e->obj))
			{
				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;
			}
			else if (dynamic_cast<Ground*>(e->obj))
			{
				if (ny != 0)
				{
					if (ny == -1)
					{
						vy = 0;
						isTouchGround = true;
					}
					else
					{
						y += dy;
						isTouchGround = false;
					}
				}

				if (state == STAIR_UP || state == STAIR_DOWN)
				{
					if (nx != 0) x -= nx*0.1f;
				}

				//DebugOut(L"collision\n");
			}
			else if (dynamic_cast<Door*>(e->obj))
			{
				if (e->obj->GetState() == DOOR_2_IDLE)
				{
					if (e->nx == 1.0f) vx = 0;
					else
					{
						e->obj->SetState(DOOR_2_OPEN);
						e->obj->animations[e->obj->GetState()]->SetAniStartTime(GetTickCount());

						isWalkThroughDoor = true;
					}
				}
				else if (e->obj->GetState() == DOOR_2_OPEN)
				{
					if (nx == -1) vx = 0;
				}
				else
				{
					vx = SIMON_WALKING_SPEED_LOWER;
					vy = 0;
					AutoWalk(80, STAND, 1);
				}
			}
			else if (dynamic_cast<FireBall*>(e->obj))
			{
				LoseHP(2);
				e->obj->SetEnable(false);
			}
			else if (dynamic_cast<Zombie*>(e->obj) || dynamic_cast<BlackLeopard*>(e->obj)
				|| dynamic_cast<VampireBat*>(e->obj) || dynamic_cast<FishMan*>(e->obj)
				|| dynamic_cast<Boss*>(e->obj))
			{
				if (isUntouchable == false)
				{
					// nếu dơi tông trúng simon thì cho huỷ
					if (dynamic_cast<VampireBat*>(e->obj))
					{
						VampireBat * bat = dynamic_cast<VampireBat*>(e->obj);
						bat->SetState(VAMPIRE_BAT_DESTROYED);
					}

					// đặt trạng thái deflect cho simon
					if (e->nx != 0)
					{
						if (e->nx == 1.0f && this->nx == 1) this->nx = -1;
						else if (e->nx == -1.0f && this->nx == -1) this->nx = 1;
					}

					SetState(DEFLECT);
					StartUntouchable();

					LoseHP(2);
				}
				else
				{
					if (e->nx != 0) x += dx;
					if (e->ny != 0) y += dy;
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
}

void Simon::Render()
{
	if (isUntouchable)  // Để render Simon nhấp nháy trong trạng thái isUntouchable
	{
		int r = rand() % 2;

		if (r == 0) animations[state]->Render(1, nx, x, y);
		else animations[state]->Render(1, nx, x, y, 100);
	}
	else
	{
		animations[state]->Render(1, nx, x, y);
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
		animations[state]->SetAniStartTime(GetTickCount());
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
		isStandOnStair = false;
		isStand = true;
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
		break;
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
	case DEFLECT:
		vy = -SIMON_DEFLECT_SPEED_Y;
		if (nx > 0) vx = -SIMON_DEFLECT_SPEED_X;
		else vx = SIMON_DEFLECT_SPEED_X;
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case HIT_STAIR_UP:
	case HIT_STAIR_DOWN:
		isStand = true;
		vx = 0;
		vy = 0;
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

	if (HP < 0)
	{
		HP = 0;
		life -= 1;
	}
}

bool Simon::CheckCollisionWithStair(vector<LPGAMEOBJECT>* listStair)
{
	isMovingUp = false;
	isMovingDown = false;


	float simon_l, simon_t, simon_r, simon_b;
	GetBoundingBox(simon_l, simon_t, simon_r, simon_b);

	// thu nhỏ vùng xét va chạm, chỉ xét va chạm với chân của Simon
	simon_t += 55;
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
			if (simon_b < stair_b) isMovingDown = true;
			if (stair_t - y <= 35) isMovingUp = true;

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
				}

				if (dx == GROUND_BBOX_WIDTH && dy == GROUND_BBOX_HEIGHT) // vì bậc nằm duoi nên dy = +...
				{
					isMovingDown = true;
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
				}

				if (dx == GROUND_BBOX_WIDTH && dy == GROUND_BBOX_HEIGHT) // vì bậc nằm duoi nên dy = +...
				{
					isMovingDown = true;
				}
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
				break;
			case INVISIBILITY_POTION:
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

			return true;
		}
	}
}

void Simon::CheckCollisionWithEnemyActiveArea(vector<LPGAMEOBJECT>* listEnemy)
{
	float simon_l, simon_t, simon_r, simon_b;

	GetBoundingBox(simon_l, simon_t, simon_r, simon_b);

	for (UINT i = 0; i < listEnemy->size(); i++)
	{
		LPGAMEOBJECT enemy = listEnemy->at(i);

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

				if (zombie->IsAbleToActivate() == true)
				{
						if (enemyEntryPostion.x < x) zombie->SetOrientation(1);
						else zombie->SetOrientation(-1);

						zombie->SetState(ZOMBIE_ACTIVE);
				}
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
				{
					bat->SetState(VAMPIRE_BAT_ACTIVE);
				}
			}
			else if (dynamic_cast<FishMan*>(enemy))
			{
				FishMan * fishman = dynamic_cast<FishMan*>(enemy);

				if (fishman->GetState() == FISHMAN_INACTIVE && fishman->IsAbleToActivate() == true)
				{
					fishman->SetState(FISHMAN_JUMP);
				}
			}
			else if (dynamic_cast<Boss*>(enemy))
			{
				Boss * boss = dynamic_cast<Boss*>(enemy);
				boss->SetState(BOSS_ACTIVE);
			}
		}
	}
}

bool Simon::CheckChangeScene(vector<LPCHANGESCENEOBJ>* listChangeScene)
{
	float simon_l, simon_t, simon_r, simon_b;
	float obj_l, obj_t, obj_r, obj_b;

	GetBoundingBox(simon_l, simon_t, simon_r, simon_b);

	for (UINT i = 0; i < listChangeScene->size(); i++)
	{
		listChangeScene->at(i)->GetBoundingBox(obj_l, obj_t, obj_r, obj_b);

		float t, nx, ny;
		GameObject::SweptAABB(simon_l, simon_t, simon_r, simon_b, dx, dy, obj_l, obj_t, obj_r, obj_b, t, nx, ny);
		bool collision = GameObject::AABB(simon_l, simon_t, simon_r, simon_b, obj_l, obj_t, obj_r, obj_b);

		if (nx != 0 || ny != 0 || collision == true)
		{
			changeScene = listChangeScene->at(i)->GetIDNextScene();
			return true;
		}
	}

	return false;
}

void Simon::StandOnStair()
{
	vx = 0;
	vy = 0;
}

void Simon::AutoWalk(float distance, int new_state, int new_nx)
{
	isAutoWalk = true;

	autoWalkDistance = distance;
	stateAfterAutoWalk = new_state;
	nxAfterAutoWalk = new_nx;
}





