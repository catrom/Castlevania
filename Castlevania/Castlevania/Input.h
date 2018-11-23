#pragma once

#include "Game.h"
#include "Simon.h"
#include "SceneManager.h"

class Input : public KeyEventHandler
{
	Game * game;
	SceneManager * scene;
public:
	Input(Game * game, SceneManager * scene);
	~Input();

	virtual void KeyState(BYTE *state);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

