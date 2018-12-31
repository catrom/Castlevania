#include "Input.h"



Input::Input(Game * game, SceneManager * scene)
{
	this->game = game;
	this->scene = scene;
}

Input::~Input()
{
}

bool Input::AnimationDelay()
{
	if (isNeedToWaitingAnimation == true)
	{
		if (simon->GetState() == POWER && simon->animations[POWER]->IsOver(POWER_ANI_TIME_DELAY) == false)
			return true;

		if (simon->GetState() == STAIR_UP && simon->animations[STAIR_UP]->IsOver(STAIR_WALK_ANI_TIME_DELAY) == false)
			return true;

		if (simon->GetState() == STAIR_DOWN && simon->animations[STAIR_DOWN]->IsOver(STAIR_WALK_ANI_TIME_DELAY) == false)
			return true;

		if (simon->GetState() == DEFLECT && simon->animations[DEFLECT]->IsOver(DEFLECT_ANI_TIME_DELAY) == false)
			return true;

		if (simon->GetState() == HIT_STAND && simon->animations[HIT_STAND]->IsOver(HIT_ANI_TIME_DELAY) == false)
			return true;

		if (simon->GetState() == HIT_SIT && simon->animations[HIT_SIT]->IsOver(HIT_ANI_TIME_DELAY) == false)
			return true;

		if (simon->GetState() == BACK && simon->animations[BACK]->IsOver(BACK_ANI_TIME_DELAY) == false)
			return true;

		if (simon->GetState() == HIT_STAIR_UP && simon->animations[HIT_STAIR_UP]->IsOver(HIT_ANI_TIME_DELAY) == false)
			return true;

		if (simon->GetState() == HIT_STAIR_DOWN && simon->animations[HIT_STAIR_DOWN]->IsOver(HIT_ANI_TIME_DELAY) == false)
			return true;
	}
	else
	{
		// Đặt lại biến chờ render animation
		isNeedToWaitingAnimation = true;

		// Để tránh việc ở frame tiếp theo rơi vào trạng thái chờ render animation 
		// (vì animation == 200ms, một frame ~ 30ms nên sẽ phải bị chờ dù cho có biến = false),
		// do đó cần reset lại animation start time về 0
		simon->animations[STAIR_UP]->SetAniStartTime(0);
		simon->animations[STAIR_DOWN]->SetAniStartTime(0);
	}

	return false;
}

bool Input::CanProcessKeyboard()
{
	if (scene->IsMovingCamera() == true)
		return false;

	if (scene->isGamePause == true)
		return false;

	if (simon->GetState() == DEAD)
		return false;

	if (simon->isAutoWalk == true)
		return false;

	if (AnimationDelay() == true)
		return false;

	return true;
}

void Input::KeyState(BYTE *state)
{
	simon = scene->GetSimon();

	if (CanProcessKeyboard() == false)
		return;

	// nếu simon đang nhảy và chưa chạm đất
	if ((simon->GetState() == JUMP || simon->GetState() == STAND)
		&& simon->isTouchGround == false)
		return;

	// Xét trạng thái phím
	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (StairCollisionsDetection() == true && simon->isStandOnStair == true)
		{
			if (simon->stairDirection == 1) // cầu thang trái dưới - phải trên
				Simon_Stair_Up();
			else
				Simon_Stair_Down();

			return;
		}

		Simon_Walk_Right();
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (StairCollisionsDetection() == true && simon->isStandOnStair == true)
		{
			if (simon->stairDirection == 1) // cầu thang trái dưới - phải trên
				Simon_Stair_Down();
			else
				Simon_Stair_Up();

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

		if (simon->isTouchGround == false || simon->isFalling == true)
		{
			simon->SetState(STAND);
			return;
		}

		simon->SetState(SIT);
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
		if (scene->GetIDScene() == INTRO_SCREEN)
		{
			scene->ResetGame();
			scene->Init(SCENE_1);
			return;
		}

		simon->isHitSubWeapons = false;

		if (StairCollisionsDetection() == true)
		{
			if (Simon_Stair_Stand() == true)
				return;
		}

		simon->SetState(STAND);
	}
}

void Input::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_PAUSE)						// Pause game
	{
		scene->isGamePause = !(scene->isGamePause);
		return;
	}

	if (scene->isGameOver == true)
	{
		if (KeyCode == DIK_UP || KeyCode == DIK_DOWN)
			scene->chooseToPlayAgain = (scene->chooseToPlayAgain + 1) % 2;
		else if (KeyCode == DIK_Z)
		{
			if (scene->chooseToPlayAgain == 0)		// Continue game
			{
				scene->ResetGame();
				scene->Init(SCENE_1);
			}
			else
			{
				HWND hWnd = GetActiveWindow();		// End game
				DestroyWindow(hWnd);
			}
		}

		return;
	}
	
	if (scene->GetIDScene() == TITLE_SCREEN)		// nhấn phím bất kì từ màn hình Title Screen
	{
		scene->Init(INTRO_SCREEN);
		return;
	}

	if (CanProcessKeyboard() == false)
		return;

	switch (KeyCode)
	{
	case DIK_0:
		simon->SetSubWeapon(WEAPONS_STOP_WATCH);
		break;
	case DIK_1:
		simon->SetSubWeapon(WEAPONS_DAGGER);
		break;
	case DIK_2:
		simon->SetSubWeapon(WEAPONS_AXE);
		break;
	case DIK_3:
		simon->SetSubWeapon(WEAPONS_HOLY_WATER);
		break;
	case DIK_4:
		simon->SetSubWeapon(WEAPONS_BOOMERANG);
		break;
	case DIK_5:
		simon->isGotCrossItem = true;
		break;
	case DIK_6:
		simon->isGotDoubleShotItem = true;
		break;
	case DIK_7:
		simon->isGotTripleShotItem = true;
		break;
	case DIK_8:
		simon->invisibilityTimer->Start();
		break;
	case DIK_Q:
		scene->Init(SCENE_1);
		scene->SetGameState(GAMESTATE_1);
		break;
	case DIK_W:
		scene->Init(SCENE_2);
		scene->SetGameState(GAMESTATE_2_1);
		break;
	case DIK_E:
		scene->Init(SCENE_2);
		scene->SetGameState(GAMESTATE_2_2);
		break;
	case DIK_R:
		scene->Init(SCENE_2);
		scene->SetGameState(GAMESTATE_2_3);
		break;
	case DIK_T:
		scene->Init(SCENE_3);
		scene->SetGameState(GAMESTATE_3_1);
		break;
	case DIK_Y:
		scene->Init(SCENE_3);
		scene->SetGameState(GAMESTATE_3_2);
		break;
	case DIK_A:
		if (game->IsKeyDown(DIK_UP))
			Simon_Hit_SubWeapon();
		else
			Simon_Hit();
		break;
	case DIK_S:
		Simon_Hit_SubWeapon();
		break;
	case DIK_SPACE:
		Simon_Jump();
		break;
	case DIK_L:
		scene->ResetGame();
		scene->Init(SCENE_1);
		break;
	default:
		break;
	}
}

void Input::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void Input::Simon_Walk_Left()
{
	simon->SetOrientation(-1);
	simon->SetState(WALK);
}

void Input::Simon_Walk_Right()
{
	simon->SetOrientation(1);
	simon->SetState(WALK);
}

void Input::Simon_Jump()
{
	if (simon->isTouchGround == false || simon->IsHit() == true)
		return;

	simon->SetState(JUMP);
}

void Input::Simon_Hit()
{
	if (simon->IsHit() == true)
		return;

	if (simon->isFalling == true)
		return;

	if (simon->GetState() == STAND || simon->GetState() == JUMP)
	{
		simon->SetState(HIT_STAND);
	}
	else if (simon->GetState() == SIT)
	{
		simon->SetState(HIT_SIT);
	}
	else if (simon->GetState() == STAIR_UP)
	{
		simon->SetState(HIT_STAIR_UP);
	}
	else if (simon->GetState() == STAIR_DOWN)
	{
		simon->SetState(HIT_STAIR_DOWN);
	}
}

void Input::Simon_Hit_SubWeapon()
{
	if (simon->isFalling == true)
		return;

	vector<SubWeapon*> * weaponlist = scene->GetWeaponList();
	SubWeapon * weapon;

	if (simon->GetSubWeapon() == -1 || simon->GetEnergy() == 0) // không có vũ khí hoặc enery = 0
		return;

	if (simon->GetSubWeapon() == STOP_WATCH)
	{
		if (simon->GetEnergy() < 5)
			return;
		if (scene->stopWatchTimer->IsTimeUp() == false) // đang sử dụng stop watch
			return;

		weaponlist->at(0)->SetEnable(false);
	}

	if (weaponlist->at(0)->IsEnable() == false)
		weapon = weaponlist->at(0);
	else if (weaponlist->at(1)->IsEnable() == false && (scene->doubleShotTimer->IsTimeUp() == false || scene->tripleShotTimer->IsTimeUp() == false))
		weapon = weaponlist->at(1);
	else if (weaponlist->at(2)->IsEnable() == false && scene->tripleShotTimer->IsTimeUp() == false)
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
			scene->stopWatchTimer->Start();
		}
		else
		{
			simon->LoseEnergy(1);
			simon->isHitSubWeapons = true;
			Simon_Hit();
		}
	}
}

void Input::Simon_Stair_Down()
{
	int stairDirection = simon->stairDirection;

	if (simon->canMoveDownStair == false)
	{
		if (simon->isStandOnStair == true)
			simon->SetState(STAND);
		else
			simon->SetState(SIT);

		return;
	}

	// Auto-walk của Simon đi đến đúng đầu cầu thang rồi mới bước xuống
	if (simon->isStandOnStair == false)
	{
		float stair_x, simon_x, temp_y;

		simon->stairCollided->GetPosition(stair_x, temp_y);
		simon->GetPosition(simon_x, temp_y);

		if (stairDirection == -1) stair_x -= 28.0f;

		if (stair_x < simon_x) simon->SetOrientation(-1);
		else if (stair_x > simon_x) simon->SetOrientation(1);
		else return;

		simon->SetState(WALK);
		simon->vy = 0;
		simon->AutoWalk(stair_x - simon_x, STAIR_DOWN, -stairDirection);
		simon->isStandOnStair = true;

		return;
	}
	else
	{
		simon->SetOrientation(-simon->stairDirection);
		simon->SetState(STAIR_DOWN);
	}

	return;
}

void Input::Simon_Stair_Up()
{
	int stairDirection = simon->stairDirection;

	if (simon->canMoveUpStair == false)
	{
		if (simon->isStandOnStair == true)
		{
			int nx = simon->stairDirection;
			simon->SetOrientation(nx);
			simon->SetState(STAIR_UP);
			simon->AutoWalk(14 * nx, STAND, nx);
		}

		return;
	}

	// Auto-walk của Simon đi đến đúng chân cầu thang rồi mới bước lên
	if (simon->isStandOnStair == false)
	{
		float stair_x, simon_x, temp_y;

		simon->stairCollided->GetPosition(stair_x, temp_y);
		simon->GetPosition(simon_x, temp_y);

		if (stairDirection == 1) stair_x -= 31.0f;
		else stair_x += 5.0f;

		if (stair_x < simon_x) simon->SetOrientation(-1);
		else if (stair_x > simon_x)  simon->SetOrientation(1);
		else return;

		simon->SetState(WALK);
		simon->vy = 0;
		simon->AutoWalk(stair_x - simon_x, STAIR_UP, stairDirection);
		simon->isStandOnStair = true;

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
		simon->animations[STAIR_UP]->Reset();
		simon->animations[STAIR_UP_INVISIBLE]->Reset();
		simon->animations[STAIR_DOWN]->Reset();
		simon->animations[STAIR_DOWN_INVISIBLE]->Reset();

		return true;
	}

	return false;
}

bool Input::StairCollisionsDetection()
{
	return simon->CheckCollisionWithStair(scene->GetListStairs());
}
