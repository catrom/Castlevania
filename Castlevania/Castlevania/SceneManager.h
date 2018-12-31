#pragma once

#include "Game.h"
#include "Grid.h"
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
#include "Water.h"
#include "BreakWall.h"
#include "ChangeSceneObject.h"
#include "Timer.h"

#include "IntroScene.h"
#include "TitleScreen.h"

#include <map>
using namespace std;

class SceneManager
{
	int IDScene;

	Game * game;
	Grid * grid;
	Unit * unit;

	IntroScene * introscene;
	TitleScreen * titlescreen;

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
	vector<LPGAMEOBJECT> listDoors;
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

	Timer * gameoverDelayTimer = new Timer(50);
	Timer * gameoverDelayTimer2 = new Timer(3000);

	SceneManager(Game * game);
	~SceneManager();

	int chooseToPlayAgain = 0;					// Lựa chọn của người chơi khi game over
	bool isGameReset = false;
	bool isGameOver = false;
	bool isGamePause = false;
	int isNeedToAddScoreTime = -1;				// Để cộng điểm dựa vào thời gian còn lại bên Player	
												// -1: không, 0: cần, 1: đã xong.
	
	void Init(int idScene);						// init simon position, camera position, grid..
	void LoadObjectsFromFile(LPCWSTR FilePath);	// load all objects (position, state, isEnable) from file 

	void GetObjectFromGrid();
	void GetColliableObjects(LPGAMEOBJECT curObj, vector<LPGAMEOBJECT>&coObjects);

	void Simon_Update(DWORD dt);
	void Whip_Update(DWORD dt);
	void Weapon_Update(DWORD dt, int index);
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

	void SetEnemiesSpawnPositon();				// Set position cho khởi tạo enemies

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

	// Game Over
	void DoGameOver();
};

