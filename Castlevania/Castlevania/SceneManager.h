﻿#pragma once

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
#include "ChangeSceneObject.h"


class SceneManager
{
	int IDScene;

	Game * game;

	Simon * simon;
	Candle * candle;
	Ground * ground;
	Items * item;
	Whip * whip;
	Effect * effect;
	SubWeapon * weapon;
	Stair * stair;
	Door * door;
	Zombie * zombie;
	BlackLeopard * leopard;
	VampireBat * bat;

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

