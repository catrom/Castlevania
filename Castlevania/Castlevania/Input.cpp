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
	bool isCollideWithStair = false;

	Simon * simon = scene->GetSimon();
	vector<LPGAMEOBJECT> * listStairs = scene->GetListStairs();

	if (simon->CheckCollisionWithStair(listStairs) == true)
	{
		isCollideWithStair = true;
	}


	if (scene->GetSimon()->IsAutoWalk() == true)
		return;

	if (scene->GetSimon()->GetState() == POWER && scene->GetSimon()->animations[POWER]->IsOver(450) == false)
		return;

	if (scene->GetSimon()->GetState() == HIT && scene->GetSimon()->animations[HIT]->IsOver(300) == false)
		return;

	if (scene->GetSimon()->GetState() == STAIR_UP && scene->GetSimon()->animations[STAIR_UP]->IsOver(200) == false)
		return;

	if (scene->GetSimon()->GetState() == STAIR_DOWN && scene->GetSimon()->animations[STAIR_DOWN]->IsOver(200) == false)
		return;

	if (scene->GetSimon()->GetState() == DEFLECT && scene->GetSimon()->animations[DEFLECT]->IsOver(600) == false)
		return;

	// nếu simon đang nhảy và chưa chạm đất, tiếp tục render trạng thái nhảy
	if ((scene->GetSimon()->GetState() == JUMP || scene->GetSimon()->GetState() == STAND)
		&& scene->GetSimon()->IsTouchGround() == false)
		return;

	// nếu simon đang quất roi và animation chưa được render hết thì tiếp tục render

	if (scene->GetSimon()->GetState() == HIT_STAND && scene->GetSimon()->animations[HIT_STAND]->IsOver(300) == false)
		return;

	if (scene->GetSimon()->GetState() == HIT_SIT && scene->GetSimon()->animations[HIT_SIT]->IsOver(300) == false)
		return;


	if (game->IsKeyDown(DIK_RIGHT))
	{
		scene->GetSimon()->SetOrientation(1);
		scene->GetSimon()->SetState(WALK);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		scene->GetSimon()->SetOrientation(-1);
		scene->GetSimon()->SetState(WALK);
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		int prevState = simon->GetState();

		if (isCollideWithStair == true)
		{
			if (simon->IsMovingDown() == false)
			{
				simon->SetState(STAND);

				return;
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
			return;
		}

		scene->GetSimon()->SetState(SIT);
	}
	else if (game->IsKeyDown(DIK_UP))
	{
		int prevState = simon->GetState();

		if (isCollideWithStair == true)
		{
			if (simon->IsMovingUp() == false)
			{			
				if (prevState == STAIR_UP || prevState == STAIR_DOWN)
				{
					int nx = simon->GetOrientation();
					simon->SetState(STAIR_UP);
					simon->AutoWalk(16 * nx, STAND, nx);
				}

				return;
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
		}
		else
		{
			simon->SetState(STAND);
		}
	}
	else
	{
		if (isCollideWithStair == true && (simon->GetState() == STAIR_UP || simon->GetState() == STAIR_DOWN))
		{
			simon->StandOnStair();
			simon->animations[simon->GetState()]->Reset();
			return;
		}

		scene->GetSimon()->SetState(STAND);
	}
}

void Input::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	switch (KeyCode)
	{
	case DIK_SPACE:
		if (scene->GetSimon()->GetState() == JUMP
			|| scene->GetSimon()->GetState() == HIT_STAND || scene->GetSimon()->GetState() == HIT_SIT )
			return;
		scene->GetSimon()->SetState(JUMP);
		break;
	case DIK_Z:
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
		break;
	case DIK_X:
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

		break;
	case DIK_C:
		scene->GetSimon()->SetState(WALK);
		scene->GetSimon()->AutoWalk(100, STAND, -1);
		break;
	default:
		break;
	}
}

void Input::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}
