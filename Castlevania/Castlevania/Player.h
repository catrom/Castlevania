#pragma once

#include "d3dx9.h"
#include "Define.h"
#include "Textures.h"
#include "Sprites.h"
#include "Simon.h"
#include "SceneManager.h"

#include <vector>
#include <string>

using namespace std;

class Player
{
private:
	SceneManager * scenes;
	Game * game;
	Simon * simon;
	Boss * boss;

	ID3DXFont * font;
	string information;

	vector<LPSPRITE> playerHP;
	vector<LPSPRITE> enemyHP;
	vector<LPSPRITE> loseHP;

	Sprite * subWeaponBox;
	vector<LPSPRITE> subWeaponList;
	
	int score;
	int time;
	int scene;
	int item;
	int energy;
	int life;
	int subWeapon;
	int simonHP;
	int bossHP;

public:
	Player(SceneManager * scenes, Game * game);
	~Player();

	void Init();
	void Update(DWORD dt, bool stopwatch);
	void Render();
};

