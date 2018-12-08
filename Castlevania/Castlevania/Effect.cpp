#include "Effect.h"


void Effect::LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations)
{
	textures->Add(ID_TEX_EFFECT, FILEPATH_TEX_EFFECT, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texEffect = textures->Get(ID_TEX_EFFECT);

	sprites->Add(50001, 0, 0, 32, 60, texEffect); 
	sprites->Add(50002, 32, 0, 64, 60, texEffect);
	sprites->Add(50003, 64, 0, 96, 60, texEffect);
	sprites->Add(50004, 96, 0, 146, 60, texEffect);
	sprites->Add(50005, 146, 0, 196, 60, texEffect);
	sprites->Add(50006, 196, 0, 246, 60, texEffect);

	LPANIMATION ani;

	ani = new Animation(50);
	ani->Add(50001);
	ani->Add(50002);
	ani->Add(50003);
	animations->Add(EFFECT_ANI, ani);

	ani = new Animation(50);
	ani->Add(50004);
	ani->Add(50005);
	ani->Add(50006);
	animations->Add(EFFECT_2_ANI, ani);
}

