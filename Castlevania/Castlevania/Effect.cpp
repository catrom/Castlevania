#include "Effect.h"

void Effect::LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations)
{
	textures->Add(ID_TEX_EFFECT, FILEPATH_TEX_EFFECT, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texEffect = textures->Get(ID_TEX_EFFECT);

	sprites->Add(50001, 0, 0, 32, 64, texEffect); 
	sprites->Add(50002, 32, 0, 64, 64, texEffect);
	sprites->Add(50003, 64, 0, 96, 64, texEffect);
	sprites->Add(50004, 0, 0, 0, 0, texEffect);

	LPANIMATION ani;

	ani = new Animation(50);
	ani->Add(50001);
	ani->Add(50002);
	ani->Add(50003);
	ani->Add(50004);
	animations->Add(EFFECT_ANI, ani);

}

void Effect::Render()
{
	animations[state]->Render(nx, x, y);
}
