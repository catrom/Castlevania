#include "Effect.h"
#include "Define.h"

void Effect::LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations)
{
	textures->Add(ID_TEX_EFFECT, FILEPATH_TEX_EFFECT, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_SPARK, FILEPATH_TEX_SPARK, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texEffect = textures->Get(ID_TEX_EFFECT);

	sprites->Add("effect1_1", 0, 0, 32, 60, texEffect); 
	sprites->Add("effect1_2", 32, 0, 64, 60, texEffect);
	sprites->Add("effect1_3", 64, 0, 96, 60, texEffect);

	sprites->Add("effect2_1", 96, 0, 192, 60, texEffect);
	sprites->Add("effect2_2", 192, 0, 288, 60, texEffect);
	sprites->Add("effect2_3", 288, 0, 384, 60, texEffect);

	LPDIRECT3DTEXTURE9 texSpark = textures->Get(ID_TEX_SPARK);

	sprites->Add("spark", 0, 0, 16, 20, texSpark);

	LPANIMATION ani;

	ani = new Animation();
	ani->Add("effect1_1");
	ani->Add("effect1_2");
	ani->Add("effect1_3");
	animations->Add("effect1_ani", ani);

	ani = new Animation();
	ani->Add("effect2_1");
	ani->Add("effect2_2");
	ani->Add("effect2_3");
	animations->Add("effect2_ani", ani);

	ani = new Animation();
	ani->Add("spark");
	animations->Add("spark_ani", ani);
}

