#pragma once

#include "Game.h"
#include "Simon.h"
#include "SceneManager.h"

class Input : public KeyEventHandler
{
	Game * game;
	SceneManager * scene;
	bool isNeedToWaitingAnimation = true;

public:
	Input(Game * game, SceneManager * scene);
	~Input();

	virtual void KeyState(BYTE *state);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	///////

	void Simon_Walk_Left();
	void Simon_Walk_Right();
	void Simon_Jump();
	void Simon_Hit();
	void Simon_Hit_SubWeapon();
	bool Simon_Stair_Down();
	bool Simon_Stair_Up();
	bool Simon_Stair_Stand();

	bool StairCollisionsDetection();
};

