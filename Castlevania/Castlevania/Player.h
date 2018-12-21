#pragma once

#include "d3dx9.h"
#include "SceneManager.h"

#include <vector>
#include <string>

using namespace std;

/*
	Class hiển thị thông tin của người chơi.
*/
class Player
{
private:
	SceneManager * scene;
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
	vector<LPSPRITE> itemList;
	
	int score;
	int time;
	int id_scene;
	int item;
	int energy;
	int life;
	int subWeapon;
	int simonHP;
	int bossHP;

public:
	Player(Game * game, SceneManager * scene);
	~Player();

	void Init();
	void Update(DWORD dt, bool stopwatch);
	void Render();
};

