#pragma once

#include "Game.h"
#include "Simon.h"

class Input : public KeyEventHandler
{
	Game * game;
	Simon * simon;
public:
	Input(Game * game, Simon * simon);
	~Input();

	virtual void KeyState(BYTE *state);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

