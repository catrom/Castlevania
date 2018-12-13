#include "Input.h"



Input::Input(Game * game, SceneManager * scene)
{
	this->game = game;
	this->scene = scene;
}

Input::~Input()
{
}

void Input::KeyState(BYTE *state)
{
	Simon * simon = scene->GetSimon();

	if (simon->GetState() == DEAD)
		return;

	if (simon->IsAutoWalk() == true)
		return;

	if (isNeedToWaitingAnimation == true)
	{
		if (simon->GetState() == POWER && simon->animations[POWER]->IsOver(450) == false)
			return;

		if (simon->GetState() == STAIR_UP && simon->animations[STAIR_UP]->IsOver(200) == false)
			return;

		if (simon->GetState() == STAIR_DOWN && simon->animations[STAIR_DOWN]->IsOver(200) == false)
			return;

		if (simon->GetState() == DEFLECT && simon->animations[DEFLECT]->IsOver(600) == false)
			return;

		// nếu simon đang nhảy và chưa chạm đất, tiếp tục render trạng thái nhảy
		if ((simon->GetState() == JUMP || simon->GetState() == STAND)
			&& simon->IsTouchGround() == false)
			return;

		// nếu simon đang quất roi và animation chưa được render hết thì tiếp tục render

		if (simon->GetState() == HIT_STAND && simon->animations[HIT_STAND]->IsOver(300) == false)
			return;

		if (simon->GetState() == HIT_SIT && simon->animations[HIT_SIT]->IsOver(300) == false)
			return;

		if (simon->GetState() == HIT_STAIR_UP && simon->animations[HIT_STAIR_UP]->IsOver(300) == false)
			return;

		if (simon->GetState() == HIT_STAIR_DOWN && simon->animations[HIT_STAIR_DOWN]->IsOver(300) == false)
			return;

	}
	else
	{
		// Đặt lại biến chờ render animation
		isNeedToWaitingAnimation = true;

		// Để tránh việc ở frame tiếp theo rơi vào trạng thái chờ render animation 
		// (vì animation == 200ms, một frame == 30ms nên sẽ phải bị chờ dù cho có biến isNeedToWaitingAnimation),
		// do đó cần reset lại animation start time về 0
		simon->animations[simon->GetState()]->SetAniStartTime(0);
	}


	// Xét trạng thái phím
	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (StairCollisionsDetection() == true && simon->IsStandOnStair() == true)
		{
			if (simon->GetStairDirection() == 1) // cầu thang trái dưới - phải trên
			{
				Simon_Stair_Up();
			}
			else {
				Simon_Stair_Down();
			}

			return;
		}

		Simon_Walk_Right();
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (StairCollisionsDetection() == true && simon->IsStandOnStair() == true)
		{
			if (simon->GetStairDirection() == 1) // cầu thang trái dưới - phải trên
			{
				Simon_Stair_Down();
			}
			else {
				Simon_Stair_Up();
			}

			return;
		}

		Simon_Walk_Left();
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		if (StairCollisionsDetection() == true)
		{
			Simon_Stair_Down();
			return;
		}

		if (simon->IsTouchGround() == true)
			simon->SetState(SIT);
		else simon->SetState(STAND);
	}
	else if (game->IsKeyDown(DIK_UP))
	{
		if (StairCollisionsDetection() == true)
		{
			Simon_Stair_Up();
			return;
		}

		simon->SetState(STAND);
	}
	else
	{
		simon->SetHitSubWeapons(false);

		if (StairCollisionsDetection() == true)
		{
			if (Simon_Stair_Stand() == true)
			{
				return;
			}
		}

		simon->SetState(STAND);
	}
}

void Input::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	if (scene->GetSimon()->GetState() == DEAD)
		return;

	switch (KeyCode)
	{
	case DIK_0:
		scene->GetSimon()->SetSubWeapon(WEAPONS_STOP_WATCH);
		break;
	case DIK_1:
		scene->GetSimon()->SetSubWeapon(WEAPONS_DAGGER);
		break;
	case DIK_2:
		scene->GetSimon()->SetSubWeapon(WEAPONS_AXE);
		break;
	case DIK_3:
		scene->GetSimon()->SetSubWeapon(WEAPONS_HOLY_WATER);
		break;
	case DIK_4:
		scene->GetSimon()->SetSubWeapon(WEAPONS_BOOMERANG);
		break;
	case DIK_5:
		scene->GetSimon()->SetCrossCollected(true);
		break;
	case DIK_6:
		scene->GetSimon()->SetGotDoubleShotItem(true);
		break;
	case DIK_7:
		scene->GetSimon()->SetGotTripleShotItem(true);
		break;
	case DIK_SPACE:
		Simon_Jump();
		break;
	case DIK_Z:
		Simon_Hit();
		break;
	case DIK_X:
		Simon_Hit_SubWeapon();
		break;
	default:
		break;
	}
}

void Input::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void Input::Simon_Walk_Left()
{
	scene->GetSimon()->SetOrientation(-1);
	scene->GetSimon()->SetState(WALK);
}

void Input::Simon_Walk_Right()
{
	scene->GetSimon()->SetOrientation(1);
	scene->GetSimon()->SetState(WALK);
}

void Input::Simon_Jump()
{
	if (scene->GetSimon()->GetState() == JUMP ||
		scene->GetSimon()->GetState() == HIT_STAND ||
		scene->GetSimon()->GetState() == HIT_SIT)
		return;

	scene->GetSimon()->SetState(JUMP);
}

void Input::Simon_Hit()
{
	if ((scene->GetSimon()->GetState() == HIT_STAND || scene->GetSimon()->GetState() == HIT_SIT))
		return;

	if (scene->GetSimon()->GetState() == STAND || scene->GetSimon()->GetState() == JUMP)
	{
		scene->GetSimon()->SetState(HIT_STAND);
	}
	else if (scene->GetSimon()->GetState() == SIT)
	{
		scene->GetSimon()->SetState(HIT_SIT);
	}
	else if (scene->GetSimon()->GetState() == STAIR_UP)
	{
		scene->GetSimon()->SetState(HIT_STAIR_UP);
	}
	else if (scene->GetSimon()->GetState() == STAIR_DOWN)
	{
		scene->GetSimon()->SetState(HIT_STAIR_DOWN);
	}
}

void Input::Simon_Hit_SubWeapon()
{
	Simon * simon = scene->GetSimon();
	vector<SubWeapon*> * weaponlist = scene->GetWeaponList();
	SubWeapon * weapon;

	if (simon->GetSubWeapon() == -1 || simon->GetEnergy() == 0) // không có vũ khí hoặc enery = 0
		return;

	if (simon->GetSubWeapon() == STOP_WATCH && simon->GetEnergy() < 5)
		return;

	if (weaponlist->at(0)->GetState() == STOP_WATCH && scene->IsUsingStopWatch() == true) // đang sử dụng stop watch
		return;

	if (weaponlist->at(0)->IsEnable() == false)
		weapon = weaponlist->at(0);
	else if (weaponlist->at(1)->IsEnable() == false && (scene->IsDoubleShotEffect() || scene->IsTripleShotEffect()))
		weapon = weaponlist->at(1);
	else if (weaponlist->at(2)->IsEnable() == false && scene->IsTripleShotEffect())
		weapon = weaponlist->at(2);
	else return;

	if (simon->GetState() == STAND || simon->GetState() == JUMP ||
		simon->GetState() == SIT || simon->GetState() == STAIR_UP ||
		simon->GetState() == STAIR_DOWN)
	{
		float sx, sy;

		// position
		simon->GetPosition(sx, sy);
		
		if (simon->GetState() == SIT) sy += 25.0f; // khớp vị trí tay
		else sy += 10.0f;
		if (simon->GetOrientation() < 0) sx += 30.0f;

		weapon->SetPosition(sx, sy); 

		// orientation
		weapon->SetOrientation(simon->GetOrientation());

		// state enable
		weapon->SetEnable(true);
		weapon->SetState(simon->GetSubWeapon());

		if (weapon->GetState() == STOP_WATCH)
		{
			simon->LoseEnergy(5);
			scene->StartStopWatch();
		}
		else
		{
			simon->LoseEnergy(1);
			simon->SetHitSubWeapons(true);
			Simon_Hit();
		}
	}
}

void Input::Simon_Stair_Down()
{
	Simon * simon = scene->GetSimon();
	int prevState = simon->GetState();
	int stairDirection = simon->GetStairDirection();
	
	if (simon->IsMovingDown() == false)
	{
		simon->SetState(STAND);
		return;
	}

	// Auto-walk của Simon đi đến đúng đầu cầu thang rồi mới bước lên
	if (simon->IsStandOnStair() == false)
	{
		float stair_x, simon_x, temp_y;

		simon->GetStairCollided()->GetPosition(stair_x, temp_y);
		simon->GetPosition(simon_x, temp_y);

		if (stairDirection == -1) stair_x -= 28.0f;

		if (stair_x < simon_x) simon->SetOrientation(-1);
		else if (stair_x > simon_x) simon->SetOrientation(1);
		else return;

		simon->SetState(WALK);
		simon->vy = 0;
		simon->AutoWalk(stair_x - simon_x, STAIR_DOWN, -stairDirection);
		simon->SetStandOnStair(true);

		return;
	}
	else
	{
		simon->SetOrientation(-simon->GetStairDirection());
		simon->SetState(STAIR_DOWN);
	}

	return;
}

void Input::Simon_Stair_Up()
{
	Simon * simon = scene->GetSimon();
	int prevState = simon->GetState();
	int stairDirection = simon->GetStairDirection();

	if (simon->IsMovingUp() == false)
	{
		if (prevState == STAIR_UP || prevState == STAIR_DOWN)
		{
			int nx = simon->GetStairDirection();
			simon->SetOrientation(nx);
			simon->SetState(STAIR_UP);
			simon->AutoWalk(16 * nx, STAND, nx);
		}

		return;
	}

	// Auto-walk của Simon đi đến đúng chân cầu thang rồi mới bước lên
	if (simon->IsStandOnStair() == false)
	{
		float stair_x, simon_x, temp_y;

		simon->GetStairCollided()->GetPosition(stair_x, temp_y);
		simon->GetPosition(simon_x, temp_y);

		if (stairDirection == 1) stair_x -= 31.0f;
		else stair_x += 5.0f;

		if (stair_x < simon_x) simon->SetOrientation(-1);
		else if (stair_x > simon_x)  simon->SetOrientation(1);
		else return;

		simon->SetState(WALK);
		simon->vy = 0;
		simon->AutoWalk(stair_x - simon_x, STAIR_UP, stairDirection);
		simon->SetStandOnStair(true);

		return;
	}
	else
	{
		simon->SetOrientation(stairDirection);
		simon->SetState(STAIR_UP);
	}

	return;
}

bool Input::Simon_Stair_Stand()
{
	Simon * simon = scene->GetSimon();

	if (simon->GetState() == STAIR_UP || simon->GetState() == STAIR_DOWN ||
		simon->GetState() == HIT_STAIR_UP || simon->GetState() == HIT_STAIR_DOWN)
	{
		if (simon->GetState() == HIT_STAIR_UP)
		{
			simon->SetState(STAIR_UP);
			isNeedToWaitingAnimation = false;
		}
		else if (simon->GetState() == HIT_STAIR_DOWN)
		{
			simon->SetState(STAIR_DOWN);
			isNeedToWaitingAnimation = false;
		}

		simon->StandOnStair();
		simon->animations[simon->GetState()]->Reset();

		return true;
	}

	return false;
}

bool Input::StairCollisionsDetection()
{
	Simon * simon = scene->GetSimon();
	vector<LPGAMEOBJECT> * listStairs = scene->GetListStairs();

	return simon->CheckCollisionWithStair(listStairs);
}
