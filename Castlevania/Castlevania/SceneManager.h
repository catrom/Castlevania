#pragma once

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
#include "ChangeSceneObject.h"


class SceneManager
{
	int IDScene;

	Game * game;

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

	ChangeSceneObject * changeScene;

	TileMaps * tilemaps = TileMaps::GetInstance();
	Textures * textures = Textures::GetInstance();
	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();

	vector<LPGAMEOBJECT> Objects;
	vector<LPGAMEOBJECT> listCandles;
	vector<LPGAMEOBJECT> listStairs;
	vector<LPGAMEOBJECT> listGrounds;
	vector<LPGAMEOBJECT> listItems;
	vector<LPGAMEOBJECT> listDoors;
	vector<LPGAMEOBJECT> listZombies;
	vector<LPGAMEOBJECT> listBlackLeopards;
	vector<LPGAMEOBJECT> listVampireBats;
	vector<LPGAMEOBJECT> listFishMans;
	vector<LPGAMEOBJECT> listFireBalls;

	vector<LPCHANGESCENEOBJ> listChangeSceneObjs;

	bool isSetSimonAutoWalk = false;
	bool isMovingCamera = false;
	int countDxCamera = 0;

public:
	SceneManager(Game * game, int idScene);
	~SceneManager();

	void LoadResources();		// load all sprites and tilemaps
	void LoadObjectsFromFile(LPCWSTR FilePath);		// load all objects (position, state, isenable) from file and save to vector Objects
	void CreateListChangeSceneObjects();

	virtual void Update(DWORD dt);
	virtual void Render();

	void SetDropItems(LPGAMEOBJECT object);
	void SetInactivationByPosition();  // Nếu object ra khỏi toạ độ viewport thì set unable / inactive

	void ChangeScene(int scene);
	int GetIDScene() { return this->IDScene; }

	Simon * GetSimon() { return this->simon; }
	SubWeapon * GetWeapon() { return this->weapon; }
	vector<LPGAMEOBJECT> * GetListStairs() { return &(this->listStairs); }
};

