#include "Input.h"



Input::Input(Game * game, Simon * simon)
{
	this->game = game;
	this->simon = simon;
}

Input::~Input()
{
}

void Input::KeyState(BYTE *state)
{
	if (simon->GetState() == POWER && simon->animations[POWER]->IsOver(450) == false)
		return;

	if (simon->GetState() == HIT && simon->animations[HIT]->IsOver(300) == false)
		return;

	// nếu simon đang nhảy và chưa chạm đất, tiếp tục render trạng thái nhảy
	if (simon->GetState() == JUMP && simon->IsTouchGround() == false)
		return;

	// nếu simon đang quất roi và animation chưa được render hết thì tiếp tục render

	if (simon->GetState() == HIT_STAND && simon->animations[HIT_STAND]->IsOver(300) == false)
		return;

	if (simon->GetState() == HIT_SIT && simon->animations[HIT_SIT]->IsOver(300) == false)
		return;


	if (game->IsKeyDown(DIK_RIGHT))
	{
		simon->nx = 1;
		simon->SetState(WALK);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		simon->nx = -1;
		simon->SetState(WALK);
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		simon->SetState(SIT);
	}
	else
	{
		simon->SetState(STAND);
	}
}

void Input::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	switch (KeyCode)
	{
	case DIK_SPACE:
		if (simon->GetState() == JUMP || simon->GetState() == HIT_STAND || simon->GetState() == HIT_SIT)
			return;
		simon->SetState(JUMP);
		break;
	case DIK_Z:
		if ((simon->GetState() == HIT_STAND || simon->GetState() == HIT_SIT))
			return;
		if (simon->GetState() == STAND || simon->GetState() == JUMP)
		{
			simon->SetState(HIT_STAND);
		}
		else if (simon->GetState() == SIT)
		{
			simon->SetState(HIT_SIT);
		}
		break;
	case DIK_X:
		if (simon->isPowered == false)
			return;
		if (simon->GetState() == STAND)
		{
			float sx, sy;
			simon->GetPosition(sx, sy);
			//dagger->SetPosition(sx, sy + 10);
			//dagger->SetOrientation(simon->GetOrientation());
			//dagger->isEnable = true;
			simon->SetState(HIT);
		}
	default:
		break;
	}
}

void Input::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}
