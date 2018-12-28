#pragma once

#include "Simon.h"
#include "Bat.h"
#include "Cloud.h"

class IntroScene
{
	LPDIRECT3DTEXTURE9 view = Textures::GetInstance()->Get(ID_TEX_INTROSCREEN);
	vector<Bat*> bats;
	Cloud * cloud;

	Simon * simon;

public:
	IntroScene(Simon * simon);
	~IntroScene();

	void Update(DWORD dt);
	void Render();
};

