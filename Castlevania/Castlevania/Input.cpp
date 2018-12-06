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

	if (simon->IsAutoWalk() == true)
		return;

	if (isNeedToWaitingAnimation == true)
	{
		if (simon->GetState() == POWER && simon->animations[POWER]->IsOver(450) == false)
			return;

		if (simon->GetState() == HIT && simon->animations[HIT]->IsOver(300) == false)
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

	switch (KeyCode)
	{
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
	if (scene->GetSimon()->GetSubWeapon() == -1 || scene->GetSimon()->GetEnergy() == 0) // không có vũ khí hoặc enery = 0
		return;
	if (scene->GetSimon()->GetState() == STAND || scene->GetSimon()->GetState() == JUMP)
	{
		Simon * simon = scene->GetSimon();
		SubWeapon * weapon = scene->GetWeapon();
		float sx, sy;

		// position
		simon->GetPosition(sx, sy);
		weapon->SetPosition(sx, sy);

		// orientation
		weapon->SetOrientation(simon->GetOrientation());

		// state weapon
		weapon->SetState(simon->GetSubWeapon());

		weapon->SetEnable(true);
		simon->LoseEnergy(1);
		simon->SetState(HIT);
	}
}

bool Input::Simon_Stair_Down()
{
	Simon * simon = scene->GetSimon();
	int prevState = simon->GetState();

	if (simon->IsMovingDown() == false)
	{
		simon->SetState(STAND);

		return true;
	}


	simon->SetOrientation(-simon->GetStairDirection());
	simon->SetState(STAIR_DOWN);


	if (simon->IsStandOnStair() == false)
	{
		simon->SetStandOnStair(true);
		simon->PositionCorrection();
	}
	else if (prevState == STAIR_UP)
	{
		simon->PositionCorrection(prevState);
	}

	return true;
}

bool Input::Simon_Stair_Up()
{
	Simon * simon = scene->GetSimon();
	int prevState = simon->GetState();

	if (simon->IsMovingUp() == false)
	{
		if (prevState == STAIR_UP || prevState == STAIR_DOWN)
		{
			int nx = simon->GetOrientation();
			simon->SetState(STAIR_UP);
			simon->AutoWalk(16 * nx, STAND, nx);
		}

		return true;
	}


	simon->SetOrientation(simon->GetStairDirection());
	simon->SetState(STAIR_UP);


	if (simon->IsStandOnStair() == false)
	{
		simon->SetStandOnStair(true);
		simon->PositionCorrection();
	}
	else if (prevState == STAIR_DOWN)
	{
		simon->PositionCorrection(prevState);
	}

	return true;
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
