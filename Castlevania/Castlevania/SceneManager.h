#pragma once

#include "Game.h"
#include "Grid.h"
#include "GameObject.h"
#include "Candle.h"
#include "TileMap.h"
#include "Ground.h"
#include "Effect.h"
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
#include "Water.h"
#include "ChangeSceneObject.h"
#include "Timer.h"

#include <map>
using namespace std;

class SceneManager
{
	int IDScene;

	Game * game;
	Grid * grid;
	Unit * unit;

	vector<Unit*> listUnits;
	vector<LPGAMEOBJECT> listObjects;
	vector<LPGAMEOBJECT> listItems;
	vector<LPGAMEOBJECT> listStairs;

	Boss * boss;
	Simon * simon;
	Whip * whip;
	SubWeapon * weapon;
	Water * water;

	TileMaps * tilemaps = TileMaps::GetInstance();
	Textures * textures = Textures::GetInstance();
	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	
	vector<LPGAMEOBJECT> listStaticObjectsToRender;
	vector<LPGAMEOBJECT> listMovingObjectsToRender;
	vector<SubWeapon*> weaponlist;		// dùng mảng để sử dụng double shot, triple shot

	bool isSetSimonAutoWalk = false;	//
	bool isMovingCamera1 = false;		
	bool isMovingCamera2 = false;
	int countDxCamera = 0;

	bool isBossFighting = false;
	bool isSimonDead = false;

public:
	Timer * stopWatchTimer = new Timer(WEAPONS_STOP_WATCH_TIME);
	Timer * simonDeadTimer = new Timer(SIMON_DEAD_TIME);
	Timer * crossEffectTimer = new Timer(ITEM_CROSS_EFFECT_TIME);
	Timer * doubleShotTimer = new Timer(ITEM_DOUBLE_SHOT_EFFECT_TIME);
	Timer * tripleShotTimer = new Timer(ITEM_TRIPLE_SHOT_EFFECT_TIME);

	SceneManager(Game * game);
	~SceneManager();

	bool isGameReset = false;

	void Init(int idScene);						// init simon position, camera position, grid..
	void LoadResources();						// load all sprites, textures and tilemaps
	void LoadObjectsFromFile(LPCWSTR FilePath);	// load all objects (position, state, isEnable) from file 

	void GetObjectFromGrid();
		
	void Update(DWORD dt);						
	void UpdateTimeCounter();					
	void UpdateCameraPosition();				
	void UpdateGrid();

	void Render();
	
	bool SimonWalkThroughDoor();				// Di chuyển camera -> Simon auto walk -> di chuyển camera

	int GetRandomItem();						// Random item cho object bị huỷ
	void SetDropItems();						// Xét rơi item cho các object bị huỷ	
	
	bool IsInViewport(LPGAMEOBJECT object);
	void SetInactivationByPosition();			// Nếu object ra khỏi vùng viewport thì set unable / inactive

	void ChangeScene();							// Chuyển đổi scene khi Simon va chạm với ChangeSceneObject

	void SetGameState(int state);				// Set vị trí của simon, camera theo id state
	void ResetGame();							// Reset lại trạng thái của game (map, simon...) sau khi simon chết

	// Get, Set
	int GetIDScene() { return this->IDScene; }
	Simon * GetSimon() { return this->simon; }
	Boss * GetBoss() { return this->boss; }
	vector<SubWeapon*> * GetWeaponList() { return &weaponlist; }
	vector<LPGAMEOBJECT> * GetListStairs() { return &(listStairs); }

	bool IsMovingCamera() { return isMovingCamera1 || isMovingCamera2; }

	// Item Effect
	void CrossEffect();
	void DoubleShotEffect();
	void TripleShotEffect();

	// Các hàm con của hàm Update()
	void Simon_Update(DWORD dt);
	void Whip_Update(DWORD dt);
	void Weapon_Update(DWORD dt, int index);  
	void Item_Update(DWORD dt, LPGAMEOBJECT &object);
	void Zombie_Update(DWORD dt, LPGAMEOBJECT &object);
	void BlackLeopard_Update(DWORD dt, LPGAMEOBJECT &object);
	void VampireBat_Update(DWORD dt, LPGAMEOBJECT &object);
	void FishMan_Update(DWORD dt, LPGAMEOBJECT &object);
	void Boss_Update(DWORD dt, LPGAMEOBJECT &object);
};

