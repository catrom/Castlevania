#pragma once

#include "Game.h"
#include "GameObject.h"
#include "Candle.h"
#include "TileMap.h"
#include "Ground.h"
#include "Simon.h"
#include "Whip.h"
#include "SubWeapon.h"


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

	TileMaps * tilemaps = TileMaps::GetInstance();
	Textures * textures = Textures::GetInstance();
	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();

	vector<LPGAMEOBJECT> Objects;

public:
	SceneManager(Game * game, int idScene);
	~SceneManager();

	void LoadResources();		// load all sprites and tilemaps
	void LoadObjectsFromFile(LPCWSTR FilePath);		// load all objects (position, state, isenable) from file and save to vector Objects

	virtual void Update(DWORD dt);
	virtual void Render();

	void ChangeScene(int scene);
	int GetIDScene() { return this->IDScene; }

	Simon * GetSimon() { return this->simon; }
	SubWeapon * GetWeapon() { return this->weapon; }
};

