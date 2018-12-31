#pragma once

#include "Textures.h"
#include "Sprites.h"

class TitleScreen
{
	LPDIRECT3DTEXTURE9 view = Textures::GetInstance()->Get(ID_TEX_TITLESCREEN);
	Animation * bird = Animations::GetInstance()->Get("title_ani");

public:
	TitleScreen();
	~TitleScreen();

	void Render();
};

