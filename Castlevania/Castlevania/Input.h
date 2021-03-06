#pragma once

#include "Game.h"
#include "Simon.h"
#include "SceneManager.h"

class Input : public KeyEventHandler
{
	Game * game;
	SceneManager * scene;
	Simon * simon;
	bool isNeedToWaitingAnimation = true;

public:
	Input(Game * game, SceneManager * scene);
	~Input();

	bool AnimationDelay();
	bool CanProcessKeyboard();

	virtual void KeyState(BYTE *state);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	///////

	void Simon_Walk_Left();
	void Simon_Walk_Right();
	void Simon_Jump();
	void Simon_Hit();
	void Simon_Hit_SubWeapon();
	void Simon_Stair_Down();
	void Simon_Stair_Up();
	bool Simon_Stair_Stand();

	bool StairCollisionsDetection();
};

