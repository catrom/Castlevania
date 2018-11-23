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
	if (scene->GetSimon()->GetState() == POWER && scene->GetSimon()->animations[POWER]->IsOver(450) == false)
		return;

	if (scene->GetSimon()->GetState() == HIT && scene->GetSimon()->animations[HIT]->IsOver(300) == false)
		return;

	// nếu simon đang nhảy và chưa chạm đất, tiếp tục render trạng thái nhảy
	if (scene->GetSimon()->GetState() == JUMP && scene->GetSimon()->IsTouchGround() == false)
		return;

	// nếu simon đang quất roi và animation chưa được render hết thì tiếp tục render

	if (scene->GetSimon()->GetState() == HIT_STAND && scene->GetSimon()->animations[HIT_STAND]->IsOver(300) == false)
		return;

	if (scene->GetSimon()->GetState() == HIT_SIT && scene->GetSimon()->animations[HIT_SIT]->IsOver(300) == false)
		return;


	if (game->IsKeyDown(DIK_RIGHT))
	{
		scene->GetSimon()->nx = 1;
		scene->GetSimon()->SetState(WALK);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		scene->GetSimon()->nx = -1;
		scene->GetSimon()->SetState(WALK);
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		scene->GetSimon()->SetState(SIT);
	}
	else
	{
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
		if (scene->GetSimon()->isPowered == false)
			return;
		if (scene->GetSimon()->GetState() == STAND || scene->GetSimon()->GetState() == JUMP)
		{
			float sx, sy;
			scene->GetSimon()->GetPosition(sx, sy);
			scene->GetDagger()->SetPosition(sx, sy + 10);
			scene->GetDagger()->SetOrientation(scene->GetSimon()->GetOrientation());
			scene->GetDagger()->isEnable = true;
			scene->GetSimon()->SetState(HIT);
		}
	default:
		break;
	}
}

void Input::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}
