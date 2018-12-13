#include "Player.h"



Player::Player(SceneManager * scenes, Game * game)
{
	this->scenes = scenes;
	this->game = game;
	this->simon = scenes->GetSimon();
	this->boss = scenes->GetBoss();

	time = 0;
}


Player::~Player()
{
}

void Player::Init()
{
	// Khởi tạo list máu của Simon và Enemy
	Textures * textures = Textures::GetInstance();
	textures->Add(ID_TEX_HP, FILEPATH_TEX_HP, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_RECT, FILEPATH_TEX_RECT, D3DCOLOR_XRGB(255, 255, 255)); 

	LPDIRECT3DTEXTURE9 texHP = textures->Get(ID_TEX_HP);
	LPDIRECT3DTEXTURE9 texRect = textures->Get(ID_TEX_RECT);

	for (int i = 0; i < 16; i++)
	{
		Sprite * player = new Sprite(100, 0, 0, 8, 15, texHP);
		playerHP.push_back(player);

		Sprite * lose = new Sprite(101, 8, 0, 16, 15, texHP);
		loseHP.push_back(lose);

		Sprite * enemy = new Sprite(102, 16, 0, 24, 15, texHP);
		enemyHP.push_back(enemy);
	}

	// Khởi tạo list subweapon để render trong subweaponbox
	subWeaponBox = new Sprite(110, 0, 0, 95, 40, texRect);

	Sprites * sprites = Sprites::GetInstance();
	subWeaponList.push_back(sprites->Get(80001)); // ID bên class Items
	subWeaponList.push_back(sprites->Get(80002));
	subWeaponList.push_back(sprites->Get(80003));
	subWeaponList.push_back(sprites->Get(80004));
	subWeaponList.push_back(sprites->Get(80005));

	// Khởi tạo list item (double shot, triple shot)
	itemList.push_back(sprites->Get(80014));
	itemList.push_back(sprites->Get(80015));

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
	score = simon->GetScore();
	energy = simon->GetEnergy();
	life = simon->GetLife();
	subWeapon = simon->GetSubWeapon();
	scene = scenes->GetIDScene() + 1; // (based 1)
	simonHP = simon->GetHP();
	bossHP = boss->GetHP();

	if (scenes->IsDoubleShotEffect()) item = 0; // double shot
	else if (scenes->IsTripleShotEffect()) item = 1; // trip shot
	else item = -1;
	
	if (stopwatch == false) time += dt; // khi sử dụng stop watch thì không đếm thời gian

	int remainTime = DEFAULT_TIME_PLAY - time / 1000;

	string score_str = to_string(score);
	while (score_str.length() < 6) score_str = "0" + score_str;

	string time_str = to_string(remainTime);
	while (time_str.length() < 4) time_str = "0" + time_str;

	string scene_str = to_string(scene);
	while (scene_str.length() < 2) scene_str = "0" + scene_str;

	string energy_str = to_string(energy);
	while (energy_str.length() < 2) energy_str = "0" + energy_str;

	string life_str = to_string(life);
	while (life_str.length() < 2) life_str = "0" + life_str;

	// update information
	information = "SCORE-" + score_str + " TIME " + time_str + " SCENE " + scene_str + "\n";
	information += "PLAYER                  -" + energy_str + "\n";
	information += "ENEMY                   -" + life_str + "\n";
}

void Player::Render()
{
	RECT rect;
	SetRect(&rect, 0, 15, SCREEN_WIDTH, 80);

	if (font != NULL)
	{
		font->DrawTextA(NULL, information.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
	}

	// draw subWeaponBox
	subWeaponBox->Draw(0, -1, 288, 32);

	if (subWeapon != -1) // simon get subweapon
	{
		subWeaponList[subWeapon]->Draw(0, -1, 305, 40);
	}

	// draw item

	if (item != -1)
	{
		itemList[item]->Draw(0, -1, 450, 38);
	}

	for (int i = 0; i < simonHP; i++)
	{
		playerHP[i]->Draw(0, -1, 105 + i * 9, 31);
	}

	for (int i = simonHP; i < 16; i++)
	{
		loseHP[i]->Draw(0, -1, 105 + i * 9, 31);
	}

	for (int i = 0; i < bossHP; i++)
	{
		enemyHP[i]->Draw(0, -1, 106 + i * 9, 47);
	}

	for (int i = bossHP; i < 16; i++)
	{
		loseHP[i]->Draw(0, -1, 106 + i * 9, 47);
	}
}


