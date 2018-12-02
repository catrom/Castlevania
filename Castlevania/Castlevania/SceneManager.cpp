#include "SceneManager.h"


SceneManager::SceneManager(Game * game, int idScene)
{
	this->game = game;
	IDScene = idScene;
}


SceneManager::~SceneManager()
{
}

void SceneManager::LoadResources()
{
	simon = new Simon();
	simon->LoadResources(textures, sprites, animations);

	candle = new Candle();
	candle->LoadResources(textures, sprites, animations);

	effect = new Effect();
	effect->LoadResources(textures, sprites, animations);

	ground = new Ground();
	ground->LoadResources(textures, sprites, animations);

	item = new Items();
	item->LoadResources(textures, sprites, animations);

	whip = new Whip();
	whip->LoadResources(textures, sprites, animations);

	weapon = new SubWeapon();
	weapon->LoadResources(textures, sprites, animations);

	stair = new Stair();
	stair->LoadResources(textures, sprites, animations);

	door = new Door();
	door->LoadResources(textures, sprites, animations);

	zombie = new Zombie();
	zombie->LoadResources(textures, sprites, animations);


	tilemaps->Add(SCENE_1, FILEPATH_TEX_MAP_SCENE_1, FILEPATH_DATA_MAP_SCENE_1, 1536, 320, 32, 32);
	tilemaps->Add(SCENE_2, FILEPATH_TEX_MAP_SCENE_2, FILEPATH_DATA_MAP_SCENE_2, 5632, 352, 32, 32);
	tilemaps->Add(SCENE_3, FILEPATH_TEX_MAP_SCENE_3, FILEPATH_DATA_MAP_SCENE_3, 1024, 352, 32, 32);

	textures->Add(ID_TEX_BBOX, FILEPATH_TEX_BBOX, D3DCOLOR_XRGB(255, 255, 255));

	simon = new Simon();
	weapon = new SubWeapon();
}

void SceneManager::LoadObjectsFromFile(LPCWSTR FilePath)
{
	Objects.clear();
	listCandles.clear();
	listStairs.clear();
	listGrounds.clear();
	listItems.clear();
	listDoors.clear();
	listZombies.clear();

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
			candle = new Candle();
			candle->SetPosition(pos_x, pos_y);
			candle->SetState(state);
			candle->SetEnable(isEnable);
			candle->SetIDItem(idItem);
			listCandles.push_back(candle);
			Objects.push_back(candle);
			break;
		case GROUND:
			ground = new Ground();
			ground->SetPosition(pos_x, pos_y);
			ground->SetState(state);
			ground->SetEnable(isEnable);
			ground->SetIDItem(idItem);
			listGrounds.push_back(ground);
			Objects.push_back(ground);
			break;
		case STAIR:
			stair = new Stair();
			stair->SetPosition(pos_x, pos_y);
			stair->SetState(state);
			stair->SetEnable(isEnable);
			stair->SetIDItem(idItem);
			listStairs.push_back(stair);
			Objects.push_back(stair);
			break;
		case DOOR:
			door = new Door();
			door->SetPosition(pos_x, pos_y);
			door->SetState(state);
			door->SetEnable(isEnable);
			door->SetIDItem(idItem);
			listDoors.push_back(door);
			Objects.push_back(door);
			break;
		default:
			break;
		}
	}

	fs.close();


	// Test
	zombie = new Zombie();
	zombie->SetPosition(400, 336);
	zombie->isEnable = true;
	zombie->SetIDItem(5);
	listZombies.push_back(zombie);
	Objects.push_back(zombie);

	//zombie = new Zombie();
	//zombie->SetPosition(450, 336);
	//zombie->isEnable = true;
	//zombie->SetIDItem(6);
	//listZombies.push_back(zombie);
	//Objects.push_back(zombie);



	////////

	Objects.push_back(simon);

	weapon->SetEnable(false);
	Objects.push_back(weapon);
}

void SceneManager::CreateListChangeSceneObjects()
{
	listChangeSceneObjs.clear();

	switch (IDScene)
	{
	case SCENE_1:
		changeScene = new ChangeSceneObject(1440, 336, SCENE_2);
		listChangeSceneObjs.push_back(changeScene);
		break;
	case SCENE_2:
		changeScene = new ChangeSceneObject(3168, 432, SCENE_3);
		listChangeSceneObjs.push_back(changeScene);
		changeScene = new ChangeSceneObject(3808, 432, SCENE_3);
		listChangeSceneObjs.push_back(changeScene);
		break;
	case SCENE_3:
		changeScene = new ChangeSceneObject(96, 80, SCENE_2);
		listChangeSceneObjs.push_back(changeScene);
		changeScene = new ChangeSceneObject(736, 80, SCENE_2);
		listChangeSceneObjs.push_back(changeScene);
		break;
	default:
		break;
	}
}

void SceneManager::Update(DWORD dt)
{
	// Cập nhật trạng thái Simon đi qua cửa:
	// Di chuyển Camera -> Mở cửa -> AutoWalk -> Di chuyển Camera

	if (simon->isWalkThroughDoor == true)
	{
		isMovingCamera = true;
		countDxCamera = 0;

		simon->isWalkThroughDoor = false;
	}

	if (isMovingCamera == true)
	{
		if (countDxCamera < 224)	// Di chuyển camera một đoạn 224
		{
			D3DXVECTOR3 cam = game->GetCameraPositon();
			game->SetCameraPosition(cam.x + 2, cam.y);
			countDxCamera += 2;

			return;
		}

		if (isSetSimonAutoWalk == false)  // AutoWalk
		{
			isSetSimonAutoWalk = true;  

			simon->SetState(WALK);
			simon->vy = 0;
			simon->AutoWalk(120, STAND, 1);
		}
		else
		{
			if (simon->IsAutoWalk() == false)
			{
				if (countDxCamera < 480) // Di chuyển camera thêm một đoạn nữa
				{
					D3DXVECTOR3 cam = game->GetCameraPositon();
					game->SetCameraPosition(cam.x + 2, cam.y);
					countDxCamera += 2;

					return;
				}
				else
				{
					isMovingCamera = false;
					isSetSimonAutoWalk = false;
					countDxCamera = 0;

					tilemaps->Get(IDScene)->index += 1;
				}
			}
		}
	}

	// Khi Simon va chạm với ChangScene objects, tiến hành thay đổi, cập nhật trạng thái
	if (simon->GetChangeScene() != -1)
	{
		if (IDScene == SCENE_1 || 
			(IDScene == SCENE_2 && simon->GetState() == STAIR_DOWN) ||
			(IDScene == SCENE_3 && simon->GetState() == STAIR_UP))
		{
			bool isNeedToUpdatePosition = false;

			if (IDScene != SCENE_1) isNeedToUpdatePosition = true;

			float x, y;
			simon->GetPosition(x, y);

			//DebugOut(L"%f %f \n", x, y);

			IDScene = simon->GetChangeScene();
			ChangeScene(IDScene);

			if (isNeedToUpdatePosition == true)
			{
				switch (IDScene)
				{
				case SCENE_3:
					if (x < 3200.0f) simon->SetPosition(93.0f, 48.0f);
					else simon->SetPosition(733.0f, 48.0f);

					tilemaps->Get(IDScene)->index = 0;
					game->SetCameraPosition(0.0f, 0.0f);
					break;
				case SCENE_2:
					if (x < 320.0f) simon->SetPosition(3136.0f, 335.0f);
					else simon->SetPosition(3776.0f, 335.0f);

					simon->SetState(STAND);
					tilemaps->Get(IDScene)->index = 1;
					game->SetCameraPosition(3056.0f, 0.0f);
					break;
				default:
					break;
				}
			}

			simon->SetChangeScene(-1);
		}
		else
		{
			simon->SetChangeScene(-1);
		}
	}

	for (UINT i = 0; i < Objects.size(); i++)
	{
		LPGAMEOBJECT object = Objects[i];

		if (object->IsEnable() == false)
		{
			if (dynamic_cast<Candle*>(object))
			{
				if (object->idItem != -1)
				{
					// Tạo một item theo id và thêm vào Objects

					item = new Items();
					item->SetEnable(true);
					item->SetPosition(object->x, object->y);
					item->SetItem(object->idItem);

					listItems.push_back(item);
					Objects.push_back(item);
				}
			}

			Objects.erase(Objects.begin() + i);
			i--;

			continue;
		}


		vector<LPGAMEOBJECT> coObjects;

		if (dynamic_cast<Simon*>(object))
		{
			for (auto candle : listCandles)
			{
				if (candle->IsEnable() == false)
					continue;

				coObjects.push_back(candle);
			}

			for (auto ground : listGrounds)
			{
				if (ground->IsEnable() == false)
					continue;

				coObjects.push_back(ground);
			}

			for (auto zombie : listZombies)
			{
				if (zombie->IsEnable() == false)
					continue;

				coObjects.push_back(zombie);
			}

			for (auto door : listDoors)
			{
				if (door->IsEnable() == false)
					continue;

				coObjects.push_back(door);
			}


			simon->Update(dt, &Objects, &coObjects);
			simon->CheckCollisionWithItem(&listItems);
			simon->CheckChangeScene(&listChangeSceneObjs);
		}
		else if (dynamic_cast<Items*>(object))
		{
			for (auto ground : listGrounds)
			{
				if (ground->IsEnable() == false)
					continue;

				coObjects.push_back(ground);
			}

			object->Update(dt, &Objects, &coObjects);
		}
		else if (dynamic_cast<SubWeapon*>(object))
		{
			//for (int j = 1; j < Objects.size(); j++)
			//{
			//	if (Objects[j]->isEnable == false)
			//		continue;

			//	if (dynamic_cast<Ground*>(Objects[j])) // thêm tất cả objects "là ground", dùng trong hàm update của subweapon
			//	{
			//		coObjects.push_back(Objects[j]);
			//	}
			//}
		}
		else
		{
			object->Update(dt, &Objects, &coObjects);
		}
	}



	// update camera

	TileMap * map = tilemaps->Get(IDScene);
	int min_col = map->min_max_col_to_draw[map->index][0];
	int max_col = map->min_max_col_to_draw[map->index][1];

	if (simon->x > SCREEN_WIDTH / 2 &&
		simon->x + SCREEN_WIDTH / 2 < tilemaps->Get(IDScene)->GetMapWidth())
	{
		if (simon->x >= min_col * 32 + (SCREEN_WIDTH / 2 - 16) &&
			simon->x <= max_col * 32 - (SCREEN_WIDTH/ 2 - 16))
		{
			game->SetCameraPosition(simon->x - SCREEN_WIDTH / 2, 0);
		}
	}
}

void SceneManager::Render()
{
	tilemaps->Get(IDScene)->Draw(game->GetCameraPositon());

	for (auto candle : listCandles)
	{
		if (candle->IsEnable() == false)
			continue;

		candle->Render();
		candle->RenderBoundingBox();
	}

	for (auto item : listItems)
	{
		if (item->IsEnable() == false)
			continue;

		item->Render();
		item->RenderBoundingBox();
	}

	for (auto zombie : listZombies)
	{
		if (zombie->IsEnable() == false)
			continue;

		zombie->Render();
		zombie->RenderBoundingBox();
	}

	simon->Render();
	simon->RenderBoundingBox();

	for (auto door : listDoors)
	{
		if (door->IsEnable() == false)
			continue;

		door->Render();
		door->RenderBoundingBox();
	}
}

void SceneManager::ChangeScene(int scene)
{
	IDScene = scene;

	switch (IDScene)
	{
	case SCENE_1:
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_1);
		CreateListChangeSceneObjects();
		simon->SetPosition(0.0f, 302.0f);
		game->SetCameraPosition(0.0f, 0.0f);
		break;
	case SCENE_2:
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_2);
		CreateListChangeSceneObjects();
		simon->SetPosition(0.0f, 335.0f);
		game->SetCameraPosition(0.0f, 0.0f);
		break;
	case SCENE_3:
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_3);
		CreateListChangeSceneObjects();
 		simon->SetPosition(93.0f, 48.0f);
		simon->SetState(STAIR_DOWN);
		game->SetCameraPosition(0.0f, 0.0f);
		break;
	default:
		break;
	}
}

