#include "Player.h"
#include "Define.h"


Player::Player(Game * game, SceneManager * scene)
{
	this->scene = scene;
	this->game = game;
}

Player::~Player()
{
}

void Player::Init()
{
	Sprites * sprites = Sprites::GetInstance();
	time = 0;

	for (int i = 0; i < 16; i++)
	{
		playerHP.push_back(sprites->Get("HP_player"));
		loseHP.push_back(sprites->Get("HP_lose"));
		enemyHP.push_back(sprites->Get("HP_enemy"));
	}

	// Tạo list subweapon để render trong subweaponbox
	subWeaponBox = sprites->Get("rect");

	subWeaponList.push_back(sprites->Get("item_stopwatch"));
	subWeaponList.push_back(sprites->Get("item_dagger"));
	subWeaponList.push_back(sprites->Get("item_axe"));
	subWeaponList.push_back(sprites->Get("item_holywater"));
	subWeaponList.push_back(sprites->Get("item_boomerang"));

	// Khởi tạo list item (double shot, triple shot)
	itemList.push_back(sprites->Get("item_doubleshot"));
	itemList.push_back(sprites->Get("item_tripleshot"));

	// Font
	font = NULL;
	AddFontResourceEx(FILEPATH_FONT, FR_PRIVATE, NULL);
	
	HRESULT hr = D3DXCreateFont(
		game->GetDirect3DDevice(), 16, 0, FW_NORMAL, 1, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, L"Press Start", &font);

	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] Create font failed\n");
		return;
	}

	information = "SCORE-000000 TIME 0000 SCENE 00\n";
	information +="PLAYER                  -00\n";
	information +="ENEMY                   -00\n";
}

void Player::Update(DWORD dt, bool stopwatch)
{
	this->simon = scene->GetSimon();
	this->boss = scene->GetBoss();

	// Lấy thông tin
	score = simon->GetScore();
	energy = simon->GetEnergy();
	life = simon->GetLife();
	subWeapon = simon->GetSubWeapon();
	id_scene = scene->GetIDScene() + 1;				// (based 1)
	simonHP = simon->GetHP();
	bossHP = boss->GetHP();

	if (scene->doubleShotTimer->IsTimeUp() == false) item = 0;		// double shot
	else if (scene->tripleShotTimer->IsTimeUp() == false) item = 1; // trip shot
	else item = -1;
	
	if (scene->isGameReset == true)
	{
		time = 0;
		scene->isGameReset = false;
	}

	if (stopwatch == false) time += dt;				// khi sử dụng stop watch thì không đếm thời gian
	int remainTime = DEFAULT_TIME_PLAY - time / CLOCKS_PER_SEC;

	if (remainTime <= 0)
	{
		remainTime = 0;

		if (simon->isTouchGround == true && simon->GetState() != DEAD)
			simon->SetState(DEAD);
	}
		

	// Chuẩn hoá chuỗi
	string score_str = to_string(score);
	while (score_str.length() < 6) score_str = "0" + score_str;

	string time_str = to_string(remainTime);
	while (time_str.length() < 4) time_str = "0" + time_str;

	string scene_str = to_string(id_scene);
	while (scene_str.length() < 2) scene_str = "0" + scene_str;

	string energy_str = to_string(energy);
	while (energy_str.length() < 2) energy_str = "0" + energy_str;

	string life_str = to_string(life);
	while (life_str.length() < 2) life_str = "0" + life_str;

	// 
	information = "SCORE-" + score_str + " TIME " + time_str + " SCENE " + scene_str + "\n";
	information += "PLAYER                  -" + energy_str + "\n";
	information += "ENEMY                   -" + life_str + "\n";
}

void Player::Render()
{
	RECT rect;
	SetRect(&rect, 0, 15, SCREEN_WIDTH, 80);

	if (font != NULL)
		font->DrawTextA(NULL, information.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));

	// draw subWeaponBox
	subWeaponBox->Draw(0, -1, 288, 32);

	if (subWeapon != -1)
		subWeaponList[subWeapon]->Draw(0, -1, 305, 38);

	// draw item
	if (item != -1)
		itemList[item]->Draw(0, -1, 450, 38);

	// player HP
	for (int i = 0; i < simonHP; i++)
		playerHP[i]->Draw(0, -1, 105 + i * 9, 31);

	for (int i = simonHP; i < 16; i++)
		loseHP[i]->Draw(0, -1, 105 + i * 9, 31);

	// enemy HP
	for (int i = 0; i < bossHP; i++)
		enemyHP[i]->Draw(0, -1, 106 + i * 9, 47);

	for (int i = bossHP; i < 16; i++)
		loseHP[i]->Draw(0, -1, 106 + i * 9, 47);
}


