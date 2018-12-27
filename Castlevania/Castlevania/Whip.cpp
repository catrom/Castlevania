#include "Whip.h"
#include "Candle.h"
#include "Zombie.h"
#include "BlackLeopard.h"
#include "VampireBat.h"
#include "FishMan.h"
#include "FireBall.h"
#include "Boss.h"

Whip::Whip() : GameObject()
{
	AddAnimation(NORMAL_WHIP_ANI);
	AddAnimation(SHORT_CHAIN_ANI);
	AddAnimation(LONG_CHAIN_ANI);

	SetState(LONG_CHAIN);
}

void Whip::LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations)
{
	textures->Add(ID_TEX_WHIP, FILEPATH_TEX_WHIP, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texWhip = textures->Get(ID_TEX_WHIP);

	sprites->Add(20001, 0, 0, 240, 66, texWhip); // normal whip
	sprites->Add(20002, 240, 0, 480, 66, texWhip);
	sprites->Add(20003, 480, 0, 720, 66, texWhip);

	sprites->Add(20011, 0, 66, 240, 132, texWhip); // short chain
	sprites->Add(20012, 240, 66, 480, 132, texWhip);
	sprites->Add(20013, 480, 66, 720, 132, texWhip);

	sprites->Add(20021, 0, 132, 240, 198, texWhip); // long chain
	sprites->Add(20022, 240, 132, 480, 198, texWhip);
	sprites->Add(20023, 480, 132, 720, 198, texWhip);
	sprites->Add(20024, 0, 198, 240, 264, texWhip);
	sprites->Add(20025, 240, 198, 480, 264, texWhip);
	sprites->Add(20026, 480, 198, 720, 264, texWhip);
	sprites->Add(20027, 0, 264, 240, 330, texWhip);
	sprites->Add(20028, 240, 264, 480, 330, texWhip);
	sprites->Add(20029, 480, 264, 720, 330, texWhip);
	sprites->Add(20030, 0, 330, 240, 396, texWhip);
	sprites->Add(20031, 240, 330, 480, 396, texWhip);
	sprites->Add(20032, 480, 330, 720, 396, texWhip);

	LPANIMATION ani;

	ani = new Animation();
	ani->Add(20001);
	ani->Add(20002);
	ani->Add(20003);
	animations->Add(NORMAL_WHIP_ANI, ani);

	ani = new Animation();
	ani->Add(20011);
	ani->Add(20012);
	ani->Add(20013);
	animations->Add(SHORT_CHAIN_ANI, ani);

	ani = new Animation(25);
	ani->Add(20021);
	ani->Add(20022);
	ani->Add(20023);
	ani->Add(20024);
	ani->Add(20025);
	ani->Add(20026);
	ani->Add(20027);
	ani->Add(20028);
	ani->Add(20029);
	ani->Add(20030);
	ani->Add(20031);
	ani->Add(20032);
	animations->Add(LONG_CHAIN_ANI, ani);
}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, bool stopMovement)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);

		if (dynamic_cast<Candle*>(obj))
		{
			Candle * e = dynamic_cast<Candle*> (obj);

			float left, top, right, bottom;

			e->GetBoundingBox(left, top, right, bottom);

			if (CheckCollision(left, top, right, bottom) == true) // va chạm giữa roi và nến
			{
				e->SetState(CANDLE_DESTROYED);
				targetTypeHit = CANDLE;
				sparkCoord.push_back({ left, top });
			}
		}
		else if (dynamic_cast<FireBall*>(obj))
		{
			FireBall * e = dynamic_cast<FireBall*> (obj);

			float left, top, right, bottom;

			e->GetBoundingBox(left, top, right, bottom);

			if (CheckCollision(left, top, right, bottom) == true) // va chạm giữa roi và boss
			{
				e->SetEnable(false);
				targetTypeHit = FIREBALL;
				sparkCoord.push_back({ left, top });
			}
		}
		else if (dynamic_cast<Zombie*>(obj))
		{
			Zombie * e = dynamic_cast<Zombie*> (obj);

			float left, top, right, bottom;

			e->GetBoundingBox(left, top, right, bottom);

			if (CheckCollision(left, top, right, bottom) == true) // va chạm giữa roi và zombie
			{
				e->LoseHP(1);
				targetTypeHit = ZOMBIE;

				if (e->GetState() == ZOMBIE_DESTROYED)
				{
					scoreReceived += e->GetScore();
					sparkCoord.push_back({ left, top });
				}
			}
		}
		else if (dynamic_cast<BlackLeopard*>(obj))
		{
			BlackLeopard * e = dynamic_cast<BlackLeopard*> (obj);

			float left, top, right, bottom;

			e->GetBoundingBox(left, top, right, bottom);

			if (CheckCollision(left, top, right, bottom) == true) // va chạm giữa roi và black leopard
			{
				e->LoseHP(1);
				targetTypeHit = BLACK_LEOPARD;

				if (e->GetState() == BLACK_LEOPARD_DESTROYED)
				{
					scoreReceived += e->GetScore();
					sparkCoord.push_back({ left, top });
				}
			}
		}
		else if (dynamic_cast<VampireBat*>(obj))
		{
			VampireBat * e = dynamic_cast<VampireBat*> (obj);

			float left, top, right, bottom;

			e->GetBoundingBox(left, top, right, bottom);

			if (CheckCollision(left, top, right, bottom) == true) // va chạm giữa roi và vampire bat
			{
				e->LoseHP(1);
				targetTypeHit = VAMPIRE_BAT;

				if (e->GetState() == VAMPIRE_BAT_DESTROYED)
				{
					scoreReceived += e->GetScore();
					sparkCoord.push_back({ left, top });
				}
			}
		}
		else if (dynamic_cast<FishMan*>(obj))
		{
			FishMan * e = dynamic_cast<FishMan*> (obj);

			float left, top, right, bottom;

			e->GetBoundingBox(left, top, right, bottom);

			if (CheckCollision(left, top, right, bottom) == true) // va chạm giữa roi và fishman
			{
				e->LoseHP(1);
				targetTypeHit = FISHMAN;

				if (e->GetState() == FISHMAN_DESTROYED)
				{
					scoreReceived += e->GetScore();
					sparkCoord.push_back({ left, top });
				}
			}
		}
		else if (dynamic_cast<Boss*>(obj))
		{
			Boss * e = dynamic_cast<Boss*> (obj);

			float left, top, right, bottom;

			e->GetBoundingBox(left, top, right, bottom);

			if (CheckCollision(left, top, right, bottom) == true) // va chạm giữa roi và boss
			{
				e->LoseHP(1);
				targetTypeHit = BOSS;
				sparkCoord.push_back({ left, top });

				if (e->GetState() == BOSS_DESTROYED)
					scoreReceived += e->GetScore();
			}
		}
	}
}

void Whip::Render(int currentID)
{
	RenderSpark();

	if (currentID >= 0)
		animations[state]->RenderByID(currentID, nx, x, y);
}

void Whip::RenderSpark()
{
	if (sparkCoord.size() > 0)
	{
		if (startTimeRenderSpark == 0)
			startTimeRenderSpark = GetTickCount();
		else if (GetTickCount() - startTimeRenderSpark > SPARK_ANI_TIME_DELAY)
		{
			startTimeRenderSpark = 0;
			sparkCoord.clear();
		}

		for (auto coord : sparkCoord)
			spark->Render(1, -1, coord[0], coord[1]);
	}
}

void Whip::SetWhipPosition(D3DXVECTOR3 simonPositon, bool isStand)
{
	simonPositon.x -= 90;
	if (isStand == false)
		simonPositon.y += 15;

	SetPosition(simonPositon.x, simonPositon.y);
}

bool Whip::CheckCollision(float obj_left, float obj_top, float obj_right, float obj_bottom)
{
	float whip_left,
		whip_top,
		whip_right,
		whip_bottom;

	GetBoundingBox(whip_left, whip_top, whip_right, whip_bottom);

	return GameObject::AABB(whip_left, whip_top, whip_right, whip_bottom, obj_left, obj_top, obj_right, obj_bottom);
}

void Whip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	top = y + 15;
	bottom = top + WHIP_BBOX_HEIGHT;
	if (nx < 0)
	{
		if (state != LONG_CHAIN)
			left = x + 50;
		else left = x + 20;
	}
	else if (nx > 0)
	{
		if (state != LONG_CHAIN)
			left = (240 - 50) - WHIP_BBOX_WIDTH + x;
		else left = (240 - 20) - LONG_CHAIN_BBOX_WIDTH + x;
	}

	if (state != LONG_CHAIN)
		right = left + WHIP_BBOX_WIDTH;
	else  right = left + LONG_CHAIN_BBOX_WIDTH;
}

void Whip::GetActiveBoundingBox(float & left, float & top, float & right, float & bottom)
{
	GetBoundingBox(left, top, right, bottom);
}

void Whip::PowerUp()
{
	if (state == NORMAL_WHIP) SetState(SHORT_CHAIN);
	else if (state == SHORT_CHAIN) SetState(LONG_CHAIN);
}


