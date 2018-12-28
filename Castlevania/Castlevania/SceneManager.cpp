#include "SceneManager.h"


SceneManager::SceneManager(Game * game)
{
	this->game = game;
	LoadResources();

	// INIT
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

SceneManager::~SceneManager()
{
}

void SceneManager::Init(int idScene)
{
	IDScene = idScene;

	switch (idScene)
	{
	case INTRO_SCREEN:
		introscene = new IntroScene(simon);
		break;
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

void SceneManager::LoadSprites(int id, LPCWSTR tex, LPCWSTR sprite_data, LPCWSTR animation_data)
{
	textures->Add(id, tex);
	LPDIRECT3DTEXTURE9 texture = textures->Get(id);

	ifstream spriteReader, animationReader;

	spriteReader.open(sprite_data);
	animationReader.open(animation_data);

	if (spriteReader.fail())
	{
		DebugOut(L"[ERROR] LoadSprites failed!: ID=%d", id);
		spriteReader.close();
		return;
	}

	if (animationReader.fail())
	{
		DebugOut(L"[ERROR] LoadAnimation failed!: ID=%d", id);
		animationReader.close();
		return;
	}
	
	// Load sprite data

	string spriteid;
	int left, top, right, bottom;

	while (spriteReader >> spriteid >> left >> top >> right >> bottom)
		sprites->Add(spriteid, left, top, right, bottom, texture);

	spriteReader.close();

	// Load animation data

	string animationId;
	string line;
	string spriteId;
	int frameTime;

	while (getline(animationReader, line))
	{
		LPANIMATION ani = new Animation();

		istringstream iss(line, istringstream::in);
		iss >> animationId;

		while (iss >> spriteId >> frameTime)
			ani->Add(spriteId, frameTime);

		animations->Add(animationId, ani);
	}

	animationReader.close();
}

void SceneManager::LoadResources()
{
	// for render bounding box
	textures->Add(ID_TEX_BBOX, L"Textures\\BBox.png");
	textures->Add(ID_TEX_BBOX_2, L"Textures\\BBox2.png");

	// for game control
	textures->Add(ID_TEX_YESNO, L"Textures\\YesNo.png");
	textures->Add(ID_TEX_PAUSE, L"Textures\\Pause.png");

	// Title screen
	textures->Add(ID_TEX_TITLESCREEN, L"Textures\\TitleScreen.png");

	// Intro screen
	textures->Add(ID_TEX_INTROSCREEN, L"Textures\\IntroScreen.png");

	// Game object
	LoadSprites(ID_TEX_SIMON, L"Textures\\Simon.png", L"Textures\\Simon_sprites.txt", L"Textures\\Simon_animations.txt");
	LoadSprites(ID_TEX_WHIP, L"Textures\\Whip.png", L"Textures\\Whip_sprites.txt", L"Textures\\Whip_animations.txt");
	LoadSprites(ID_TEX_BOSS, L"Textures\\Boss.png", L"Textures\\Boss_sprites.txt", L"Textures\\Boss_animations.txt");
	LoadSprites(ID_TEX_SUBWEAPONS, L"Textures\\SubWeapons.png", L"Textures\\SubWeapons_sprites.txt", L"Textures\\SubWeapons_animations.txt");
	LoadSprites(ID_TEX_CANDLE, L"Textures\\Candle.png", L"Textures\\Candle_sprites.txt", L"Textures\\Candle_animations.txt");
	LoadSprites(ID_TEX_EFFECT, L"Textures\\Effect.png", L"Textures\\Effect_sprites.txt", L"Textures\\Effect_animations.txt");
	LoadSprites(ID_TEX_SPARK, L"Textures\\Spark.png", L"Textures\\Spark_sprites.txt", L"Textures\\Spark_animations.txt");
	LoadSprites(ID_TEX_BUBBLES, L"Textures\\Bubbles.png", L"Textures\\Bubbles_sprites.txt", L"Textures\\Bubbles_animations.txt");
	LoadSprites(ID_TEX_GROUND, L"Textures\\Ground.png", L"Textures\\Ground_sprites.txt", L"Textures\\Ground_animations.txt");
	LoadSprites(ID_TEX_ITEMS, L"Textures\\Items.png", L"Textures\\Items_sprites.txt", L"Textures\\Items_animations.txt");
	LoadSprites(ID_TEX_STAIR, L"Textures\\Stair.png", L"Textures\\Stair_sprites.txt", L"Textures\\Stair_animations.txt");
	LoadSprites(ID_TEX_DOOR, L"Textures\\Door.png", L"Textures\\Door_sprites.txt", L"Textures\\Door_animations.txt");
	LoadSprites(ID_TEX_ZOMBIE, L"Textures\\Zombie.png", L"Textures\\Zombie_sprites.txt", L"Textures\\Zombie_animations.txt");
	LoadSprites(ID_TEX_BLACK_LEOPARD, L"Textures\\BlackLeopard.png", L"Textures\\BlackLeopard_sprites.txt", L"Textures\\BlackLeopard_animations.txt");
	LoadSprites(ID_TEX_VAMPIRE_BAT, L"Textures\\VampireBat.png", L"Textures\\VampireBat_sprites.txt", L"Textures\\VampireBat_animations.txt");
	LoadSprites(ID_TEX_FISHMAN, L"Textures\\FishMan.png", L"Textures\\FishMan_sprites.txt", L"Textures\\FishMan_animations.txt");
	LoadSprites(ID_TEX_FIREBALL, L"Textures\\FireBall.png", L"Textures\\FireBall_sprites.txt", L"Textures\\FireBall_animations.txt");
	LoadSprites(ID_TEX_RECT, L"Textures\\Rect.png", L"Textures\\Rect_sprites.txt", L"Textures\\Rect_animations.txt");
	LoadSprites(ID_TEX_HP, L"Textures\\HP.png", L"Textures\\HP_sprites.txt", L"Textures\\HP_animations.txt");
	LoadSprites(ID_TEX_BREAKWALL, L"Textures\\BreakWall.png", L"Textures\\BreakWall_sprites.txt", L"Textures\\BreakWall_animations.txt");
	LoadSprites(ID_TEX_BREAKWALL, L"Textures\\IntroObjects.png", L"Textures\\IntroObjects_sprites.txt", L"Textures\\IntroObjects_animations.txt");

	tilemaps->Add(SCENE_1, L"Scenes\\Scene1.png", L"Scenes\\Scene1_map.txt", 1536, 320);
	tilemaps->Add(SCENE_2, L"Scenes\\Scene2.png", L"Scenes\\Scene2_map.txt", 5632, 352);
	tilemaps->Add(SCENE_3, L"Scenes\\Scene3.png", L"Scenes\\Scene3_map.txt", 1024, 352);
}

void SceneManager::LoadObjectsFromFile(LPCWSTR FilePath)
{
	fstream fs;
	fs.open(FilePath, ios::in);
	if (fs.fail())
	{
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
			candle->SetEnable(true);
			candle->SetIDItem(idItem);
			unit = new Unit(grid, candle, pos_x, pos_y);
			break;
		}
		case GROUND:
		{
			Ground * ground = new Ground();
			ground->SetPosition(pos_x, pos_y);
			ground->SetState(state);
			ground->SetEnable(true);
			unit = new Unit(grid, ground, pos_x, pos_y);
			break;
		}
		case STAIR:
		{
			Stair * stair = new Stair();
			stair->SetPosition(pos_x, pos_y);
			stair->SetState(state);
			stair->SetEnable(true);
			unit = new Unit(grid, stair, pos_x, pos_y);
			break;
		}
		case DOOR:
		{
			Door * door = new Door();
			door->SetPosition(pos_x, pos_y);
			door->SetState(state);
			door->SetEnable(true);
			unit = new Unit(grid, door, pos_x, pos_y);
			break;
		}
		case ZOMBIE:
		{
			Zombie * zombie = new Zombie();
			zombie->SetEntryPosition(pos_x, pos_y);
			zombie->SetState(INACTIVE);
			zombie->SetEnable(true);
			unit = new Unit(grid, zombie, pos_x, pos_y);
			break;
		}
		case BLACK_LEOPARD:
		{
			BlackLeopard * leopard = new BlackLeopard();
			leopard->SetEntryPosition(pos_x, pos_y);
			leopard->SetState(INACTIVE);
			leopard->SetEnable(true);
			unit = new Unit(grid, leopard, pos_x, pos_y);
			break;
		}
		case VAMPIRE_BAT:
		{
			VampireBat * bat = new VampireBat();
			bat->SetEntryPosition(pos_x, pos_y);
			bat->SetState(INACTIVE);
			bat->SetEnable(true);
			unit = new Unit(grid, bat, pos_x, pos_y);
			break;
		}
		case FISHMAN:
		{
			FishMan * fishman = new FishMan();
			fishman->SetEntryPosition(pos_x, pos_y);
			fishman->SetState(INACTIVE);
			fishman->SetEnable(true);
			unit = new Unit(grid, fishman, pos_x, pos_y);
			break;
		}
		case BOSS:
		{
			boss = new Boss();
			boss->SetEntryPosition(pos_x, pos_y);
			boss->SetState(INACTIVE);
			boss->SetEnable(true);
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
		case WATER:
		{
			water = new Water();
			water->SetPosition(pos_x, pos_y);
			water->SetEnable(true);
			unit = new Unit(grid, water, pos_x, pos_y);
			break;
		}
		case BREAKWALL:
		{
			BreakWall * breakwall = new BreakWall();
			breakwall->SetPosition(pos_x, pos_y);
			breakwall->SetEnable(true);
			breakwall->SetState(NORMAL);
			breakwall->SetIDItem(idItem);
			unit = new Unit(grid, breakwall, pos_x, pos_y);
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
	listStairs.clear();
	listDoors.clear();
	listStaticObjectsToRender.clear();
	listMovingObjectsToRender.clear();

	grid->Get(game->GetCameraPositon(), listUnits);

	//DebugOut(L"%d \n", listUnits.size());

	for (UINT i = 0; i < listUnits.size(); i++)
	{
		LPGAMEOBJECT obj = listUnits[i]->GetObj();
		listObjects.push_back(obj);

		if (dynamic_cast<Ground*>(obj))
			continue;
		else if (dynamic_cast<Stair*>(obj))
			listStairs.push_back(obj);
		else if (dynamic_cast<Door*>(obj))
			listDoors.push_back(obj);
		else if (dynamic_cast<Candle*>(obj) || 
				dynamic_cast<Water*>(obj) || dynamic_cast<BreakWall*>(obj))
			listStaticObjectsToRender.push_back(obj);
		else 
			listMovingObjectsToRender.push_back(obj);
	}
}

void SceneManager::Update(DWORD dt)
{
	if (IDScene == TITLE_SCREEN)
		return;

	if (IDScene == INTRO_SCREEN)
	{
		introscene->Update(dt);
		return;
	}

	// Pause Game
	if (isGamePause == true)
		return;

	// Game over
	if (simon->isGotMagicCrystalItem == true)
	{
		DoGameOver();

		if (isGameOver == true)
			return;
	}

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
		Weapon_Update(dt, i);

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
			object->Update(dt, &listObjects, !stopWatchTimer->IsTimeUp());
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
	if (stopWatchTimer->IsTimeUp() == true)
		stopWatchTimer->Stop();

	// Cross
	if (crossEffectTimer->IsTimeUp() == true)
		crossEffectTimer->Stop();

	// Simon dead
	if (isSimonDead == true && simonDeadTimer->IsTimeUp() == true)
	{
		simonDeadTimer->Stop();

		if (simon->GetLife() == 0)
			isGameOver = true;
		else 
			ResetGame();
	}

	// Double shot
	if (doubleShotTimer->IsTimeUp() == true)
		doubleShotTimer->Stop();

	// Triple shot
	if (tripleShotTimer->IsTimeUp() == true)
		tripleShotTimer->Stop();
}

void SceneManager::Render()
{
	if (isGameOver == true)
		return;

	if (IDScene == TITLE_SCREEN)
	{
		titlescene = Textures::GetInstance()->Get(ID_TEX_TITLESCREEN);
		game->Draw(0, 0, 0, 0, titlescene, 0, 0, 514, 450);
	}
	else if (IDScene == INTRO_SCREEN)
	{
		introscene->Render();
	}
	else
	{
		tilemaps->Get(IDScene)->Draw(game->GetCameraPositon(), !crossEffectTimer->IsTimeUp());

		for (auto obj : listStaticObjectsToRender)
		{
			obj->Render();
			//obj->RenderBoundingBox();
		}

		for (auto obj : listMovingObjectsToRender)
		{
			obj->Render();
			//obj->RenderBoundingBox();
		}

		simon->Render();
		//simon->RenderBoundingBox();

		for (int i = 0; i < 3; i++)
		{
			weaponlist[i]->Render();
			//weaponlist[i]->RenderBoundingBox();
		}

		if (simon->isHitSubWeapons == false)
		{
			if (simon->IsHit() == true)
				whip->Render(simon->animations[simon->GetState()]->GetCurrentFrame());
			else
				whip->Render(-1);

			//whip->RenderBoundingBox();
		}

		for (auto obj : listDoors)
		{
			obj->Render();
			//obj->RenderBoundingBox();
		}
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
		simon->isFalling = false;
		simon->SetOrientation(DIR_RIGHT);
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
			simon->AutoWalk(120, STAND, DIR_RIGHT);
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

int SceneManager::GetRandomItem()
{
	std::map<int, int> randomRange = {
		{STOP_WATCH,	1},
		{DAGGER,		4},
		{AXE,			6},
		{HOLY_WATER,	8},
		{BOOMERANG,		10},
		{SMALL_HEART,	60},
		{LARGE_HEART,	70},
		{CROSS,			72},
		{INVISIBILITY_POTION, 74},
		{CHAIN,			80},
		{MONEY_BAG_RED,	85},
		{MONEY_BAG_BLUE, 89},
		{MONEY_BAG_WHITE,	92},
		{MONEY_BAG_FLASHING,94},
		{DOUBLE_SHOT,	96},
		{TRIPLE_SHOT,	98},
		{PORK_CHOP,		100} };

	bool canDropItem = (rand() % 100) < 80 ? true : false; // tỉ lệ rớt item là 80/100

	if (canDropItem == false)
		return -1;

	int randomValue = rand() % 100;

	for (auto i = randomRange.begin(); i != randomRange.end(); i++)
	{
		if (randomValue < (*i).second)
			return (*i).first;
	}
}

void SceneManager::SetDropItems()
{
	for (UINT i = 0; i < listObjects.size(); i++)
	{
		LPGAMEOBJECT object = listObjects[i];
		int idItem = -1;
		float x, y;

		if (object->IsDroppedItem() == true)
			continue;

		if (dynamic_cast<Candle*>(object) && object->GetState() == CANDLE_DESTROYED)
		{
			idItem = object->idItem;
			object->GetPosition(x, y);
			object->SetIsDroppedItem(true);
		}
		else if (dynamic_cast<BreakWall*>(object)
			&& object->GetState() == BREAK && object->IsDroppedItem() == false)
		{
			idItem = object->idItem;
			object->GetPosition(x, y);
			object->SetIsDroppedItem(true);
		}
		else if (dynamic_cast<Boss*>(object) && object->GetState() == BOSS_DESTROYED)
		{
			if (boss->DropItem() == true)
			{
				boss->SetEnable(false);
				boss->SetIsDroppedItem(true);

				idItem = MAGIC_CRYSTAL;
				x = game->GetCameraPositon().x + SCREEN_WIDTH / 2;
				y = game->GetCameraPositon().y + SCREEN_HEIGHT / 2;
			}
		}
		else if ((dynamic_cast<Zombie*>(object) && object->GetState() == ZOMBIE_DESTROYED) ||
			(dynamic_cast<VampireBat*>(object) && object->GetState() == VAMPIRE_BAT_DESTROYED) ||
			(dynamic_cast<FishMan*>(object) && object->GetState() == FISHMAN_DESTROYED))
		{
			idItem = GetRandomItem();
			object->GetPosition(x, y);
			object->SetIsDroppedItem(true);
		}

		if (idItem != -1)
		{
			// Tạo một item theo id

			auto item = new Items();
			item->SetEnable(true);
			item->SetPosition(x, y);
			item->SetItem(idItem);

			listItems.push_back(item);
			unit = new Unit(grid, item, x, y);
		}
	}
}

bool SceneManager::IsInViewport(LPGAMEOBJECT object)
{
	D3DXVECTOR2 camPosition = game->GetCameraPositon();

	float obj_x, obj_y;
	object->GetPosition(obj_x, obj_y);

	return obj_x >= camPosition.x && obj_x < camPosition.x + SCREEN_WIDTH
		&& obj_y >= camPosition.y && obj_y < camPosition.y + SCREEN_HEIGHT; 
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
		simon->SetOrientation(1);
		game->SetCameraPosition(0, 0);
		tilemaps->Get(SCENE_3)->index = 0;
		break;
	case GAMESTATE_3_2:
		simon->SetState(STAIR_DOWN);
		simon->SetPosition(740, 48);
		simon->SetOrientation(1);
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
	isGameOver = false;
	isGamePause = false;
	isSimonDead = false;

	int life = simon->GetLife();
	
	simon = new Simon();
	if (life > 0)
		simon->SetLife(life);

	whip->SetState(NORMAL_WHIP);

	boss = new Boss();
	boss->SetState(BOSS_INACTIVE);

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
			SetGameState(GAMESTATE_2_3);
			isBossFighting = false;
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
	if (simon->isGotCrossItem == true)
	{
		simon->isGotCrossItem = false;
		crossEffectTimer->Start();

		for (UINT i = 0; i < listObjects.size(); i++)
		{
			// Cross chỉ tác dụng với các object nằm trong viewport
			if (IsInViewport(listObjects[i]) == false)
				continue;

			if (dynamic_cast<Zombie*>(listObjects[i]) && listObjects[i]->GetState() == ACTIVE)
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
		doubleShotTimer->Start();
	}
}

void SceneManager::TripleShotEffect()
{
	if (simon->isGotTripleShotItem == true)
	{
		simon->isGotTripleShotItem = false;
		tripleShotTimer->Start();
	}
}

void SceneManager::DoGameOver()
{
	// 3 giai đoạn:
	// + Cộng HP
	// + Cộng điểm theo thời gian còn lại
	// + Cộng điểm theo energy còn lại

	if (simon->GetHP() < 16)
	{
		if (gameoverDelayTimer->IsTimeUp() == true)		// delay tăng máu
		{
			gameoverDelayTimer->Start();
			simon->AddHP(1);
		}

		return;
	}
	
	if (isNeedToAddScoreTime == -1)
	{
		isNeedToAddScoreTime = 0;
		return;
	}
	else if (isNeedToAddScoreTime == 0)
	{
		return;
	}

	if (simon->GetEnergy() > 0)
	{
		simon->LoseEnergy(1);
		simon->AddScore(100);
		return;
	}

	isGameOver = true;
}

void SceneManager::Simon_Update(DWORD dt)
{
	if (simon->GetState() == DEAD)
	{
		if (isSimonDead == false)
		{
			isSimonDead = true;
			simonDeadTimer->Start();
		}

		return;
	}

	vector<LPGAMEOBJECT> coObjects;

	for (auto obj : listObjects)
	{
		if (dynamic_cast<Door*>(obj) || dynamic_cast<Ground*>(obj) ||
			dynamic_cast<ChangeSceneObject*>(obj) || dynamic_cast<Water*>(obj))
			coObjects.push_back(obj);
		else if (dynamic_cast<BreakWall*>(obj) && obj->GetState() == NORMAL)
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
			if (dynamic_cast<BreakWall*>(obj) && obj->GetState() == NORMAL)
				coObjects.push_back(obj);
			else if (dynamic_cast<Candle*>(obj) || dynamic_cast<FireBall*>(obj))
				coObjects.push_back(obj);
			else if ((dynamic_cast<Zombie*>(obj) || dynamic_cast<VampireBat*>(obj))
				&& obj->GetState() == ACTIVE)
				coObjects.push_back(obj);
			else if (dynamic_cast<BlackLeopard*>(obj) &&
				(obj->GetState() == BLACK_LEOPARD_ACTIVE || obj->GetState() == BLACK_LEOPARD_IDLE || obj->GetState() == BLACK_LEOPARD_JUMP))
				coObjects.push_back(obj);
			else if (dynamic_cast<FishMan*>(obj) &&
				(obj->GetState() == ACTIVE || obj->GetState() == FISHMAN_JUMP || obj->GetState() == FISHMAN_HIT))
				coObjects.push_back(obj);
			else if (dynamic_cast<Boss*>(obj) && obj->GetState() == BOSS_ACTIVE && whip->GetTargetTypeHit() != BOSS)
				coObjects.push_back(obj);
		}

		whip->Update(dt, &coObjects);
	}
	else
		whip->SetTargetTypeHit(-1);
}

void SceneManager::Weapon_Update(DWORD dt, int index)
{
	if (simon->GetSubWeapon() == STOP_WATCH)
		return;

	if (weaponlist[index]->GetScoreReceived() != 0)
	{
		simon->AddScore(weaponlist[index]->GetScoreReceived());
		weaponlist[index]->SetScoreReceived(0);
	}

	if (weaponlist[index]->IsEnable() == false)
	{
		weaponlist[index]->SetTargetTypeHit(-1);
		return;
	}

	vector<LPGAMEOBJECT> coObjects;
	coObjects.push_back(simon); // dùng để xét va chạm của Simon với boomerang

	if (isBossFighting == true && boss->GetState() == BOSS_ACTIVE && weaponlist[index]->GetTargetTypeHit() != BOSS)
		coObjects.push_back(boss);

	for (auto obj : listObjects)
	{
		if (dynamic_cast<Candle*>(obj) || dynamic_cast<Ground*>(obj) || dynamic_cast<FireBall*>(obj))
			coObjects.push_back(obj);
		else if ((dynamic_cast<Zombie*>(obj)||dynamic_cast<VampireBat*>(obj)) 
			&& obj->GetState() == ACTIVE)
			coObjects.push_back(obj);
		else if (dynamic_cast<BlackLeopard*>(obj) && 
			(obj->GetState() == BLACK_LEOPARD_ACTIVE || obj->GetState() == BLACK_LEOPARD_IDLE || obj->GetState() == BLACK_LEOPARD_JUMP))
			coObjects.push_back(obj);
		else if (dynamic_cast<FishMan*>(obj) &&
			(obj->GetState() == ACTIVE || obj->GetState() == FISHMAN_JUMP || obj->GetState() == FISHMAN_HIT))
			coObjects.push_back(obj);
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
			if (dynamic_cast<Ground*>(obj) || (dynamic_cast<BreakWall*>(obj) && obj->GetState() == NORMAL))
				coObjects.push_back(obj);
		}

		item->Update(dt, &coObjects);
	}
}

void SceneManager::Zombie_Update(DWORD dt, LPGAMEOBJECT & object)
{
	if (crossEffectTimer->IsTimeUp() == true && object->GetState() != ZOMBIE_INACTIVE)
	{
		auto zombie = dynamic_cast<Zombie*>(object);

		if (zombie->isSettedPosition == false)
		{
			zombie->isSettedPosition = true;

			float simon_x, simon_y;
			simon->GetPosition(simon_x, simon_y);

			int nx = zombie->GetEntryPosition().x < simon_x ? 1 : -1;
			zombie->SetOrientation(nx);

			// Cần random một khoảng nhỏ để tránh việc các zombie spawn cùng lúc, tại cùng một vị trí
			int randomDistance = rand() % 20; 

			float x, y;
			y = zombie->GetEntryPosition().y;
			if (nx == -1)
				x = game->GetCameraPositon().x + SCREEN_WIDTH - (ENEMY_DEFAULT_BBOX_WIDTH + randomDistance);
			else
				x = game->GetCameraPositon().x + (ENEMY_DEFAULT_BBOX_WIDTH + randomDistance);

			zombie->SetPosition(x, y);
			zombie->SetState(ZOMBIE_ACTIVE);
		}

		vector<LPGAMEOBJECT> coObjects;

		for (auto obj : listObjects)
		{
			if (dynamic_cast<Ground*>(obj) || (dynamic_cast<BreakWall*>(obj) && obj->GetState() == NORMAL))
				coObjects.push_back(obj);
		}

		object->Update(dt, &coObjects, !stopWatchTimer->IsTimeUp());
	}

}

void SceneManager::BlackLeopard_Update(DWORD dt, LPGAMEOBJECT & object)
{
	BlackLeopard * leopard = dynamic_cast<BlackLeopard*>(object);

	if (leopard->GetState() == BLACK_LEOPARD_INACTIVE)
	{
		if (leopard->IsAbleToActivate() == true && IsInViewport(leopard) == true
			&& abs(simon->x - leopard->GetEntryPosition().x) > BLACK_LEOPARD_ACTIVE_BBOX_WIDTH)
		{
			int nx = leopard->GetEntryPosition().x < simon->x ? 1 : -1;
			leopard->SetOrientation(nx);

			leopard->SetState(BLACK_LEOPARD_IDLE);
		}
	}
	else
	{
		vector<LPGAMEOBJECT> coObjects;

		for (auto obj : listObjects)
		{
			if (dynamic_cast<Ground*>(obj) || (dynamic_cast<BreakWall*>(obj) && obj->GetState() == NORMAL))
				coObjects.push_back(obj);
		}

		object->Update(dt, &coObjects, !stopWatchTimer->IsTimeUp());
	}
}

void SceneManager::VampireBat_Update(DWORD dt, LPGAMEOBJECT & object)
{
	if (crossEffectTimer->IsTimeUp() == true && object->GetState() != VAMPIRE_BAT_INACTIVE)
	{
		auto bat = dynamic_cast<VampireBat*>(object);

		if (bat->isSettedPosition == false)
		{
			bat->isSettedPosition = true;

			// set random hướng cho dơi
			int listNx[2] = { -1, 1 };
			int rndIndex = rand() % 2;
			bat->SetOrientation(listNx[rndIndex]);

			// set vị trí cho dơi
			// dơi bay ngang tầm simon, từ phía cuối của 2 đầu màn hình)
			float bx, by;
			int randomDistance = rand() % 30;

			by = simon->y + (rand() % SIMON_BBOX_HEIGHT);

			if (bat->GetOrientation() == -1)
				bx = game->GetCameraPositon().x + SCREEN_WIDTH - (ENEMY_DEFAULT_BBOX_WIDTH - randomDistance);
			else 
				bx = game->GetCameraPositon().x + (ENEMY_DEFAULT_BBOX_WIDTH - randomDistance);

			bat->SetPosition(bx, by);
			bat->SetState(VAMPIRE_BAT_ACTIVE);
		}

		bat->Update(dt, NULL, !stopWatchTimer->IsTimeUp());
	}
}

void SceneManager::FishMan_Update(DWORD dt, LPGAMEOBJECT & object)
{
	auto fishman = dynamic_cast<FishMan*>(object);

	if (fishman->GetState() != FISHMAN_INACTIVE)
	{
		if (fishman->GetState() == FISHMAN_ACTIVE && fishman->isSettedPosition == true &&
			GetTickCount() - fishman->GetLastTimeShoot() >= fishman->GetDeltaTimeToShoot())
		{
			fishman->SetState(FISHMAN_HIT);

			// Tạo fireball
			float fx, fy, nx;

			fishman->GetPosition(fx, fy);
			nx = fishman->GetOrientation();

			auto fireball = new FireBall();
			fireball->SetPosition(fx + 5, fy + 10);
			fireball->SetOrientation(nx);
			fireball->SetState(FIREBALL);
			fireball->SetEnable(true);

			unit = new Unit(grid, fireball, fx, fy);

			// Đặt hướng quay mặt của Fishman sau khi bắn (quay về phía simon)
			float sx, sy;
			simon->GetPosition(sx, sy);

			if (fx < sx) fishman->SetNxAfterShoot(1);
			else fishman->SetNxAfterShoot(-1);
		}
		else
		{
			if (crossEffectTimer->IsTimeUp() == true && fishman->isSettedPosition == false)
			{
				fishman->isSettedPosition = true;

				// Set vị trí cho fishman dựa vào vị trí của Simon
				float simon_x, simon_y;
				simon->GetPosition(simon_x, simon_y);

				int nx = simon_x > fishman->GetEntryPosition().x ? 1 : -1;
				float distance = 50 + rand() % 150;

				float x = simon_x - nx * distance;
				float y = fishman->GetEntryPosition().y;
				
				fishman->SetOrientation(nx);
				fishman->SetPosition(x, y);

				fishman->SetState(FISHMAN_JUMP);

				// Thêm bubbles vào water để render bọt nước
				water->AddBubbles(x, y);
			}

			vector<LPGAMEOBJECT> coObjects;

			for (auto obj : listObjects)
			{
				if ((dynamic_cast<BreakWall*>(obj) && obj->GetState() == NORMAL) ||
					dynamic_cast<Ground*>(obj) || dynamic_cast<Water*>(obj))
					coObjects.push_back(obj);
			}

			fishman->Update(dt, &coObjects, !stopWatchTimer->IsTimeUp());
		}
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


