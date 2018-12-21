#include "SceneManager.h"


SceneManager::SceneManager(Game * game)
{
	this->game = game;

	LoadResources();
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init(int idScene)
{
	IDScene = idScene;

	switch (idScene)
	{
	case SCENE_1:
		grid = new Grid(1536, 480);
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_1);
		SetGameState(GAMESTATE_1);
		break;
	case SCENE_2:
		grid = new Grid(5632, 480);
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_2);
		SetGameState(GAMESTATE_2_1);
		break;
	case SCENE_3:
		grid = new Grid(1024, 480);
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_3);
		simon->SetState(STAIR_DOWN);
		SetGameState(GAMESTATE_3_1);
		break;
	default:
		break;
	}
}

void SceneManager::LoadResources()
{
	simon = new Simon();
	simon->LoadResources(textures, sprites, animations);

	whip = new Whip();
	whip->LoadResources(textures, sprites, animations);

	boss = new Boss();
	boss->LoadResources(textures, sprites, animations);

	weapon = new SubWeapon();
	weapon->LoadResources(textures, sprites, animations);

	Candle * candle = new Candle();
	candle->LoadResources(textures, sprites, animations);

	Effect * effect = new Effect();
	effect->LoadResources(textures, sprites, animations);

	Ground * ground = new Ground();
	ground->LoadResources(textures, sprites, animations);

	Items * item = new Items();
	item->LoadResources(textures, sprites, animations);

	Stair * stair = new Stair();
	stair->LoadResources(textures, sprites, animations);

	Door * door = new Door();
	door->LoadResources(textures, sprites, animations);

	Zombie * zombie = new Zombie();
	zombie->LoadResources(textures, sprites, animations);

	BlackLeopard * leopard = new BlackLeopard();
	leopard->LoadResources(textures, sprites, animations);

	VampireBat * bat = new VampireBat();
	bat->LoadResources(textures, sprites, animations);

	FishMan * fishman = new FishMan();
	fishman->LoadResources(textures, sprites, animations);

	FireBall * fireball = new FireBall();
	fireball->LoadResources(textures, sprites, animations);

	Bubble * bubble = new Bubble();
	bubble->LoadResources(textures, sprites, animations);

	tilemaps->Add(SCENE_1, FILEPATH_TEX_MAP_SCENE_1, FILEPATH_DATA_MAP_SCENE_1, 1536, 320);
	tilemaps->Add(SCENE_2, FILEPATH_TEX_MAP_SCENE_2, FILEPATH_DATA_MAP_SCENE_2, 5632, 352);
	tilemaps->Add(SCENE_3, FILEPATH_TEX_MAP_SCENE_3, FILEPATH_DATA_MAP_SCENE_3, 1024, 352);

	// for render bounding box
	textures->Add(ID_TEX_BBOX, FILEPATH_TEX_BBOX, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_BBOX_2, FILEPATH_TEX_BBOX_2, D3DCOLOR_XRGB(255, 255, 255));

	simon = new Simon();
	boss = new Boss();
	whip = new Whip();

	for (int i = 1; i <= 3; i++)
	{
		weapon = new SubWeapon();
		weapon->SetEnable(false);
		weaponlist.push_back(weapon);
	}
}

void SceneManager::LoadObjectsFromFile(LPCWSTR FilePath)
{
	fstream fs;
	fs.open(FilePath, ios::in);
	if (fs.fail())
	{
		MessageBox(GetActiveWindow(), L"Load object from file failed!", L"ERROR", MB_OK);
		DebugOut(L"[ERROR] Scene %d load data failed: file path = %s\n", IDScene, FilePath);
		fs.close();
		return;
	}

	int ID_Obj;
	float pos_x, pos_y;
	int state;
	bool isEnable;
	int idItem;

	while (!fs.eof())
	{
		fs >> ID_Obj >> pos_x >> pos_y >> state >> isEnable >> idItem;

		switch (ID_Obj)
		{
		case CANDLE:
		{
			Candle * candle = new Candle();
			candle->SetPosition(pos_x, pos_y);
			candle->SetState(state);
			candle->SetEnable(isEnable);
			candle->SetIDItem(idItem);
			unit = new Unit(grid, candle, pos_x, pos_y);
			break;
		}
		case GROUND:
		{
			Ground * ground = new Ground();
			ground->SetPosition(pos_x, pos_y);
			ground->SetState(state);
			ground->SetEnable(isEnable);
			ground->SetIDItem(idItem);
			unit = new Unit(grid, ground, pos_x, pos_y);
			break;
		}
		case STAIR:
		{
			Stair * stair = new Stair();
			stair->SetPosition(pos_x, pos_y);
			stair->SetState(state);
			stair->SetEnable(isEnable);
			stair->SetIDItem(idItem);
			listStairs.push_back(stair);
			unit = new Unit(grid, stair, pos_x, pos_y);
			break;
		}
		case DOOR:
		{
			Door * door = new Door();
			door->SetPosition(pos_x, pos_y);
			door->SetState(state);
			door->SetEnable(isEnable);
			door->SetIDItem(idItem);
			unit = new Unit(grid, door, pos_x, pos_y);
			break;
		}
		case ZOMBIE:
		{
			Zombie * zombie = new Zombie();
			zombie->SetEntryPosition(pos_x, pos_y);
			zombie->SetState(ZOMBIE_INACTIVE);
			zombie->SetEnable(isEnable);
			zombie->SetIDItem(idItem);
			unit = new Unit(grid, zombie, pos_x, pos_y);
			break;
		}
		case BLACK_LEOPARD:
		{
			BlackLeopard * leopard = new BlackLeopard();
			leopard->SetEntryPosition(pos_x, pos_y);
			leopard->SetPosition(pos_x, pos_y);
			leopard->SetState(state);
			leopard->SetIsRespawnWaiting(false);
			leopard->SetEnable(true);
			unit = new Unit(grid, leopard, pos_x, pos_y);
			break;
		}
		case VAMPIRE_BAT:
		{
			VampireBat * bat = new VampireBat();
			bat->SetEntryPosition(pos_x, pos_y);
			bat->SetState(VAMPIRE_BAT_INACTIVE);
			bat->SetEnable(true);
			bat->SetIDItem(idItem);
			unit = new Unit(grid, bat, pos_x, pos_y);
			break;
		}
		case FISHMAN:
		{
			FishMan * fishman = new FishMan();
			fishman->SetEntryPosition(pos_x, pos_y);
			fishman->SetState(FISHMAN_INACTIVE);
			fishman->SetEnable(true);
			fishman->SetIDItem(idItem);
			unit = new Unit(grid, fishman, pos_x, pos_y);
			break;
		}
		case BOSS:
		{
			boss = new Boss();
			boss->SetEntryPosition(pos_x, pos_y);
			boss->SetPosition(pos_x, pos_y);
			boss->SetState(BOSS_INACTIVE);
			boss->SetEnable(true);
			boss->SetIDItem(idItem);
			unit = new Unit(grid, boss, pos_x, pos_y);
			break;
		}
		case CHANGE_SCENE_OBJECT:
		{
			ChangeSceneObject * changeScene = new ChangeSceneObject();
			changeScene->SetPosition(pos_x, pos_y);
			changeScene->SetIDNextScene(state);
			changeScene->SetEnable(true);
			unit = new Unit(grid, changeScene, pos_x, pos_y);
			break;
		}
		default:
			break;
		}
	}

	fs.close();
}

void SceneManager::GetObjectFromGrid()
{
	listUnits.clear();
	listObjects.clear();
	listStaticObjectsToRender.clear();
	listMovingObjectsToRender.clear();

	grid->Get(game->GetCameraPositon(), listUnits);

	//DebugOut(L"%d \n", listUnits.size());

	for (UINT i = 0; i < listUnits.size(); i++)
	{
		LPGAMEOBJECT obj = listUnits[i]->GetObj();
		listObjects.push_back(obj);

		if (dynamic_cast<Candle*>(obj) || dynamic_cast<Door*>(obj))
			listStaticObjectsToRender.push_back(obj);
		else if (dynamic_cast<Zombie*>(obj) || dynamic_cast<BlackLeopard*>(obj) ||
			dynamic_cast<VampireBat*>(obj) || dynamic_cast<FishMan*>(obj) ||
			dynamic_cast<FireBall*>(obj) || dynamic_cast<Boss*>(obj) ||
			dynamic_cast<Items*>(obj))
			listMovingObjectsToRender.push_back(obj);
	}
}

void SceneManager::Update(DWORD dt)
{
	// Nếu Simon đi qua cửa thì không cần cập nhật hay xét va chạm
	if (SimonWalkThroughDoor() == true)
		return;

	// Khi Simon va chạm với ChangScene objects, tiến hành thay đổi, cập nhật trạng thái
	if (simon->changeScene != -1)
	{
		ChangeScene();
		simon->changeScene = -1;
	}

	// Lấy danh sách object từ grid 
	GetObjectFromGrid();

	// Cross effect
	CrossEffect();

	// Cập nhật bộ đếm thời gian
	UpdateTimeCounter();

	// double shot
	DoubleShotEffect();

	// triple shot
	TripleShotEffect();

	// Drop item
	SetDropItems();

	// Update
	Simon_Update(dt);
	Whip_Update(dt);

	for (int i = 0; i < 3; i++)
	{
		if (weaponlist[i]->IsEnable() == true)
		{
			Weapon_Update(dt, i);
		}
	}

	for (UINT i = 0; i < listObjects.size(); i++)
	{
		LPGAMEOBJECT object = listObjects[i];

		if (dynamic_cast<Items*>(object))
			Item_Update(dt, object);
		else if (dynamic_cast<Zombie*>(object))
			Zombie_Update(dt, object);
		else if (dynamic_cast<BlackLeopard*>(object))
			BlackLeopard_Update(dt, object);
		else if (dynamic_cast<VampireBat*>(object))
			VampireBat_Update(dt, object);
		else if (dynamic_cast<FishMan*>(object))
			FishMan_Update(dt, object);
		else if (dynamic_cast<Boss*>(object))
			Boss_Update(dt, object);
		else
			object->Update(dt, &listObjects, isUsingStopWatch);
	}

	// Không cho Simon đi ra khỏi vùng đánh boss
	if (isBossFighting == true && simon->x < game->GetCameraPositon().x)
		simon->x = game->GetCameraPositon().x;

	// Xoá các object đi ra khỏi vùng viewport
	SetInactivationByPosition();

	// update camera
	UpdateCameraPosition();

	// update grid
	UpdateGrid();
}

void SceneManager::UpdateTimeCounter()
{
	// Stop Watch
	if (isUsingStopWatch == true && GetTickCount() - stopWatchCounter > WEAPONS_STOP_WATCH_TIME)
	{
		isUsingStopWatch = false;
		stopWatchCounter = 0;
	}

	// Cross
	if (isCrossEffect == true && GetTickCount() - crossEffectTimeCounter > ITEM_CROSS_EFFECT_TIME)
	{
		isCrossEffect = false;
		crossEffectTimeCounter = 0;
	}

	// Simon dead
	if (isSimonDead == true && GetTickCount() - simonDeadTimeCounter > SIMON_DEAD_TIME)
	{
		isSimonDead = false;
		simonDeadTimeCounter = 0;
		ResetGame();
	}

	// Double shot
	if (isDoubleShotEffect == true && GetTickCount() - doubleShotEffectTimeCounter > ITEM_DOUBLE_SHOT_EFFECT_TIME)
	{
		isDoubleShotEffect = false;
		doubleShotEffectTimeCounter = 0;
	}

	// Triple shot
	if (isTripleShotEffect == true && GetTickCount() - tripleShotEffectTimeCounter > ITEM_TRIPLE_SHOT_EFFECT_TIME)
	{
		isTripleShotEffect = false;
		tripleShotEffectTimeCounter = 0;
	}
}

void SceneManager::Render()
{
	tilemaps->Get(IDScene)->Draw(game->GetCameraPositon(), isCrossEffect);

	simon->Render();
	//simon->RenderBoundingBox();

	for (int i = 0; i < 3; i++)
	{
		if (weaponlist[i]->IsEnable() == true)
		{
			weaponlist[i]->Render();
			//weaponlist[i]->RenderBoundingBox();
		}
	}

	if ((simon->GetState() == HIT_STAND || simon->GetState() == HIT_SIT ||
		simon->GetState() == HIT_STAIR_UP || simon->GetState() == HIT_STAIR_DOWN)
		&& simon->isHitSubWeapons == false)
	{
		whip->Render(simon->animations[simon->GetState()]->GetCurrentFrame());
		//whip->RenderBoundingBox();
	}

	/*for (auto obj : listObjects)
	{
		if (dynamic_cast<ChangeSceneObject*>(obj))
		{
			obj->RenderBoundingBox();
		}
	}*/

	for (auto obj : listStaticObjectsToRender)
	{
		obj->Render();
		//obj->RenderBoundingBox();
	}

	for (auto obj : listMovingObjectsToRender)
	{
		obj->Render();
		obj->RenderBoundingBox();
		obj->RenderActiveBoundingBox();
	}
}

void SceneManager::UpdateCameraPosition()
{
	if (isBossFighting == true)				// Boss fight -> not moving camera
		return;

	if (boss->GetState() == BOSS_ACTIVE)
	{
		isBossFighting = true;
		return;
	}

	if (simon->x > SCREEN_WIDTH / 2 &&
		simon->x + SCREEN_WIDTH / 2 < tilemaps->Get(IDScene)->GetMapWidth())
	{
		TileMap * map = tilemaps->Get(IDScene);
		int min_col = map->min_max_col_to_draw[map->index][0];
		int max_col = map->min_max_col_to_draw[map->index][1];

		if (simon->x >= min_col * 32 + (SCREEN_WIDTH / 2 - 16) &&
			simon->x <= max_col * 32 - (SCREEN_WIDTH / 2 - 16))
		{
			game->SetCameraPosition(simon->x - SCREEN_WIDTH / 2, 0);
		}
	}
}

void SceneManager::UpdateGrid()
{
	for (int i = 0; i < listUnits.size(); i++)
	{
		LPGAMEOBJECT obj = listUnits[i]->GetObj();

		if (obj->IsEnable() == false)
			continue;

		float newPos_x, newPos_y;
		obj->GetPosition(newPos_x, newPos_y);
		listUnits[i]->Move(newPos_x, newPos_y);
	}
}

bool SceneManager::SimonWalkThroughDoor()
{
	// Cập nhật trạng thái Simon đi qua cửa:
	// Di chuyển Camera -> Mở cửa -> AutoWalk -> Di chuyển Camera

	if (simon->isWalkThroughDoor == true && simon->isTouchGround == true)
	{
		simon->isWalkThroughDoor = false;
		simon->SetOrientation(1);
		simon->SetState(STAND);

		isMovingCamera1 = true;
		countDxCamera = 0;
	}

	if (isMovingCamera1 == true)
	{
		if (countDxCamera < 240)			// Di chuyển camera một đoạn 224
		{
			countDxCamera += 2;

			D3DXVECTOR3 cam = game->GetCameraPositon();
			game->SetCameraPosition(cam.x + 2, cam.y);

			return true;
		}

		if (isSetSimonAutoWalk == false)	// AutoWalk
		{
			isSetSimonAutoWalk = true;

			simon->SetState(WALK);
			simon->vy = 0;
			simon->AutoWalk(120, STAND, 1);
		}
		else
		{
			if (simon->isAutoWalk == false)
			{
				isMovingCamera2 = true;

				if (countDxCamera < 480)	// Di chuyển camera thêm một đoạn -> 480
				{
					countDxCamera += 2;

					D3DXVECTOR3 cam = game->GetCameraPositon();
					game->SetCameraPosition(cam.x + 2, cam.y);

					return true;
				}
				else
				{
					isMovingCamera1 = false;
					isMovingCamera2 = false;
					isSetSimonAutoWalk = false;
					countDxCamera = 0;

					tilemaps->Get(IDScene)->index += 1;  // tăng giới hạn min_max_col của tilemap
				}
			}
		}
	}

	return false;
}

void SceneManager::SetDropItems()
{
	for (UINT i = 0; i < listObjects.size(); i++)
	{
		LPGAMEOBJECT object = listObjects[i];

		if ((dynamic_cast<Candle*>(object) && object->GetState() == CANDLE_DESTROYED) ||
			(dynamic_cast<Zombie*>(object) && object->GetState() == ZOMBIE_DESTROYED) ||
			(dynamic_cast<VampireBat*>(object) && object->GetState() == VAMPIRE_BAT_DESTROYED) ||
			(dynamic_cast<FishMan*>(object) && object->GetState() == FISHMAN_DESTROYED) ||
			(dynamic_cast<Boss*>(object) && object->GetState() == BOSS_DESTROYED))
		{
			if (object->idItem != -1 && object->IsDroppedItem() == false)
			{
				if (dynamic_cast<Boss*>(object))
				{
					boss = dynamic_cast<Boss*>(object);

					if (boss->DropItem() == true)
					{
						object->SetIsDroppedItem(true);
						boss->SetEnable(false);

						float ix = game->GetCameraPositon().x + SCREEN_WIDTH / 2;
						float iy = game->GetCameraPositon().y + SCREEN_HEIGHT / 2;

						auto item = new Items();
						item->SetEnable(true);
						item->SetPosition(ix, iy);
						item->SetItem(object->idItem);

						listItems.push_back(item);
						unit = new Unit(grid, item, ix, iy);
					}
				}
				else
				{
					object->SetIsDroppedItem(true);

					// Tạo một item theo id

					auto item = new Items();
					item->SetEnable(true);
					item->SetPosition(object->x, object->y);
					item->SetItem(object->idItem);

					listItems.push_back(item);
					unit = new Unit(grid, item, object->x, object->y);
				}
			}
		}
	}
}

bool SceneManager::IsInViewport(LPGAMEOBJECT object)
{
	D3DXVECTOR2 camPosition = game->GetCameraPositon();

	float obj_x, obj_y;
	object->GetPosition(obj_x, obj_y);

	return obj_x >= camPosition.x && obj_x < camPosition.x + SCREEN_WIDTH
		&& obj_y >= camPosition.y && obj_y < camPosition.y + SCREEN_HEIGHT; // -5.0f để đảm bảo object vẫn còn nằm trong vùng grid để việc cập nhật grid chính xác
}

void SceneManager::SetInactivationByPosition()
{
	for (auto object : listObjects)
	{
		if (IsInViewport(object) == false)
		{
			if (dynamic_cast<Zombie*>(object) && object->GetState() == ZOMBIE_ACTIVE)
			{
				auto zombie = dynamic_cast<Zombie*>(object);
				zombie->SetState(ZOMBIE_INACTIVE);
			}
			else if (dynamic_cast<BlackLeopard*>(object) && object->GetState() == BLACK_LEOPARD_ACTIVE)
			{
				auto leopard = dynamic_cast<BlackLeopard*>(object);
				leopard->SetState(BLACK_LEOPARD_INACTIVE);
			}
			else if (dynamic_cast<VampireBat*>(object) && object->GetState() == VAMPIRE_BAT_ACTIVE)
			{
				auto bat = dynamic_cast<VampireBat*>(object);
				bat->SetState(VAMPIRE_BAT_INACTIVE);
			}
			else if (dynamic_cast<FishMan*>(object)
				&& (object->GetState() == FISHMAN_ACTIVE || object->GetState() == FISHMAN_JUMP))
			{
				auto fishman = dynamic_cast<FishMan*>(object);
				fishman->SetState(FISHMAN_INACTIVE);
			}
			else if (dynamic_cast<FireBall*>(object) && object->IsEnable() == true)
				object->SetEnable(false);
			else if (dynamic_cast<Items*>(object) && object->IsEnable() == true)
				object->SetEnable(false);
		}
		else if (dynamic_cast<FishMan*>(object)
			&& (object->GetState() == FISHMAN_ACTIVE || object->GetState() == FISHMAN_JUMP))
		{
			auto fishman = dynamic_cast<FishMan*>(object);

			float fish_x, fish_y;
			fishman->GetPosition(fish_x, fish_y);

			if (fish_y > fishman->GetEntryPosition().y)
			{
				fishman->SetIsNeedToCreateBubbles(true);   // rơi xuống nước
				fishman->SetState(FISHMAN_INACTIVE);
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (weaponlist[i]->IsEnable() == true)
		{
			if (IsInViewport(weaponlist[i]) == false)
				weaponlist[i]->SetEnable(false);
		}
	}
}

void SceneManager::ChangeScene()
{
	float x, y;
	simon->GetPosition(x, y);

	if (IDScene == SCENE_2 && simon->changeScene == SCENE_3)
	{
		Init(SCENE_3);

		if (x < 3200) SetGameState(GAMESTATE_3_1);
		else SetGameState(GAMESTATE_3_2);
	}
	else if (IDScene == SCENE_3 && simon->changeScene == SCENE_2)
	{
		Init(SCENE_2);

		if (x < 320) SetGameState(GAMESTATE_2_2_1);
		else SetGameState(GAMESTATE_2_2_2);
	}
	else if (IDScene == SCENE_1 && simon->changeScene == SCENE_2)
		Init(SCENE_2);
}

void SceneManager::SetGameState(int state)
{
	switch (state)
	{
	case GAMESTATE_1:
		simon->SetState(STAND);
		simon->SetPosition(0, 302);
		game->SetCameraPosition(0, 0);
		tilemaps->Get(SCENE_1)->index = 0;
		break;
	case GAMESTATE_2_1:
		simon->SetState(STAND);
		simon->SetPosition(0, 335);
		game->SetCameraPosition(0, 0);
		tilemaps->Get(SCENE_2)->index = 0;
		break;
	case GAMESTATE_2_2:
		simon->SetState(STAND);
		simon->SetPosition(3115, 143);
		game->SetCameraPosition(3056, 0);
		tilemaps->Get(SCENE_2)->index = 1;
		break;
	case GAMESTATE_2_2_1:
		simon->SetState(STAIR_UP);
		simon->SetPosition(3172, 370);
		game->SetCameraPosition(3056, 0);
		tilemaps->Get(SCENE_2)->index = 1;
		break;
	case GAMESTATE_2_2_2:
		simon->SetState(STAIR_UP);
		simon->SetPosition(3812, 370);
		game->SetCameraPosition(3056, 0);
		tilemaps->Get(SCENE_2)->index = 1;
		break;
	case GAMESTATE_2_3:
		simon->SetState(STAND);
		simon->SetPosition(4139, 143);
		game->SetCameraPosition(4079, 0);
		tilemaps->Get(SCENE_2)->index = 2;
		break;
	case GAMESTATE_3_1:
		simon->SetState(STAIR_DOWN);
		simon->SetPosition(100, 48);
		game->SetCameraPosition(0, 0);
		tilemaps->Get(SCENE_3)->index = 0;
		break;
	case GAMESTATE_3_2:
		simon->SetState(STAIR_DOWN);
		simon->SetPosition(740, 48);
		game->SetCameraPosition(0, 0);
		tilemaps->Get(SCENE_3)->index = 0;
		break;
	default:
		break;
	}
}

void SceneManager::ResetGame()
{
	isGameReset = true; // flag variable for reset time in Player::Update()

	simon->SetState(STAND);
	simon->SetHP(SIMON_HP);
	simon->SetEnergy(SIMON_ENERGY);

	whip->SetState(NORMAL_WHIP);
	simon->SetSubWeapon(-1);

	int curIndex;

	switch (IDScene)
	{
	case SCENE_1:
		Init(SCENE_1);
		break;
	case SCENE_2:
		curIndex = tilemaps->Get(SCENE_2)->index;

		Init(SCENE_2);

		if (curIndex == 0)
			SetGameState(GAMESTATE_2_1);
		else if (curIndex == 1)
			SetGameState(GAMESTATE_2_2);
		else
		{
			isBossFighting = false;
			SetGameState(GAMESTATE_2_3);
		}
		break;
	case SCENE_3:
		Init(SCENE_2);
		SetGameState(GAMESTATE_2_2);
		break;
	default:
		break;
	}
}

void SceneManager::CrossEffect()
{
	if (simon->isCrossCollected == true)
	{
		simon->isCrossCollected = false;

		isCrossEffect = true;
		crossEffectTimeCounter = GetTickCount();

		for (UINT i = 0; i < listObjects.size(); i++)
		{
			// Cross chỉ tác dụng với các object nằm trong viewport
			if (IsInViewport(listObjects[i]) == false)
				continue;

			if (dynamic_cast<Candle*>(listObjects[i]) && listObjects[i]->IsEnable() == true)
			{
				auto candle = dynamic_cast<Candle*>(listObjects[i]);
				candle->SetState(CANDLE_DESTROYED);
			}
			else if (dynamic_cast<Zombie*>(listObjects[i]) && listObjects[i]->GetState() == ACTIVE)
			{
				auto zombie = dynamic_cast<Zombie*>(listObjects[i]);
				zombie->SetState(ZOMBIE_DESTROYED);
			}
			else if (dynamic_cast<BlackLeopard*>(listObjects[i]) && listObjects[i]->GetState() == ACTIVE)
			{
				auto leopard = dynamic_cast<BlackLeopard*>(listObjects[i]);
				leopard->SetState(BLACK_LEOPARD_DESTROYED);
			}
			else if (dynamic_cast<VampireBat*>(listObjects[i]) && listObjects[i]->GetState() == ACTIVE)
			{
				auto bat = dynamic_cast<VampireBat*>(listObjects[i]);
				bat->SetState(VAMPIRE_BAT_DESTROYED);
			}
			else if (dynamic_cast<FishMan*>(listObjects[i]) && listObjects[i]->GetState() == ACTIVE)
			{
				auto fishman = dynamic_cast<FishMan*>(listObjects[i]);
				fishman->SetState(FISHMAN_DESTROYED);
			}
		}
	}
}

void SceneManager::DoubleShotEffect()
{
	if (simon->isGotDoubleShotItem == true)
	{
		simon->isGotDoubleShotItem = false;
		isDoubleShotEffect = true;
		doubleShotEffectTimeCounter = GetTickCount();
	}
}

void SceneManager::TripleShotEffect()
{
	if (simon->isGotTripleShotItem == true)
	{
		simon->isGotTripleShotItem = false;
		isTripleShotEffect = true;
		tripleShotEffectTimeCounter = GetTickCount();
	}
}

void SceneManager::Simon_Update(DWORD dt)
{
	if (simon->GetState() == DEAD)
	{
		if (isSimonDead == false)
		{
			isSimonDead = true;
			simonDeadTimeCounter = GetTickCount();
		}

		return;
	}

	vector<LPGAMEOBJECT> coObjects;

	for (auto obj : listObjects)
	{
		if (dynamic_cast<Door*>(obj) || dynamic_cast<Ground*>(obj) || dynamic_cast<ChangeSceneObject*>(obj))
			coObjects.push_back(obj);
		else if (simon->isAutoWalk == false) // nếu simon auto-walk sẽ không xét va chạm với enemy
		{
			if (dynamic_cast<FireBall*>(obj) && obj->IsEnable() == true)
				coObjects.push_back(obj);
			else if ((dynamic_cast<Zombie*>(obj) || dynamic_cast<BlackLeopard*>(obj) || 
				dynamic_cast<VampireBat*>(obj) || dynamic_cast<Boss*>(obj)) && obj->GetState() == ACTIVE)
				coObjects.push_back(obj);
			else if (dynamic_cast<FishMan*>(obj) && (obj->GetState() == ACTIVE || obj->GetState() == FISHMAN_JUMP))
				coObjects.push_back(obj);
		}
	}

	simon->Update(dt, &coObjects);
	simon->CheckCollisionWithItem(&listItems);
	simon->CheckCollisionWithEnemyActiveArea(&listObjects);
}

void SceneManager::Whip_Update(DWORD dt)
{
	if (whip->GetScoreReceived() != 0)
	{
		simon->AddScore(whip->GetScoreReceived());
		whip->SetScoreReceived(0);
	}

	if (simon->isGotChainItem == true) // update trạng thái của whip
	{
		simon->isGotChainItem = false;
		whip->PowerUp();
	}

	// lấy vị trí và phương của simon cho whip
	float simon_x, simon_y;
	simon->GetPosition(simon_x, simon_y);
	bool isSimonStand = true;

	if (simon->GetState() == SIT || simon->GetState() == HIT_SIT)
		isSimonStand = false;

	whip->SetOrientation(simon->GetOrientation());
	whip->SetWhipPosition(D3DXVECTOR3(simon_x, simon_y, 0), isSimonStand);

	// chỉ xét va chạm khi render tới sprite cuối cùng của simon (vung tay tới)
	if (simon->IsHit() &&
		simon->animations[simon->GetState()]->IsRenderingLastFrame() == true &&
		simon->isHitSubWeapons == false)
	{
		vector<LPGAMEOBJECT> coObjects;

		for (auto obj : listObjects)
		{
			if (dynamic_cast<Candle*>(obj) || dynamic_cast<FireBall*>(obj))
				coObjects.push_back(obj);
			if ((dynamic_cast<Zombie*>(obj) ||
				dynamic_cast<BlackLeopard*>(obj) || dynamic_cast<VampireBat*>(obj)) && obj->GetState() == ACTIVE)
				coObjects.push_back(obj);
			else if (dynamic_cast<FishMan*>(obj) && (obj->GetState() == ACTIVE || obj->GetState() == FISHMAN_JUMP))
				coObjects.push_back(obj);
			else if (dynamic_cast<Boss*>(obj) && whip->GetTargetTypeHit() != BOSS)  // Do một frame rất ngắn nên dễ dẫn đến việc xét va chạm liên tục với boss.
				coObjects.push_back(obj);											// -> Nếu đã đánh trúng boss rồi thì không thêm boss vô coObjects nữa.
		}

		whip->Update(dt, &coObjects);
	}
	else
	{
		whip->SetTargetTypeHit(-1);
	}
}

void SceneManager::Weapon_Update(DWORD dt, int index)
{
	if (weaponlist[index] == STOP_WATCH)
		return;

	if (weaponlist[index]->IsEnable() == false)
		return;

	if (weaponlist[index]->GetScoreReceived() != 0)
	{
		simon->AddScore(weaponlist[index]->GetScoreReceived());
		weaponlist[index]->SetScoreReceived(0);
	}

	vector<LPGAMEOBJECT> coObjects;
	coObjects.push_back(simon); // dùng để xét va chạm của Simon với boomerang

	for (auto obj : listObjects)
	{
		if ((dynamic_cast<Candle*>(obj) || dynamic_cast<Ground*>(obj) ||
			dynamic_cast<FireBall*>(obj) || dynamic_cast<Zombie*>(obj) ||
			dynamic_cast<BlackLeopard*>(obj) || dynamic_cast<VampireBat*>(obj) ||
			dynamic_cast<FishMan*>(obj) || dynamic_cast<Boss*>(obj)) &&
			obj->GetState() != INACTIVE && obj->IsEnable() == true)
		{
			coObjects.push_back(obj);
		}
	}

	weaponlist[index]->Update(dt, &coObjects);
}

void SceneManager::Item_Update(DWORD dt, LPGAMEOBJECT & item)
{
	if (item->IsEnable() == true)
	{
		vector<LPGAMEOBJECT> coObjects;

		for (auto obj : listObjects)
		{
			if (dynamic_cast<Ground*>(obj))
				coObjects.push_back(obj);
		}

		item->Update(dt, &coObjects);
	}
}

void SceneManager::Zombie_Update(DWORD dt, LPGAMEOBJECT & object)
{
	if (object->GetState() != ZOMBIE_INACTIVE)
	{
		auto zombie = dynamic_cast<Zombie*>(object);

		if (zombie->IsSettedPosition() == false)
		{
			zombie->SetIsSettedPosition(true);

			D3DXVECTOR2 entryPos = zombie->GetEntryPosition();
			if (zombie->GetOrientation() == -1) zombie->SetPosition(game->GetCameraPositon().x + SCREEN_WIDTH - ENEMY_DEFAULT_BBOX_WIDTH, entryPos.y);
			else zombie->SetPosition(game->GetCameraPositon().x + ENEMY_DEFAULT_BBOX_WIDTH, entryPos.y);
		}

		vector<LPGAMEOBJECT> coObjects;

		for (auto obj : listObjects)
		{
			if (dynamic_cast<Ground*>(obj))
				coObjects.push_back(obj);
		}

		object->Update(dt, &coObjects, isUsingStopWatch);
	}

}

void SceneManager::BlackLeopard_Update(DWORD dt, LPGAMEOBJECT & object)
{
	if (object->GetState() != BLACK_LEOPARD_INACTIVE)
	{
		vector<LPGAMEOBJECT> coObjects;

		for (auto obj : listObjects)
		{
			if (dynamic_cast<Ground*>(obj))
				coObjects.push_back(obj);
		}

		object->Update(dt, &coObjects, isUsingStopWatch);
	}
}

void SceneManager::VampireBat_Update(DWORD dt, LPGAMEOBJECT & object)
{
	if (object->GetState() != VAMPIRE_BAT_INACTIVE)
	{
		auto bat = dynamic_cast<VampireBat*>(object);

		if (bat->IsSettedPosition() == false)
		{
			bat->SetIsSettedPosition(true);

			// set random hướng cho dơi

			int listNx[2] = { -1, 1 };
			int rndIndex = rand() % 2;
			bat->SetOrientation(listNx[rndIndex]);

			// set vị trí cho dơi
			// dơi bay ngang tầm simon, từ phía cuối của 2 đầu màn hình)
			float bx, by;

			by = simon->y + 20;

			if (bat->GetOrientation() == -1) bx = game->GetCameraPositon().x + SCREEN_WIDTH - ENEMY_DEFAULT_BBOX_WIDTH;
			else bx = game->GetCameraPositon().x + ENEMY_DEFAULT_BBOX_WIDTH;

			bat->SetPosition(bx, by);
			bat->SetState(VAMPIRE_BAT_ACTIVE);
		}

		bat->Update(dt, NULL, isUsingStopWatch);
	}
}

void SceneManager::FishMan_Update(DWORD dt, LPGAMEOBJECT & object)
{
	auto fishman = dynamic_cast<FishMan*>(object);

	if (fishman->GetState() != FISHMAN_INACTIVE)
	{
		if (fishman->GetState() == FISHMAN_ACTIVE && fishman->IsSettedPosition() == true &&
			GetTickCount() - fishman->GetLastTimeShoot() >= fishman->GetDeltaTimeToShoot())
		{
			fishman->SetState(FISHMAN_HIT);

			// Tạo fireball
			float fx, fy, nx;
			fishman->GetPosition(fx, fy);
			nx = fishman->GetOrientation();

			auto fireball = new FireBall();
			fireball->SetPosition(fx + 5.0f, fy + 10.0f);
			fireball->SetOrientation(nx);
			fireball->SetState(FIREBALL);
			fireball->SetEnable(true);

			unit = new Unit(grid, fireball, fx + 5.0f, fy + 10.0f);

			// Đặt hướng quay mặt của Fishman sau khi bắn (quay về phía simon)
			float sx, sy;
			simon->GetPosition(sx, sy);

			if (fx < sx) fishman->SetNxAfterShoot(1);
			else fishman->SetNxAfterShoot(-1);
		}
		else
		{
			if (fishman->IsSettedPosition() == false)
			{
				fishman->SetIsSettedPosition(true);

				float simon_x, simon_y;
				simon->GetPosition(simon_x, simon_y);

				int nx = simon_x > fishman->GetEntryPosition().x ? 1 : -1;
				fishman->SetOrientation(nx);

				float distance = 50 + rand() % 100;

				fishman->SetPosition(simon_x - nx * distance, fishman->GetEntryPosition().y);

				fishman->SetState(FISHMAN_JUMP);
			}

			vector<LPGAMEOBJECT> coObjects;

			for (auto obj : listObjects)
			{
				if (dynamic_cast<Ground*>(obj))
					coObjects.push_back(obj);
			}

			fishman->Update(dt, &coObjects, isUsingStopWatch);
		}
	}
	else if (fishman->IsRenderingBubbles() == true)
	{
		fishman->Update(dt);
	}
}

void SceneManager::Boss_Update(DWORD dt, LPGAMEOBJECT & object)
{
	if (object->GetState() == BOSS_INACTIVE)
		return;

	boss = dynamic_cast<Boss*>(object);

	// Passing simon's position for boss movement
	float sx, sy;
	simon->GetPosition(sx, sy);
	boss->SetSimonPosition(sx, sy);

	boss->Update(dt);
}


