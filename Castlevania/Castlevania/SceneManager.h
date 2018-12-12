#pragma once

#include "Grid.h"
#include "Game.h"
#include "GameObject.h"
#include "Candle.h"
#include "TileMap.h"
#include "Ground.h"
#include "Simon.h"
#include "Whip.h"
#include "SubWeapon.h"
#include "Stair.h"
#include "Door.h"
#include "Zombie.h"
#include "BlackLeopard.h"
#include "VampireBat.h"
#include "FishMan.h"
#include "FireBall.h"
#include "Bubbles.h"
#include "Items.h"
#include "Boss.h"
#include "ChangeSceneObject.h"


class SceneManager
{
	int IDScene;
	bool isBossFighting = false;

	Game * game;
	Grid * grid;
	Unit * unit;

	vector<Unit*> listUnits;
	vector<LPGAMEOBJECT> listObjects;
	vector<LPGAMEOBJECT> listItems;
	vector<LPGAMEOBJECT> listStairs;

	Simon * simon = new Simon();
	Candle * candle = new Candle();
	Ground * ground = new Ground();
	Items * item = new Items();
	Whip * whip = new Whip();
	Effect * effect = new Effect();
	SubWeapon * weapon = new SubWeapon();
	Stair * stair = new Stair();
	Door * door = new Door();
	Zombie * zombie = new Zombie();
	BlackLeopard * leopard = new BlackLeopard();
	VampireBat * bat = new VampireBat();
	FishMan * fishman = new FishMan();
	FireBall * fireball = new FireBall();
	Bubble * bubble = new Bubble();
	Boss * boss = new Boss();

	ChangeSceneObject * changeScene;

	TileMaps * tilemaps = TileMaps::GetInstance();
	Textures * textures = Textures::GetInstance();
	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	

	vector<LPCHANGESCENEOBJ> listChangeSceneObjs;
	vector<LPGAMEOBJECT> listStaticObjectsToRender;
	vector<LPGAMEOBJECT> listMovingObjectsToRender;

	bool isSetSimonAutoWalk = false;
	bool isMovingCamera = false;
	int countDxCamera = 0;

	bool isUsingStopWatch = false; // xác định xem là có đang dùng stopwatch hay không
	int stopWatchCounter = 0;

public:
	SceneManager(Game * game, int idScene);
	~SceneManager();

	void LoadResources();		// load all sprites and tilemaps
	void LoadObjectsFromFile(LPCWSTR FilePath);		// load all objects (position, state, isenable) from file and save to vector Objects
	void CreateListChangeSceneObjects();

	void GetObjectFromGrid();

	void Update(DWORD dt);
	void Render();
	void UpdateCameraPosition();
	void UpdateGrid();

	void SetDropItems(LPGAMEOBJECT object);
	void SetInactivationByPosition();  // Nếu object ra khỏi toạ độ viewport thì set unable / inactive

	void ChangeScene(int scene);
	int GetIDScene() { return this->IDScene; }

	Simon * GetSimon() { return this->simon; }
	Boss * GetBoss() { return this->boss; }
	SubWeapon * GetWeapon() { return this->weapon; }
	vector<LPGAMEOBJECT> * GetListStairs() { return &(this->listStairs); }

	void SetWeapon(SubWeapon * x) { this->weapon = x; }

	bool IsUsingStopWatch() { return isUsingStopWatch; }
	void StartStopWatch() { isUsingStopWatch = true; stopWatchCounter = GetTickCount(); }

	// Các hàm update con
	void Simon_Update(DWORD dt);
	void Whip_Update(DWORD dt);
	void Weapon_Update(DWORD dt);
	void Item_Update(DWORD dt, LPGAMEOBJECT &object);
	void Zombie_Update(DWORD dt, LPGAMEOBJECT &object);
	void BlackLeopard_Update(DWORD dt, LPGAMEOBJECT &object);
	void VampireBat_Update(DWORD dt, LPGAMEOBJECT &object);
	void FishMan_Update(DWORD dt, LPGAMEOBJECT &object);
	void Boss_Update(DWORD dt, LPGAMEOBJECT &object);
};

